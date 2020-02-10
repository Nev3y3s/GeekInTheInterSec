#include "util.h"
#include <Windows.h>
void goto_vec(short x, short y) {
	static auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { x * 2,y });
}
void goto_vec(vec2 v) {
	goto_vec(v.x, v.y);
}
void set_color(short f, short b) {
	static auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (b << 4) | f);
}