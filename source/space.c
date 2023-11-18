#include "../headers/space.h"

space* generate_space(int lines, int rows){
	space* new_space;
	
	if (!(new_space = (space*) malloc(sizeof(space))))
		return NULL;
		
	if (!(new_space -> map = (enemy***) malloc (lines * sizeof(enemy*))))
		return NULL;
	for (int i = 0; i < lines; i++) 
		if (!(new_space -> map[i] = (enemy**) calloc (rows, sizeof(enemy))))
			return NULL;

	new_space -> rows = rows;
	new_space -> lines = lines;
	new_space -> super_alien = NULL;
	new_space -> power_up_list = create_power_up_list();
	
	return new_space;
}

int set_formation(char* rows, char* lines, char* difficult, unsigned char* qtd_obstacles, char* qtd_power_ups, char* vec_y, char *blanck_row){

	switch (*difficult){
	case Diff_Easy:
		*rows = 9;
		*lines = 3;
		*qtd_obstacles = 6;
		*qtd_power_ups = 7;
		vec_y[0] = MEDIUM; vec_y[1] = EASY; vec_y[2] = EASY; vec_y[3] = -1; vec_y[4] = -1; vec_y[5] = -1;
		break; 
	case Diff_Normal:
		*rows = 10;
		*lines = 4;
		*qtd_obstacles = 5;
		*qtd_power_ups = 6;
		vec_y[0] = HARD; vec_y[1] = MEDIUM; vec_y[2] = EASY; vec_y[3] = EASY; vec_y[4] = -1; vec_y[5] = -1;
		break;
	case Diff_Hard:
		*rows = 11;
		*lines = 5;
		*qtd_obstacles = 4;
		*qtd_power_ups = 4;
		vec_y[0] = HARD; vec_y[1] = MEDIUM; vec_y[2] = MEDIUM; vec_y[3] = EASY; vec_y[4] = EASY; vec_y[5] = -1;
		break;
	case Diff_Extreme:
		*rows = 13;
		*lines = 6;
		*qtd_obstacles = 2;
		*qtd_power_ups = 2;
		vec_y[0] = HARD; vec_y[1] = HARD; vec_y[2] = MEDIUM; vec_y[3] = MEDIUM; vec_y[4] = EASY; vec_y[5] = EASY;
		break;
	default:
		return 0;
	}
	blanck_row[0] = rand() % (*rows + 5);
	blanck_row[1] = rand() % (*rows + 5);
	// rows + 5 para haver a possibilidade de não existir coluna vazia 
	return 1;
}

void add_aliens(space* space, char* vec_y, char* blanck_row){

	for (int i = 0; i < space -> lines; i++)
		for (int j = 0; j < space -> rows; j++)
			space -> map[i][j] = ((j == blanck_row[0]) || (j == blanck_row[1]))? NULL: add_enemy(vec_y[i], 0);
}


space* create_space(unsigned char difficult, limits limits){
	space* space;
	char rows;
	char lines;
	char qtd_obstacles;
	char vec_y[6];
	char blank_row[2];
	char qtd_power_ups;
	if (!(set_formation(&rows, &lines, &difficult, &qtd_obstacles, &qtd_power_ups, vec_y, blank_row)))
		return NULL;
	if (!(space = generate_space(lines, rows)))
		return NULL;
	add_aliens(space, vec_y, blank_row);
	
	space -> qtd_obstacles = qtd_obstacles;
	if (!(space -> obstacles = add_obstacles(qtd_obstacles)))
		return NULL;
	if (!(space -> shot_list = create_shotlist()))
		return NULL;
	if (!(space -> super_shot = create_shotlist()))
		return NULL;
	if (!(space -> ship = add_ship((limits.max_width + limits.min_width)/2, limits.max_height)))
		return NULL;
	set_random_power_ups(space -> map, space -> lines, space -> rows, qtd_power_ups);
	
	return space;
}
 
void clean_space(space *space){
	
	for (int i = 0; i < space -> lines; i++)
		for (int j = 0; j < space -> rows; j++){
			if (!space -> map[i][j])
				continue;
			
			space -> map[i][j] = destroy_enemy(space -> map[i][j]);
		}
}

void destroy_space(space* space){
	clean_space(space);
	for (int i = 0; i < space -> lines; i++)
		free(space -> map[i]);
	free(space -> map);
	destroy_shot_list(space -> super_shot);
	destroy_power_up_list(space -> power_up_list);
	destroy_shot_list(space -> shot_list);
	if (space -> super_alien)
		destroy_enemy(space -> super_alien);
	destroy_obstacles(space -> obstacles, space -> qtd_obstacles);
	destroy_ship(space -> ship);
	free(space);
}

int move_aliens(space* space, limits limits, int mov_x){
	int most_x = 0;
	int atual_x;
	int most_y = 0;
	int atual_y;
	int sum_x = 0;
	int sum_y = 0;
	int mid_x = (limits.max_width + limits.min_width)/2;

	for (int i = 0; i < space -> lines; i++){
		for (int j = 0; j < space -> rows; j++){
			if (!space -> map[i][j])
				continue;

			if (!most_y){
				most_x = space -> map[i][j] -> pos_x*mov_x + al_get_bitmap_width(*(space -> map[i][j] -> alive_img))/2;
				most_y = space -> map[i][j] -> pos_y + al_get_bitmap_height(*(space -> map[i][j] -> alive_img))/2;
			}
			atual_x = space -> map[i][j] -> pos_x*mov_x + al_get_bitmap_width(*(space -> map[i][j] -> alive_img))/2;
			atual_y = space -> map[i][j] -> pos_y + al_get_bitmap_height(*(space -> map[i][j] -> alive_img))/2;

			if (atual_x > most_x)
				most_x = atual_x;
			if (atual_y > most_y)
				most_y = atual_y;
		}
	}
	
	if (!most_x)
		return STAY;
	if ((most_x + ALIEN_STEP < mid_x*mov_x + mid_x - limits.min_width))
		sum_x = ALIEN_STEP*mov_x;
	else if (most_y + ALIEN_STEP < limits.max_height){
		sum_y = ALIEN_STEP;
		mov_x *= -1;
	} else 
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
	
	for (int i = 0; i < space -> lines; i++)
		for (int j = 0; j < space -> rows; j++)
			if (space -> map[i][j])
				return 1;

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

		if (enemy -> exploded)
			return 0;

		if (((enemy -> pos_y + al_get_bitmap_height(*(enemy) -> alive_img)/2) > shot_aux -> pos_y)\
		&& ((enemy -> pos_y - al_get_bitmap_height(*(enemy) -> alive_img)/2) < shot_aux -> pos_y)\
		&& ((enemy -> pos_x - al_get_bitmap_width(*(enemy) -> alive_img)/2) < shot_aux -> pos_x + al_get_bitmap_width(*(shot_aux) -> img)/2)\
		&& ((enemy -> pos_x + al_get_bitmap_width(*(enemy) -> alive_img)/2) > shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img)/2)){
			shot_aux = destroy_shot(shot_aux, shot_list);
			al_play_sample(enemy -> death_s, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			sum += enemy -> points;
			enemy -> exploded++;
			return sum;
		}
	}
}

short hit_aliens(enemy*** map, unsigned char lines, unsigned char rows, shot_sentinel* shot_list){
	short sum = 0;

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < rows; j++)
			sum += hit_alien(map[i][j], shot_list);

	return sum;
}

void get_exploded(space* space){

	for (int i = 0; i < space -> lines; i++) 
		for (int j = 0; j < space -> rows; j++){
			space -> map[i][j] = get_explod(space -> map[i][j]);
			if ((space -> map[i][j]) && (space -> map[i][j] -> power_up) && (space -> map[i][j] -> exploded == 8)){
				power_up* aux_power_up = add_power_up(space -> map[i][j] -> power_up, space -> map[i][j] -> pos_x, space -> map[i][j] -> pos_y, space -> power_up_list);
			}
		}
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
		if (((ship -> pos_y + al_get_bitmap_height(*(ship) -> alive_img)/2) > shot_aux -> pos_y)\
        && ((ship -> pos_y - al_get_bitmap_height(*(ship) -> alive_img)/2) < shot_aux -> pos_y)\
        && ((ship -> pos_x - al_get_bitmap_width(*(ship) -> alive_img)/2) < shot_aux -> pos_x + al_get_bitmap_width(*(shot_aux) -> img)/2)\
        && ((ship -> pos_x + al_get_bitmap_width(*(ship) -> alive_img)/2) > shot_aux -> pos_x - al_get_bitmap_width(*(shot_aux) -> img)/2)){
            ship -> power_up_eff = -1;
			shot_aux = destroy_shot(shot_aux, shot_list);
			if (ship -> power_up_type == SHIELD)
				continue;
			ship -> life--;
			al_play_sample(ship -> death_s, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			ship -> exploded = 1;
		} else 
			shot_aux = shot_aux -> next;
	}
}

void set_random_power_ups(enemy*** map, int lines, int rows, int power_up_qtd){
	int to_set_x;
	int to_set_y;

	for (int p = 0; p < power_up_qtd; p++){
		to_set_y = rand() % rows;
		to_set_x = rand() % lines;
		if (!map[to_set_x][to_set_y])
			continue;
		map[to_set_x][to_set_y] -> power_up = (rand() % QTD_POWER_UP_TYPES) + 1;
	}
}

void ship_got_power_up(space* space){
	
	for (power_up* current = space -> power_up_list -> first; current; current = current -> next){
		current -> pos_y += FALL_MOVE;
		if (((space -> ship -> pos_y + al_get_bitmap_height(*(space -> ship) -> alive_img)/2) > current -> pos_y)\
			&& ((space -> ship -> pos_y - al_get_bitmap_height(*(space -> ship) -> alive_img)/2) < current -> pos_y)\
			&& ((space -> ship -> pos_x - al_get_bitmap_width(*(space -> ship) -> alive_img)/2) < current -> pos_x + al_get_bitmap_width(current -> img)/2)\
			&& ((space -> ship -> pos_x + al_get_bitmap_width(*(space -> ship) -> alive_img)/2) > current -> pos_x - al_get_bitmap_width(current -> img)/2)){
				space -> ship -> power_up_type = current -> type;
				space -> ship -> power_up_eff = POWER_UP_LIFETIME;
				destroy_power_up(current, space -> power_up_list);
			}
	}
}