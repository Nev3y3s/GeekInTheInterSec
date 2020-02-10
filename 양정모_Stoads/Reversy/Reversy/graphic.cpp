#include "graphic.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
void render(char* front, char* back) {
	if (front == NULL || back == NULL)return;
	static const char* shape[3][8] = {
		{ "　", "●", "Ｓ", "Ｃ", "Ｏ", "Ｒ", "Ｅ"},
		{ "１", "２", "３", "４", "５", "６", "７", "８"},
		{ "Ａ", "Ｂ", "Ｃ", "Ｄ", "Ｅ", "Ｆ", "Ｇ", "Ｈ"} 
	};
	int data[10] = {};
	int anchor_x = 0, anchor_y = 0;
	for (int x = 0, y = 0, i = 0, j; front[i]; ) {
		if (front[i] == '$') {
			i++;
			int pos = front[i++] - '0';
			for (int j = 2; j--;)
				data[pos] = data[pos] * 10 + front[i++] - '0';
			continue;
		}
		if (front[i] == 'g') {
			i++;
			anchor_x = x = anchor_y = y = 0;
			for (int j = 2; j--;)
				anchor_x = anchor_x * 10 + front[i++] - '0';
			for (int j = 2; j--;)
				anchor_y = anchor_y * 10 + front[i++] - '0';
			continue;
		}
		if (front[i] == 'n') {
			i++; x = 0; y++;
			continue;
		}
		for (j = 0; j < 4; j++) {
			if (front[i + j] != back[i + j])break;
			if (front[i + j] == '#')break;
		}
		if (j < 4) {
			int b = front[i], f = front[i + 1];
			if (b >= 'a')b -= 'a' - 10;
			else b -= '0';
			if (f >= 'a')f -= 'a' - 10;
			else f -= '0';
			int a = front[i + 2] - '0', c = front[i + 3] - '0';
			goto_vec(anchor_x + x, anchor_y + y);
			set_color(f, b);
			if (front[i + 2] != '#')
				printf("%s", shape[a][c]);
			else
				printf("%2d", data[c]);
		}
		x++;
		i += 4;
	}
	goto_vec(0, 10);
	set_color(WHITE, BLACK);
	printf("놓을 위치 입력 :     \b\b\b\b");
	strcpy_s(back, 4096, front);
}