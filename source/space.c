#include "../headers/space.h"

// Biblioteca que cria e gerencia um tabuleiro dado seu tamanho
// O tabuleiro tem índices [0,X+1] e [0,Y+1] - ou seja, tamanho, em linhas, de X+2; e em colunas, de Y+2,
// onde as bordas/limites do tabuleiro estão definidos.

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

space* create_board(int max_y, int max_x, int enemy_lines){
	space* board;

	if ((max_x < 0) || (max_y < 0) || (enemy_lines >= max_y)) 
		return NULL;
	
	//MUDAR A FORMAÇÃO DE CADA MAPA DEPENDENDO DA DIFICULDADE
	board = generate_board(max_y, max_x);
	for (int i = 0; i < enemy_lines; i++) 
		for (int j = 0; j < max_x; j++) 
			add_enemy(i, j, 1);
	//ADICIONAR A CRIAÇÃO DE OBSTACLES
	
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

	delete_obstacles(board -> obstacles);
	free(board -> map);
	free(board);
}

int in_limits(space* board, int pos_y, int pos_x){

	return ((board -> max_x < pos_x)\
	 || (board -> max_x < pos_y)\
	 || (pos_y < 0) || (pos_x < 0))? 0: 1;
}