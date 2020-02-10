#ifndef __UTIL_H__
#define __UTIL_H__
#pragma once
enum CONSOLE_COLOR {
	BLACK = 0, DARK_BLUE, DARK_GREEN, SKY_BLUE, DARK_RED, PURPLE, GOLD, GREY, 
	SILVER, BLUE, GREEN, CYAN, RED, PINK, YELLOW, WHITE};
typedef struct vec2 { short x, y; }vec2;
void goto_vec(short x, short y);
void goto_vec(vec2 v);
void set_color(short f, short b);
#endif//__UTIL_H__