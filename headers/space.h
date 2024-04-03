#ifndef __SI_SPACE__
#define __SI_SPACE__

#include "enemy.h"
#include "ship.h"
#include "obstacles.h"
#include "difficult.h"
#include "power_up.h"

#define ALIEN_STEP 30
#define SUPER_ALIEN_STEP 4

typedef struct{
    int min_width;
    int max_width;
    int min_height;
    int max_height;
}limits;

typedef struct {
	char rows;
	char lines;
	ship *ship;
	enemy ***map;
	enemy* super_alien;
	obstacles **obstacles;
	shot_sentinel* shot_list;
	shot_sentinel* super_shot;
	unsigned char qtd_obstacles;
	power_up_list* power_up_list;
} space;

//cria o espaço, cria o mapa de inimigos a partir de um tamanho definido e inicialisa a lista de power ups do space
space* generate_space(int max_y, int max_x);
//dependendo da dificuldade do jogo, define o tamanho do mapa, a quantidade de obstáculos, a quantidade de power ups, a dificuldade dos inimigos e as colunas sem inimigos
int set_formation(char* rows, char* lines, char* difficult, unsigned char* qtd_obstacles, char* qtd_power_ups, char* vec_y, char *blanck_row);
//para cada espaço no mapa cria um inimigo, com determinada dificuldade e caso não seja uma coluna vazia
void add_aliens(space* space, char* vec, char* blank_row);
//criação e inicialização de todas as estruturas em space
space* create_space(unsigned char difficult, limits limits);
//destruição de todos os inimigos em space
void clean_space(space *space);
//destruição de todos os blocos alocados em space
void destroy_space(space *space);

//movimentação dos aliens sobre a tela
int move_aliens(space* space, limits limits, int mov_x);
int has_alien(space* space);

//animação de explosão de um alien
enemy* get_explod(enemy* enemy);
//animação de explosão de todos os aliens no map em space
void get_exploded(space* space);

//teste para conferir a colisão entre uma shot_list com os obstáculos
void hit_obstacles(obstacles** obstacles, unsigned char qtd_obstaclees, shot_sentinel* shot_list);
//teste para conferir a colisão entre uma shot_list e um único alien
short hit_alien(enemy* enemy, shot_sentinel* shot_list);
//teste para conferir a colisão entre uma shot_list e todos os inimigos no mapa
short hit_aliens(enemy*** map, unsigned char lines, unsigned char rows, shot_sentinel* shot_list);
//teste para conferir a colisão entre duas shot_lists
void hit_shots(shot_sentinel* ship_list, shot_sentinel* enemy_list);
//teste para conferir a colisão entre uma shot_list e uma ship
void hit_ship(ship* ship, shot_sentinel* shot_list);

//define posições aleatóreas para inimigos com power up em um mapa
void set_random_power_ups(enemy*** map, int lines, int rows, int power_up_qtd);
//teste para conferir a colisão entre a power_up_list e a ship
void ship_got_power_up(space* space);

#endif