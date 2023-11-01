#include "../headers/space.h"
#include "../headers/enemy.h"

// Biblioteca que cria e gerencia um tabuleiro dado seu tamanho
// O tabuleiro tem índices [0,X+1] e [0,Y+1] - ou seja, tamanho, em linhas, de X+2; e em colunas, de Y+2,
// onde as bordas/limites do tabuleiro estão definidos.

space* generate_board(int max_y, int max_x){
	space* new_board;
	
	new_board = (space*) malloc(sizeof(space));
	new_board -> map = (sqm**) malloc ((max_y + 1) * sizeof(sqm*));
	for (int i = 0; i <= max_y; i++) 
		new_board -> map[i] = (sqm*) calloc (max_x + 1, sizeof(sqm));

	new_board -> max_x = max_x;
	new_board -> max_y = max_y;

	return new_board;
}

space* create_board(int max_y, int max_x, int enemy_lines){
	space* board;

	if ((max_x <= 0) || (max_y <= 0)) 
		return NULL;
	if (enemy_lines > max_y) 
		return NULL;
	
	board = generate_board(max_y, max_x);
	for (int i = 0; i <= enemy_lines; i++) 
		for (int j = 0; j <= max_x; j++) 
			add_enemy(board, i, j, 1);
	
	return board;
}
 
void clean_board(space *board){
	
	for (int i = 0; i <= board -> max_y; i++){
		for (int j = 0; j <= board -> max_x; j++){
			if (!board -> map[i][j].entity)
				continue;
			free(board -> map[i][j].entity);
			board -> map[i][j].entity = NULL;
		}
	}
}

void destroy_board(space* board){

	for (int i = 0; i <= board -> max_y; i++)
		free(board -> map[i]);

	free(board -> map);
	free(board);
}

int in_limits(space* board, int pos_y, int pos_x){

	return ((board -> max_x < pos_x)\
	 || (board -> max_x < pos_y)\
	 || (pos_y < 0) || (pos_x < 0))? 0: 1;
}