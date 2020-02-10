#include "input.h"
#include <cstdio>
#include <cstring>
int input(const char* place, vec2* v) { // 0 : success, 1 : notexist vec, 2 : can not put vec 
	char buff[128] = {};
	scanf_s(" %[^\n]s", buff, 127);
	if (strlen(buff) != 2)return 1;
	if ((('A' <= *buff && *buff < 'A' + 8) || ('a' <= *buff && *buff < 'a' + 8))// A4 : v = {1,4}
		&& ('1' <= buff[1] && buff[1] < '1' + 8))
		v->x = (*buff | 0x20) - 'a', v->y = buff[1] - '1';
	else if (('1' <= *buff && *buff < '1' + 8)									// 4a : v = {1,4};
		&& ('A' <= buff[1] && buff[1] < 'A' + 8) || ('a' <= buff[1] && buff[1] < 'a' + 8))
		v->x = (buff[1] | 0x20) - 'a', v->y = *buff - '1';
	else return 1;
	for (const char* p = place; *p; p += 2)
		if (*p - '0' == v->x && p[1] - '0' == v->y)return 0;
	return 2;
}