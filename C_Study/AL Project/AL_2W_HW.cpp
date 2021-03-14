#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAZE_SIZE	19
#define MOUSE		43

#define UP			1
#define RIGHT		2
#define DOWN		4
#define LEFT		8

int* rec;
int sx = MAZE_SIZE - 1;
int sy = MAZE_SIZE - 2;

int maze[MAZE_SIZE][MAZE_SIZE] =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
{1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
{1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
{1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1},
{1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
{1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
{1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
{1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1},
{1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
{1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
{1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
{1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
{1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void record(int x, int y) {
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}

void delay(int n) {
	for(int i = 0; i < n*100000; i++){}
}

void forward(int* x, int* y, int dir) {
	gotoxy(*x + 1, *y + 1);
	_putch(' ');

	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;

	record(*x, *y);
	gotoxy(*x + 1, *y + 1);
	_putch(MOUSE);
}

int still_in_maze(int x, int y) {
	if (x > 0 && y > 0 && x < MAZE_SIZE - 1 && y < MAZE_SIZE - 1) return 1;
	else return 0;
}

int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir) {
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;
	return m[y][x];
}

void right(int* dir) {
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}

void left(int* dir) {
	*dir >>= 1;
	*dir = (*dir == 0) ? LEFT : *dir;
}

void show() {
	int x, y;
	for (y = 0; y < MAZE_SIZE; y++) {
		if (y == 0) gotoxy(0, 1);
		for (x = 0; x < MAZE_SIZE; x++) {
			if (x == 0) printf(" ");
			if (maze[y][x] == 1) printf("#");
			else printf(" ");
		}
		printf("\n");
	}
}

void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir) {
	show();
	gotoxy(x + 1, y + 1);
	_putch(MOUSE);
	forward(&x, &y, dir);
	while (still_in_maze(x, y)) {
		delay(1000);
		right(&dir);
		while (wall_ahead(maze, x, y, dir)) left(&dir);
		forward(&x, &y, dir);
	}
	record(-1, -1);
}

int del_path(int i, int j) {
	int k = i;

	while (rec[j] >= 0) rec[i++] = rec[j++];
	rec[i] = -1;

	return k;
}

void shortest_path() {
	int i = 0, j, x, y;
	while (rec[i] >= 0) {
		j = i + 2;
		while (rec[j] >= 0) (rec[i] == rec[j])&&(rec[i+1] == rec[j+1]) ? j = del_path(i, j) + 2 : j += 2;
		i += 2;
	}
	i = 0;
	while (rec[i] >= 0) {
		x = rec[i++];
		y = rec[i++];
		gotoxy(x + 1, y + 1);
		_putch(MOUSE);
		delay(1000);
		gotoxy(x + 1, y + 1);
		_putch(' ');
	}
}

void main() {
	delay(20000);
	rec = (int*)calloc(MAZE_SIZE * MAZE_SIZE, sizeof(int));
	right_hand_on_wall(maze, sx, sy, LEFT);
	shortest_path();
	free(rec);
}