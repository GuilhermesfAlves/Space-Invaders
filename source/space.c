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
