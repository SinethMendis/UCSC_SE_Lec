#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define RAND (rand() % 6 + 1)
#define BASE -1
#define X 0

struct pieces {
    char color[10];
    char colorId;
    int pieceId;
    int roll;
    int position;
    int map;
};
