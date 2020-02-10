#ifndef __LOGIC_H__
#define __LOGIC_H__
#pragma once
#include "util.h"
typedef struct game_structure {
	int board[8][8];
	int player;
	int end;
	int w_score, b_score;
}reversy;
reversy* init();
void get_place(reversy* game, char* place);
void reverse(reversy* game, vec2& v);
void get_buff(reversy* game, char* buff, char* place);
void change_player(reversy* game);
int is_game_end(reversy* game);
int who_win(reversy* game);
void end_game(reversy* game);

void ai_reverse(char* place);
#endif//__LOGIC_H__