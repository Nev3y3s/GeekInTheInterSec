//odelo
#include "util.h"
#include "input.h"
#include "logic.h"
#include "graphic.h"
#include <cstdio>
char front_scr[4096], back_scr[4096];
int main() {
	//vec2 v;
	//int f;
	//f = input("12", &v);
	//printf("%d %d %d\n", f, v.x, v.y);
	auto game = init();
	vec2 v;
	char buff[1024] = {};
	while (!is_game_end(game)) {
		get_place(game, buff);
		get_buff(game, front_scr, buff);
		//printf(front_scr);
		render(front_scr, back_scr);
		set_color(WHITE, BLACK);
		if (*buff) {
			while(input(buff,&v))render(front_scr,back_scr);
			reverse(game, v);
		}
		change_player(game);
	}
	int winner = who_win(game);
	for (int i = 0; i < 17; i++)
		printf("\b");
	printf(winner ? "%s µ¹ ÀÌ ÀÌ°å½À´Ï´Ù." : "ºñ°å½À´Ï´Ù.%s", winner ? winner == 1 ? "°ËÀº" : "Èò" : "");
	end_game(game);
	return 0;
}