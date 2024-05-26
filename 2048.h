#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#ifdef _WIN32
    #include<conio.h>
#elif __linux__
    #include <unistd.h>
    #include <termios.h>
#endif

#define size 4


void init_map();
void random_map();
void print_map();
void main_game();

int gameover();
int check();

void up();
void down();
void right();
void left();
void reset();

void clear_screen();
#ifdef __linux__
    int getch();
#endif
void swap(int* a,int* b);

int score;
int map[size][size];