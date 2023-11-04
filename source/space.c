#include "../headers/space.h"

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
		vec[0] = 2; vec[1] = 1; vec[2] = 1; vec[3] = 0; vec[4] = 0; vec[5] = 0;
		break;
	case 1:
		rows = 10;
		lines = 4;
		qtd_obstacles = 5;
		vec[0] = 3; vec[1] = 2; vec[2] = 1; vec[3] = 1; vec[4] = 0; vec[5] = 0;
		break;
	case 2:
		rows = 11;
		lines = 5;
		qtd_obstacles = 4;
		vec[0] = 3; vec[1] = 2; vec[2] = 2; vec[3] = 1; vec[4] = 1; vec[5] = 0;
		break;
	case 3:
		rows = 13;
		lines = 6;
		qtd_obstacles = 3;
		vec[0] = 3; vec[1] = 3; vec[2] = 2; vec[3] = 2; vec[4] = 1; vec[5] = 1;
		break;
	default:
		return NULL;
	}

	board = generate_board(lines, rows);
	for (int i = 0; i < lines; i++) 
		for (int j = 0; j < rows; j++) 
			board -> map[j][i] = add_enemy(i - lines + (limits.min_height + limits.max_height)/2, j - rows + (limits.min_width + limits.max_width)/2, vec[i]);


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
	destroy_obstacles(board -> obstacles);
	free(board -> map);
	free(board);
}

int in_limits(space* board, int pos_y, int pos_x){

	return ((board -> rows < pos_x)\
	 || (board -> rows < pos_y)\
	 || (pos_y < 0) || (pos_x < 0))? 0: 1;
}