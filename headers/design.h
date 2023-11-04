#ifndef __SI_DESIGN__
#define __SI_DESIGN__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "difficult.h"
#include "space.h"
#include "joystick.h"
#include "theme.h"

void show_START_ALERT(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, int frame, int move);

void show_themes(ALLEGRO_FONT* font, ALLEGRO_DISPLAY_MODE *disp_data, theme* theme, int move);

ALLEGRO_BITMAP* add_logo(ALLEGRO_DISPLAY_MODE* disp_data);

ALLEGRO_BITMAP* add_logo_alien(ALLEGRO_DISPLAY_MODE* disp_data);

void show_alien(enemy* alien, ALLEGRO_DISPLAY_MODE *disp_data);

void show_obstacles(obstacles* obstacles, ALLEGRO_DISPLAY_MODE* disp_data);

void show_ship(ship* ship, ALLEGRO_DISPLAY_MODE* disp_data);

#endif //__DESIGN__