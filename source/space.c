#include "../headers/space.h"
#include <stdio.h>
space* generate_space(int lines, int rows){
	space* new_space;
	
	new_space = (space*) malloc(sizeof(space));
	new_space -> map = (enemy***) malloc (lines * sizeof(enemy*));
	for (int i = 0; i < lines; i++) 
		new_space -> map[i] = (enemy**) calloc (rows, sizeof(enemy));

	new_space -> rows = rows;
	new_space -> lines = lines;
	new_space -> super_alien = NULL;
		
	return new_space;
}

void set_formation(char* rows, char* lines, char* difficult, unsigned char* qtd_obstacles, char* vec){

	switch (*difficult){
	case Easy:
		*rows = 9;
		*lines = 3;
		*qtd_obstacles = 6;
		vec[0] = MEDIUM; vec[1] = EASY; vec[2] = EASY; vec[3] = -1; vec[4] = -1; vec[5] = -1;
		break;
	case Normal:
		*rows = 10;
		*lines = 4;
		*qtd_obstacles = 5;
		vec[0] = HARD; vec[1] = MEDIUM; vec[2] = EASY; vec[3] = EASY; vec[4] = -1; vec[5] = -1;
		break;
	case Hard:
		*rows = 11;
		*lines = 5;
		*qtd_obstacles = 4;
		vec[0] = HARD; vec[1] = MEDIUM; vec[2] = MEDIUM; vec[3] = EASY; vec[4] = EASY; vec[5] = -1;
		break;
	case Extreme:
		*rows = 13;
		*lines = 6;
		*qtd_obstacles = 2;
		vec[0] = HARD; vec[1] = HARD; vec[2] = MEDIUM; vec[3] = MEDIUM; vec[4] = EASY; vec[5] = EASY;
		break;
	default:
		return;
	}
}

void add_aliens(space* space, char* vec){

	for (int i = 0; i < space -> lines; i++)
		for (int j = 0; j < space -> rows; j++)
			space -> map[i][j] = add_enemy(vec[i], 0);
}


space* create_space(unsigned char difficult, limits limits){
	space* space;
	char rows;
	char lines;
	char qtd_obstacles;
	char vec[6];

	set_formation(&rows, &lines, &difficult, &qtd_obstacles, vec);
	space = generate_space(lines, rows);
	add_aliens(space, vec);

	space -> qtd_obstacles = qtd_obstacles;
	space -> obstacles = add_obstacles(qtd_obstacles);
	space -> shot_list = create_shotlist();
	space -> super_shot = create_shotlist();
	space -> ship = add_ship((limits.max_width + limits.min_width)/2, limits.max_height);
	
	return space;
}
 
void clean_space(space *space){
	
	for (int i = 0; i < space -> lines; i++)
		for (int j = 0; j < space -> rows; j++){
			if (!space -> map[i][j])
				continue;
			free(space -> map[i][j]);
			space -> map[i][j] = NULL;
		}
}

void destroy_space(space* space){

	for (int i = 0; i < space -> lines; i++)
		free(space -> map[i]);

	destroy_ship(space -> ship);
	clean_shots(space -> shot_list);
	destroy_obstacles(space -> obstacles, space -> qtd_obstacles);
	free(space -> map);
	free(space);
}

int move_aliens(space* space, limits limits, int mov_x){
	int most_x = 0;
	int atual_x;
	int most_y = 0;
	int atual_y;
	int sum_x = 0;
	int sum_y = 0;

	for (int i = 0; i < space -> lines; i++){
		for (int j = 0; j < space -> rows; j++){
			if (!space -> map[i][j])
				continue;

			if (!most_y){
				most_x = (space -> map[i][j] -> pos_x + mov_x*al_get_bitmap_width(*(space -> map[i][j] -> alive))/2)*mov_x;
				most_y = (space -> map[i][j] -> pos_y + al_get_bitmap_height(*(space -> map[i][j] -> alive))/2);
			}
			atual_x = (space -> map[i][j] -> pos_x + mov_x*al_get_bitmap_width(*(space -> map[i][j] -> alive))/2)*mov_x;
			atual_y = (space -> map[i][j] -> pos_y + al_get_bitmap_height(*(space -> map[i][j] -> alive))/2);

			if (atual_x > most_x)
				most_x = atual_x;
			if (atual_y > most_y)
				most_y = atual_y;
		}
	}
	
	if (!most_x)
		return 0;
	if ((mov_x == 1) && (most_x + ALIEN_STEP < limits.max_width))
		sum_x = ALIEN_STEP;
	else if (most_x - ALIEN_STEP*mov_x < limits.min_width*mov_x)
		sum_x = -ALIEN_STEP;
	else if (most_y + ALIEN_STEP < limits.max_height){
		sum_y = ALIEN_STEP;
		mov_x *= -1;
	}
	else 
		return 0;

	for (int i = 0; i < space -> lines; i++){
		for (int j = 0; j < space -> rows; j++){
			if (!space -> map[i][j])
				continue;

			space -> map[i][j] -> pos_x += sum_x;
			space -> map[i][j] -> pos_y += sum_y;
		}
	}
	return mov_x;
}

int has_alien(space* space){
	
	for (int i = 0; i < space -> lines; i++){
		for (int j = 0; j < space -> rows; j++){
			if (space -> map[i][j])
				return 1;
		}
	}
	return 0;
}

void hit_obstacles(obstacles** obstacles,unsigned char qtd_obstacles,shot_sentinel* shot_list){
	char alt;

	for (shot* shot_aux = shot_list -> first; shot_aux; ){
		alt = 0;
		for (int i = 0; i < qtd_obstacles; i++){
			if (!obstacles[i])
				continue;

			if (((obstacles[i] -> pos_y + al_get_bitmap_height(obstacles[i] -> img[obstacles[i] -> life -1])/2) > shot_aux -> pos_y)\
			&& ((obstacles[i] -> pos_y - al_get_bitmap_height(obstacles[i] -> img[obstacles[i] -> life -1])/2) < shot_aux -> pos_y)\
			&& ((obstacles[i] -> pos_x - al_get_bitmap_width(obstacles[i] -> img[obstacles[i] -> life -1])/2) < shot_aux -> pos_x + al_get_bitmap_width(*(shot_aux) -> img)/2)\
			&& ((obstacles[i] -> pos_x + al_get_bitmap_width(obstacles[i] -> img[obstacles[i] -> life -1])/2) > shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img)/2)){
				alt = 1;
				obstacles[i] -> life -= shot_aux -> damage;
				shot_aux = destroy_shot(shot_aux, shot_list);
				if (obstacles[i] -> life <= 0)
					obstacles[i] = destroy_obstacle(obstacles[i]);
				if (!shot_aux)
					return;
			}
		}
		if (!alt)
			shot_aux = shot_aux -> next;
	}
}

short hit_alien(enemy* enemy, shot_sentinel* shot_list){
	short sum = 0;

	for (shot* shot_aux = shot_list -> first; shot_aux; shot_aux = shot_aux -> next){
		if (!enemy)
			return 0;

		if (((enemy -> pos_y + al_get_bitmap_height(*(enemy) -> alive)/2) > shot_aux -> pos_y)\
		&& ((enemy -> pos_y - al_get_bitmap_height(*(enemy) -> alive)/2) < shot_aux -> pos_y)\
		&& ((enemy -> pos_x - al_get_bitmap_width(*(enemy) -> alive)/2) < shot_aux -> pos_x + al_get_bitmap_width(*(shot_aux) -> img)/2)\
		&& ((enemy -> pos_x + al_get_bitmap_width(*(enemy) -> alive)/2) > shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img)/2)){
			shot_aux = destroy_shot(shot_aux, shot_list);
			sum += enemy -> points;
			enemy -> exploded++;
			return sum;
		}
	}
}

short hit_aliens(enemy*** map, unsigned char lines, unsigned char rows,shot_sentinel* shot_list){
	short sum = 0;

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < rows; j++)
			sum += hit_alien(map[i][j], shot_list);

	return sum;
}

void get_exploded(enemy***map, unsigned char lines, unsigned char rows){

	for (int i = 0; i < lines; i++) 
		for (int j = 0; j < rows; j++)
			map[i][j] = get_explod(map[i][j]);
}

enemy* get_explod(enemy* enemy){
	
	if (!((enemy) && (enemy -> exploded)))
		return enemy;
	
	if (enemy -> exploded == 20)
		return destroy_enemy(enemy);
	else 
		enemy -> exploded++;

}

void hit_shots(shot_sentinel* ship_list, shot_sentinel* enemy_list){
	char alt_s;

	for (shot* ship_shot = ship_list -> first; ship_shot; ){
		alt_s = 0;
		for (shot* enemy_shot = enemy_list -> first; enemy_shot; ){//bateu em shot
			if (((enemy_shot -> pos_y + al_get_bitmap_height(*(enemy_shot) -> img)/2) > ship_shot -> pos_y - al_get_bitmap_height(*(ship_shot) -> img)/2)\
			&& ((enemy_shot -> pos_y - al_get_bitmap_height(*(enemy_shot) -> img)/2) < ship_shot -> pos_y + al_get_bitmap_height(*(ship_shot) -> img)/2)\
			&& ((enemy_shot -> pos_x - al_get_bitmap_width(*(enemy_shot) -> img)/2) < ship_shot -> pos_x + al_get_bitmap_width(*(ship_shot) -> img)/2)\
			&& ((enemy_shot -> pos_x + al_get_bitmap_width(*(enemy_shot) -> img)/2) > ship_shot -> pos_x - al_get_bitmap_width(*(ship_shot) -> img)/2)){
				ship_shot = destroy_shot(ship_shot, ship_list);
				enemy_shot = destroy_shot(enemy_shot, enemy_list);
				alt_s = 1;
				if (!ship_shot)
					return;
			} else 
				enemy_shot = enemy_shot -> next;
		}
		if (!alt_s)
			ship_shot = ship_shot -> next;
	}
}

void hit_ship(ship* ship, shot_sentinel* shot_list){

	for (shot* shot_aux = shot_list -> first; shot_aux; ){//bateu em ship
		if (((ship -> pos_y + al_get_bitmap_height(*(ship) -> alive)/2) > shot_aux -> pos_y)\
        && ((ship -> pos_y - al_get_bitmap_height(*(ship) -> alive)/2) < shot_aux -> pos_y)\
        && ((ship -> pos_x - al_get_bitmap_width(*(ship) -> alive)/2) < shot_aux -> pos_x + al_get_bitmap_width(*(shot_aux) -> img)/2)\
        && ((ship -> pos_x + al_get_bitmap_width(*(ship) -> alive)/2) > shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img)/2)){
            shot_aux = destroy_shot(shot_aux, shot_list);
			ship -> life--;
			if (!ship -> life)
				ship -> exploded = 1;
		} else 
			shot_aux = shot_aux -> next;
	}
}
