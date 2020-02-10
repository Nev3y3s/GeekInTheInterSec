#include "logic.h"
#include <cstring>
#include <cstdlib>
reversy* init() {
	reversy* game = (reversy*)malloc(sizeof(reversy));
		if (!game)return NULL;
	game->player = 1;					//black
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			game->board[i][j] = 0;
	game->board[3][3] = game->board[4][4] = 1;
	game->board[3][4] = game->board[4][3] = -1;
	game->end = 0;
	game->b_score = game->w_score = 2;
	return game;
}
int adjacent_check(reversy* game, int x, int y, int i, int j) {
	return (x + i < 0 || x + i >= 8)
		|| (y + j < 0 || y + j >= 8)
		|| (-game->player != game->board[x + i][y + j]);
}
int non_adjacent_check(reversy* game, int x, int y, int i, int j, int k) {
	return (x + k * i < 0 || x + k * i >= 8)
		|| (y + k * j < 0 || y + k * j >= 8)
		|| (!game->board[x + k * i][y + k * j]);
}
int is_placeable(reversy* game, int x, int y) {	//0 : not
	if (game->board[x][y])return 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (adjacent_check(game, x, y, i, j))continue;
			for (int k = 2; k < 8; k++) {
				if (non_adjacent_check(game, x, y, i, j, k))break;
				if (game->player == game->board[x + k * i][y + k * j])
					return 1;
			}
		}
	}
	return 0;
}
void get_place(reversy* game, char* place) {
	int p = 0;
	game->end++;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (is_placeable(game, i, j)) {
				place[p + 0] = '0' + i;
				place[p + 1] = '0' + j;
				p += 2;
				game->end = 0;
			}
		}
	}
	place[p] = 0;
}
void flip(reversy* game, int x, int y, int i, int j, int k) {
	for (int it = 1; it < k; it++) {
		game->b_score += game->player;
		game->w_score -= game->player;
		game->board[x + it * i][y + it * j] *= -1;
	}
}
void reverse(reversy* game, vec2& v) {
	int x = v.x, y = v.y;
	game->board[x][y] = game->player;
	++(game->player == 1 ? game->b_score : game->w_score);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (adjacent_check(game, x, y, i, j))continue;
			for (int k = 2; k < 8; k++) {
				if (non_adjacent_check(game, x, y, i, j, k))break;
				if (game->player == game->board[x + k * i][y + k * j]) {
					flip(game, x, y, i, j, k);
					break;
				}
			}
		}
	}
}
void get_buff(reversy* game, char* buff, char * place) {
	char* p = buff;
	char* pl = place;
	auto add_value = [&p](int pos, int value) {
		*p++ = '$';
		*p++ = pos + '0';
		*p++ = value / 10 % 10 +'0';
		*p++ = value % 10 +'0';
	};
	add_value(0, game->b_score);
	add_value(1, game->w_score);
	auto base = [&p, &pl](const char* color, const char* shape) {
		if (*color == 'b')pl += 2;
		strncpy_s(p, 1024, color, 2);
		strncpy_s(p + 2, 1022, shape, 2);
		p += 4;
	};
	base("0f", "00");
	char temp[3] = "10";
	for (int i = 0; i < 8; i++) {
		base("0f", temp);
		temp[1]++;
	}
	*temp = '2'; temp[1] = '0';
	*p++ = 'n';
	for (int i = 0; i < 8; i++) {
		base("0f", temp);
		temp[1]++;
		for (int j = 0; j < 8; j++) {
			///"b0", "bf", "70", "80", "7f", "8f";
			base((i == *pl - '0' && j == pl[1] - '0') ? (game->board[i][j]==1 ? "b0" : "bf") :
				(game->board[i][j]==1 ? ((i+j)%2 ? "70" : "80") : ((i+j)%2 ? "7f" : "8f")),
				game->board[i][j] ? "01" : "00");
		}
		*p++ = 'n';
	}// board buffer
	auto go_vec = [&p](int x, int y) {
		*p++ = 'g';
		*p++ = x / 10 % 10 + '0';
		*p++ = x % 10 + '0';
		*p++ = y / 10 % 10 + '0';
		*p++ = y % 10 + '0';
	}; go_vec(12, 1);
	char score_shape[3] = "02";
	char code_shape[3] = "#0";
	for (int i = 0; i < 3; i++) base("0f", "00");
	for (score_shape[1]='2'; score_shape[1] < '2' + 5; score_shape[1]++) base("0f", score_shape);
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base("f0", "00");
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base(i % 10 ? game->player * (5 - i) >= 0 ? "e0" : "70" : "f0", "00");
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base(i % 4 == 1 ? game->player * (5 - i) >= 0 ? "e0" : "70" : i < 5 && i % 10 ? "0f" : "f0", "00");
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base(i % 4 == 1 ? game->player * (5 - i) >= 0 ? "e0" : "70" : i < 5 && i % 10 ? "0f" : "f0",  i==3 ? "#0" : i==7 ? "#1" :"00");
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base(i % 4 == 1 ? game->player * (5 - i) >= 0 ? "e0" : "70" : i < 5 && i % 10 ? "0f" : "f0", "00");
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base(i % 10 ? game->player * (5 - i) >= 0 ? "e0" : "70" : "f0", "00");
	*p++ = 'n';
	for (int i = 0; i < 11; i++)base("f0", "00");





	*p = 0;
}
void change_player(reversy* game) {
	game->player *= -1;
}
int is_game_end(reversy* game) {
	if (game->end < 2)
		for (int i = 0; i < 8; i++) 
			for (int j = 0; j < 8; j++) 
				if (!game->board[i][j])return 0;
	return game->end == 2;
}
int who_win(reversy* game) {
	return game->w_score > game->b_score ? -1 : game->w_score == game->b_score ? 0 : 1;
}
void end_game(reversy* game) { free(game); }