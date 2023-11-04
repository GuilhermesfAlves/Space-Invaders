#include "../headers/space.h"

space* generate_board(int max_y, int max_x){
	space* new_board;
	
	new_board = (space*) malloc(sizeof(space));
	new_board -> map = (enemy**) malloc (max_y * sizeof(enemy*));
	for (int i = 0; i < max_y; i++) 
		new_board -> map[i] = (enemy*) calloc (max_x, sizeof(enemy));

	new_board -> max_x = max_x;
	new_board -> max_y = max_y;

	return new_board;
}

space* create_board(unsigned char difficult, limits limits){
	space* board;
	int x;
	int y;
	int qtd_obstacles;
	int vec[6];

	switch (difficult){
	case 0:
		x = 9;
		y = 3;
		qtd_obstacles = 6;
		vec[0] = 2; vec[1] = 1; vec[2] = 1; vec[3] = 0; vec[4] = 0; vec[5] = 0;
		break;
	case 1:
		x = 10;
		y = 4;
		qtd_obstacles = 5;
		vec[0] = 3; vec[1] = 2; vec[2] = 1; vec[3] = 1; vec[4] = 0; vec[5] = 0;
		break;
	case 2:
		x = 11;
		y = 5;
		qtd_obstacles = 4;
		vec[0] = 3; vec[1] = 2; vec[2] = 2; vec[3] = 1; vec[4] = 1; vec[5] = 0;
		break;
	case 3:
		x = 13;
		y = 6;
		qtd_obstacles = 3;
		vec[0] = 3; vec[1] = 3; vec[2] = 2; vec[3] = 2; vec[4] = 1; vec[5] = 1;
		break;
	default:
		return NULL;
	}

	board = generate_board(y, x);
	for (int i = 0; i < y; i++) 
		for (int j = 0; j < x; j++) 
			board -> map[j][i] = add_enemy(i - y + (limits.min_x + limits.max_x)/2, j, vec[i]);


	return board;
}
 
void clean_board(space *board){
	
	for (int i = 0; i < board -> max_y; i++)
		for (int j = 0; j < board -> max_x; j++){
			if (!board -> map[i][j])
				continue;
			free(board -> map[i][j]);
			board -> map[i][j] = NULL;
		}
}

void destroy_board(space* board){

	for (int i = 0; i < board -> max_y; i++)
		free(board -> map[i]);

	destroy_ship(board -> ship);
	destroy_obstacles(board -> obstacles);
	free(board -> map);
	free(board);
}

int in_limits(space* board, int pos_y, int pos_x){

	return ((board -> max_x < pos_x)\
	 || (board -> max_x < pos_y)\
	 || (pos_y < 0) || (pos_x < 0))? 0: 1;
}