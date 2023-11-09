#include "../headers/space.h"
#include <stdio.h>
space* generate_board(int lines, int rows){
	space* new_board;
	
	new_board = (space*) malloc(sizeof(space));
	new_board -> map = (enemy***) malloc (lines * sizeof(enemy*));
	for (int i = 0; i < lines; i++) 
		new_board -> map[i] = (enemy**) calloc (rows, sizeof(enemy));

	new_board -> rows = rows;
	new_board -> lines = lines;

	return new_board;
}

space* create_board(unsigned char difficult, limits limits){
	space* board;
	int rows;
	int lines;
	int qtd_obstacles;
	int vec[6];

	switch (difficult){
	case 0:
		rows = 9;
		lines = 3;
		qtd_obstacles = 6;
		vec[0] = 1; vec[1] = 0; vec[2] = 0; vec[3] = -1; vec[4] = -1; vec[5] = -1;
		break;
	case 1:
		rows = 10;
		lines = 4;
		qtd_obstacles = 5;
		vec[0] = 2; vec[1] = 1; vec[2] = 0; vec[3] = 0; vec[4] = -1; vec[5] = -1;
		break;
	case 2:
		rows = 11;
		lines = 5;
		qtd_obstacles = 4;
		vec[0] = 2; vec[1] = 1; vec[2] = 1; vec[3] = 0; vec[4] = 0; vec[5] = -1;
		break;
	case 3:
		rows = 13;
		lines = 6;
		qtd_obstacles = 2;
		vec[0] = 2; vec[1] = 2; vec[2] = 1; vec[3] = 1; vec[4] = 0; vec[5] = 0;
		break;
	default:
		return NULL;
	}

	board = generate_board(lines, rows);
	
	for (int i = 0; i < lines; i++) 
		for (int j = 0; j < rows; j++) {
			int between_x = (limits.max_width - limits.min_width)*0.3/rows;
			int between_y = (limits.max_height - limits.min_height)*0.4/lines;
			board -> map[i][j] = add_enemy(vec[i]);
		}
	board -> qtd_obstacles = qtd_obstacles;
	board -> obstacles = add_obstacles(qtd_obstacles);
	board -> shot_list = create_shotlist();
	board -> ship = add_ship((limits.max_width + limits.min_width)/2, limits.max_height);
	
	return board;
}
 
void clean_board(space *board){
	
	for (int i = 0; i < board -> lines; i++)
		for (int j = 0; j < board -> rows; j++){
			if (!board -> map[i][j])
				continue;
			free(board -> map[i][j]);
			board -> map[i][j] = NULL;
		}
}

void destroy_board(space* board){

	for (int i = 0; i < board -> lines; i++)
		free(board -> map[i]);

	destroy_ship(board -> ship);
	clean_shots(board -> shot_list);
	destroy_obstacles(board -> obstacles, board -> qtd_obstacles);
	free(board -> map);
	free(board);
}

void hit_obstacles(obstacles** obstacles,unsigned char qtd_obstacles,shot_sentinel* shot_list){
	shot* previous = NULL;
	char alt;

	for (shot* shot_aux = shot_list -> first; shot_aux; ){
		alt = 0;
		for (int i = 0; i < qtd_obstacles; i++){
			if (((obstacles[i] -> pos_y + al_get_bitmap_height(*(obstacles[i]) -> img)/2) < shot_aux -> pos_y)\
			&& ((obstacles[i] -> pos_y - al_get_bitmap_height(*(obstacles[i]) -> img)/2) > shot_aux -> pos_y)\
			&& ((obstacles[i] -> pos_x - al_get_bitmap_width(*(obstacles[i]) -> img)/2) > shot_aux -> pos_x)\
			&& ((obstacles[i] -> pos_x + al_get_bitmap_width(*(obstacles[i]) -> img)/2) < shot_aux -> pos_x)){
				shot_aux = destroy_shot(shot_aux, previous, shot_list);
				alt = 1;
				obstacles[i] -> life--;
				if (!shot_aux)
					return;				
			}
		}
		if ((!previous) || (shot_list -> first))
			previous = shot_aux;
		else if (previous)
			previous = (shot*) previous -> next;
		if ((shot_aux) && (!alt));
			shot_aux = (shot*) shot_aux -> next;
	}
}

short hit_aliens(enemy*** map, unsigned char lines, unsigned char rows,shot_sentinel* shot_list){
	short sum = 0;
	char alt;
	shot* previous = NULL;

	for (shot* shot_aux = shot_list -> first; shot_aux; ){
		alt = 0;
		for (int i = 0; i < lines; i++){
			for (int j = 0; j < rows; j++){
				if (!map[i][j])
					continue;
				if (((map[i][j] -> pos_y + al_get_bitmap_height(*(map[i][j]) -> img1)/2) > shot_aux -> pos_y)\
				&& ((map[i][j] -> pos_y - al_get_bitmap_height(*(map[i][j]) -> img1)/2) < shot_aux -> pos_y)\
				&& ((map[i][j] -> pos_x - al_get_bitmap_width(*(map[i][j]) -> img1)/2) < shot_aux -> pos_x)\
				&& ((map[i][j] -> pos_x + al_get_bitmap_width(*(map[i][j]) -> img1)/2) > shot_aux -> pos_x)){
					shot_aux = destroy_shot(shot_aux, previous, shot_list);
					alt = 1;
					sum += map[i][j] -> type*10;
					map[i][j] = destroy_enemy(map[i][j]);
					if (!shot_aux)
						return sum;
				}
			}
		}

		if ((!previous) || (shot_list -> first))
			previous = shot_aux;
		else if (previous)
			previous = (shot*) previous -> next;
		if ((shot_aux) && (!alt))
			shot_aux = (shot*) shot_aux -> next;
	}

	return sum;
}

void hit_shots(shot_sentinel* ship_list, shot_sentinel* enemy_list){
	shot* previous = NULL;
	shot* previous_aux = NULL;
	char alt_e;
	char alt_s;

	for (shot* shot_aux = ship_list -> first; shot_aux; ){
		alt_s = 0;
		for (shot* shot_atual = enemy_list -> first; shot_atual; ){//bateu em shot
			alt_e = 0;
			if (((shot_atual -> pos_y + al_get_bitmap_height(*(shot_atual) -> img1)/2) < shot_aux -> pos_y)\
			&& ((shot_atual -> pos_y - al_get_bitmap_height(*(shot_atual) -> img1)/2) > shot_aux -> pos_y)\
			&& ((shot_atual -> pos_x - al_get_bitmap_width(*(shot_atual) -> img1)/2) > shot_aux -> pos_x)\
			&& ((shot_atual -> pos_x + al_get_bitmap_width(*(shot_atual) -> img1)/2) < shot_aux -> pos_x)){
				shot_aux = destroy_shot(shot_aux, previous, ship_list);
				shot_atual = destroy_shot(shot_atual, previous_aux, enemy_list);
				alt_e = alt_s = 1;
				if ((!shot_aux) || (shot_atual))
					return;
			}
			
			if ((!previous_aux) || (enemy_list -> first))
				previous_aux = shot_aux;
			else if (previous_aux)
				previous_aux = (shot*) previous_aux -> next;
			if ((shot_atual) && (!alt_e))
				shot_atual = (shot*) shot_atual -> next;
		}
		if ((!previous) || (ship_list -> first))
			previous = shot_aux;
		else if (previous)
			previous = (shot*) previous -> next;
		if ((shot_aux) && (!alt_s))
			shot_aux = (shot*) shot_aux -> next;
	}
}

void hit_ship(ship* ship, shot_sentinel* shot_list){
	shot* previous = NULL;
	char alt;

	for (shot* shot_aux = shot_list -> first; shot_aux; ){//bateu em ship
        alt = 0;
		if (((ship -> pos_y + al_get_bitmap_height(*(ship) -> img)/2) < shot_aux -> pos_y)\
        && ((ship -> pos_y - al_get_bitmap_height(*(ship) -> img)/2) > shot_aux -> pos_y)\
        && ((ship -> pos_x - al_get_bitmap_width(*(ship) -> img)/2) > shot_aux -> pos_x)\
        && ((ship -> pos_x + al_get_bitmap_width(*(ship) -> img)/2) < shot_aux -> pos_x)){
            shot_aux = destroy_shot(shot_aux, previous, shot_list);
            alt = 1;
			ship -> life--;
        }
		if ((!previous) || (shot_list -> first))
			previous = shot_aux;
		else if (previous)
			previous = (shot*) previous -> next;
		if ((shot_aux) && (!alt))
			shot_aux = (shot*) shot_aux -> next;
	}
}