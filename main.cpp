#include "graphics.h"
#include <climits>
#include <queue>
#include<iostream>
#include<stdio.h>
#include<windows.h>
using namespace std;
const int CELL_SIZE = 18;
const int EMPTY = 0;
const int BODY1 = 1;
const int APPLE = 2;
const int WALL = 3;
const int SNOWFLAKE = 4;
const int BOMB=5;
const int BODY2 = 6;
const int HEART=7;
int snakelife=5;
bool isgameover=false;
bool isFireStarted;
int movescore1=0,movescore2=0,eatAppleScore1=0,eatAppleScore2=0;
long long speed1=4000000,speed2=4000000;
int mcolor,color1=YELLOW,freezecolor,color2=LIGHTMAGENTA;
enum Directions1 {UP,DOWN,LEFT,RIGHT};
enum Directions2 {W,S,A,D};
Directions1 snakeDirection1 = DOWN;
Directions2 snakeDirection2 = S;

struct location1
{
    int r;
    int c;
};
struct location2
{
    int r;
    int c;
};

Directions1 fireDirection;
location1 fireLocation;
queue< location1 > snakebody1;
queue< location2 > snakebody2;
int islam[35][45] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,3,3,3,0,3,3,3,0,3,0,0,0,3,3,3,3,0,3,3,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,0,0,3,0,0,0,3,0,0,3,0,3,0,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,3,0,0,3,3,3,0,3,0,0,0,3,0,0,3,0,3,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3,0,3,0,0,0,3,3,3,3,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,3,3,3,0,3,3,3,0,3,3,3,0,3,0,0,3,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,3,3,3,0,3,0,3,3,3,0,3,3,3,3,0,3,0,3,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,3,0,0,0,3,0,3,0,0,0,3,0,0,3,0,3,0,3,0,3,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,3,3,3,0,3,0,3,3,3,0,3,0,0,3,0,3,0,3,0,3,3,3,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,3,0,3,3,3,3,0,0,3,0,0,3,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,3,3,3,0,3,0,3,3,3,0,3,0,0,3,0,0,3,0,0,3,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};
int ahmed[35][45] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,3,3,0,0,3,0,0,3,0,3,3,0,3,3,0,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,3,0,3,0,3,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,3,3,3,3,0,3,3,3,3,0,3,0,0,0,3,0,3,3,3,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,0,0,3,0,3,0,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,0,0,3,0,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,3,3,3,0,0,3,3,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,3,0,0,3,0,3,3,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,3,0,3,3,3,0,0,3,3,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};
int board1[35][45] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};
//----The Functios Of Draw&Erase Every Element----//
void drawWall(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    int right = left + CELL_SIZE;
    int bottom = top + CELL_SIZE;
    setfillstyle(SOLID_FILL,LIGHTRED);
    bar(left, top, right, bottom);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1, NORM_WIDTH);
    line(left+0 ,top+9 ,left+18,top+9);
    line(left+12,top+0 ,left+12,top+9);
    line(left+4 ,top+9 ,left+4 ,bottom);
    line(left ,bottom,right ,bottom);
    line(left ,top ,right ,top);
}
void drawFire(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    readimagefile( "yg.ico",left, top, left +16, top +16 );
}
void eraseFire(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, left+18, top+18);
}
void drawheart(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    readimagefile("heart.ico",left , top, left + 16, top + 16);
}
void eraseheart(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, left+18, top+18);
}
void drawbomb(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    readimagefile("bomb.ico",left , top, left + 16, top + 16);
}
void drawSnow(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    readimagefile("snowflake.ico",left , top, left + 16, top + 16);
}
void drawApple(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    readimagefile("green_apple16.ico",left , top, left + 16, top + 16);
}
void drawempty(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    int right = left + CELL_SIZE;
    int bottom = top + CELL_SIZE;
    setfillstyle(SOLID_FILL,BLACK);
    bar(left, top, right, bottom);
}
void drawSnakeBody1(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, color1 );
    bar(left+1, top+1, left+17, top+17);
}
void eraseSnakeBody1(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, left+18, top+18);
}
void drawSnakeBody2(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, color2 );
    bar(left+1, top+1, left+17, top+17);
}
void eraseSnakeBody2(int row,int col)
{
    int left = col*CELL_SIZE;
    int top = row*CELL_SIZE;
    setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, left+18, top+18);
}
void generatewall(){
for(int i=0;i<=5;i++){
    int r,c;
    do
    {
        r=rand()%35;
        c=rand()%45;
    }

    while(board1[r][c] != EMPTY);
    board1[r][c]= WALL;
    drawWall(r,c);
    }}
//----Functions Of Drawing Screens----//
void drawislam()
{
    for(int row=0; row<35; row++)
    {
        for(int col=0; col<45; col++)
        {
            switch(islam[row][col])
            {

            case WALL:
                drawWall(row,col);
                break;
                case EMPTY :
                drawempty(row,col);
                break;
            }
            setcolor(LIGHTGRAY);
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            settextstyle(BOLD_FONT,HORIZ_DIR,2);
            outtextxy(getmaxx()/2,getmaxy()/6,"Press Enter");
        }
    }
}
void drawahmed()
{
    for(int row=0; row<35; row++)
    {
        for(int col=0; col<45; col++)
        {
            switch(ahmed[row][col])
            {

            case WALL:
				drawempty(row,col);
                drawWall(row,col);
                break;
            case EMPTY :
                drawempty(row,col);
                break;
            }
            setcolor(LIGHTGRAY);
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            settextstyle(BOLD_FONT,HORIZ_DIR,2);
            outtextxy(getmaxx()/2,getmaxy()/6,"Press Enter");
        }
    }
}

void drawMenuBoard()
{
    for(int row=0; row<35; row++)
    {
        for(int col=0; col<45; col++)
        {

            drawWall(row,col);
        }
    }
}
void drawBoard1()
{
    for(int row=0; row<35; row++)
    {
        for(int col=0; col<45; col++)
        {
            switch(board1[row][col])
            {
            case EMPTY :
                drawempty(row,col);
                break;
            case BODY1:
				drawempty(row,col);
                drawSnakeBody1(row,col);
                break;
            case BODY2:
				drawempty(row,col);
                drawSnakeBody2(row,col);
                break;
            case APPLE:
				drawempty(row,col);
                drawApple(row,col);
                break;
            case WALL:
				drawempty(row,col);
                drawWall(row,col);
                break;
            case SNOWFLAKE:
            	drawempty(row,col);
                drawSnow(row,col);
                break;
            case BOMB:
            	drawempty(row,col);
                drawbomb(row,col);
                break;
            case HEART:
				drawempty(row,col);
                drawheart(row,col);
                break;
            }
        }
    }
}
    void MenuBoardSingleorMulti()
    {
        system("cls");
        drawMenuBoard();
        setcolor(WHITE);
        setbkcolor(LIGHTRED);
        settextstyle(BOLD_FONT,HORIZ_DIR, 5);
        outtextxy(425,50,"The Snake Game");
        settextstyle(BOLD_FONT,HORIZ_DIR, 5);
        outtextxy(408,220,"single player Press 1");
        outtextxy(408,320," Multiplayer Press 2");
    }
    void choosesnakecolor()
    {
   	system("cls");
	drawMenuBoard();
	setcolor(WHITE);
	setbkcolor(LIGHTRED);
	settextstyle(BOLD_FONT,HORIZ_DIR, 5);
	outtextxy(425,50,"Choose Snake color");
		setcolor(YELLOW);
	outtextxy(408,220,"Yellow Press 3");
		setcolor(BLUE);
	outtextxy(408,320," Blue Press 4");
		setcolor(GREEN);
	outtextxy(408,420," Green Press 5");
	int colornum;
	colornum =getch();
	while((colornum !=51)&&(colornum !=52)&&(colornum !=53))
    {
    colornum =getch();
    }
    switch(colornum)
    {
	case 51:mcolor=YELLOW;color1=mcolor;break;
	case 52:mcolor=BLUE;color1=mcolor;break;
	case 53:mcolor=GREEN;color1=mcolor;break;}
    }
//----The Functions Of Generating The Things That The Snake Eats----//
void generatebomb()
{
    int r,c;
    do
    {
        r=rand()%35;
        c=rand()%45;
    }

    while(board1[r][c] != EMPTY);
    board1[r][c]= BOMB;
    drawbomb(r,c);

}
void generatesnow()
{
    int r,c;
    do
    {
        r=rand()%35;
        c=rand()%45;
    }

    while(board1[r][c] != EMPTY);
    board1[r][c]= SNOWFLAKE;
    drawSnow(r,c);

}
void generatenextapple()
{
    int r,c;
    do
    {
        r=rand()%35;
        c=rand()%45;
    }while(board1[r][c] != EMPTY);
    board1[r][c]= APPLE;
    drawApple(r,c);
}
//----Function Of Respawn Snake----//
int	tall=eatAppleScore1+2;
void initsnake1()
{
    location1 loc;
    loc.r=15;
    loc.c=15;
    for(int i=0 ; i<=(tall) ; i++)
    {
        snakebody1.push(loc);
        board1[loc.r][loc.c] =1;
        loc.r+=1;
    }
}
void initsnake2()
{
    location2 loc;
    loc.r=15;
    loc.c=35;
    for(int i=0 ; i<=1 ; i++)
    {
        snakebody2.push(loc);
        board1[loc.r][loc.c] =1;
        loc.r+=1;
    }
}
//-----Functions Of Snake Moving-----//
location1 getnextFireLocation()
{
    location1 nextFireLoc = fireLocation;
    switch(fireDirection)
    {
    case UP:
        nextFireLoc.r -=1;
        break;
    case DOWN:
        nextFireLoc.r +=1;
        break;
    case LEFT:
        nextFireLoc.c -=1;
        break;
    case RIGHT:
        nextFireLoc.c +=1;
        break;
    }
    return nextFireLoc;
}
location1 getnexthead1()
{
    location1 head1=snakebody1.back();
    switch(snakeDirection1)
    {
    case UP:
        head1.r -=1;
        break;
    case DOWN:
        head1.r +=1;
        break;
    case LEFT:
        head1.c -=1;
        break;
    case RIGHT:
        head1.c +=1;
        break;
    }
    return head1;
}
location2 getnexthead2()
{
    location2 head2=snakebody2.back();
    switch(snakeDirection2)
    {
    case W:
        head2.r -=1;
        break;
    case S:
        head2.r +=1;
        break;
    case A:
        head2.c -=1;
        break;
    case D:
        head2.c +=1;
        break;
    }
    return head2;
}
void moveandgrowsnake1(location1 nexthead1)
{
    snakebody1.push(nexthead1);
    drawSnakeBody1(nexthead1.r,nexthead1.c);
    board1[nexthead1.r][nexthead1.c] =1;
}
void movesnake1tonextlocation(location1 nexthead1)
{
    snakebody1.push(nexthead1);
    drawSnakeBody1(nexthead1.r,nexthead1.c);
    board1[nexthead1.r][nexthead1.c] =1;

    location1 tail1=snakebody1.front();
    snakebody1.pop();
    eraseSnakeBody1(tail1.r,tail1.c);
    board1[tail1.r][tail1.c] =0;
}
void moveandgrowsnake2(location2 nexthead2)
{
    snakebody2.push(nexthead2);
    drawSnakeBody2(nexthead2.r,nexthead2.c);
    board1[nexthead2.r][nexthead2.c] =1;
}
void movesnake2tonextlocation(location2 nexthead2)
{
    snakebody2.push(nexthead2);
    drawSnakeBody2(nexthead2.r,nexthead2.c);
    board1[nexthead2.r][nexthead2.c] =1;

    location2 tail2=snakebody2.front();
    snakebody2.pop();
    eraseSnakeBody2(tail2.r,tail2.c);
    board1[tail2.r][tail2.c] =0;
}
//----The Function Of Freezing The Snake----//
void freezesnake1()
{
    speed1=11000000;
	freezecolor=LIGHTCYAN;
    color1=freezecolor;
}
void freezesnake2()
{
    speed2=11000000;
    color2=LIGHTCYAN;
}
//----GameOver Function----//
void gameover()
{
    isgameover=true;
    setcolor(WHITE);
    setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(getmaxx()/2,getmaxy()/2,"Game Over");
    char arr[50];
	settextstyle(BOLD_FONT,HORIZ_DIR,5);
    sprintf(arr,"Score1: %d",eatAppleScore1);
    outtextxy(130,50,arr);
}
void gameover1()
{
    isgameover=true;
    setcolor(WHITE);
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(getmaxx()/2,getmaxy()/3,"Snake2 won");
    char as[50];
	settextstyle(BOLD_FONT,HORIZ_DIR,5);
    sprintf(as,"Score2: %d",eatAppleScore2);
    outtextxy(130,100,as);
}
void gameover2()
{
    isgameover=true;
    setcolor(WHITE);
	setbkcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(getmaxx()/2,getmaxy()/3,"Snake1 won");
    char as[50];
	settextstyle(BOLD_FONT,HORIZ_DIR,5);
    sprintf(as,"Score2: %d",eatAppleScore2);
    outtextxy(130,100,as);
    }
//----More Move Snake Functions----//
void movesnake1()
{
    location1 nexthead1 = getnexthead1();
    switch (board1[nexthead1.r][nexthead1.c])
    {
    case EMPTY:
        movesnake1tonextlocation(nexthead1);
        break;
    case APPLE:
        moveandgrowsnake1(nexthead1);
        generatenextapple();
        speed1=4000000;
        color1=mcolor;
        movescore1++;
        eatAppleScore1++;
	if(movescore2==0){
        if(movescore1%4==0 )
        {
            generatesnow();
            movescore1++;
        }
        else if(movescore1%5==0 )
            generatebomb();
}
        break;
    case WALL:
    case BODY1:
    case BODY2:
    case BOMB:
      {
        snakelife--;
		if(movescore2!=0)
        {
		gameover();
		gameover1();
        }
		break;
      }
    case SNOWFLAKE:
        movesnake1tonextlocation(nexthead1);
        freezesnake1();
        break;
    }
}
void movesnake2()
{
    location2 nexthead2 = getnexthead2();
    switch (board1[nexthead2.r][nexthead2.c])
    {
    case EMPTY:
        movesnake2tonextlocation(nexthead2);
        break;
    case APPLE:
        moveandgrowsnake2(nexthead2);
        generatenextapple();
        speed2=4000000;
        color2=LIGHTMAGENTA;
        eatAppleScore2++;
        movescore2++;
         if(movescore2%4==0 )
            generatebomb();
        break;
    case WALL:
    case BODY2:
    case BODY1:
    case BOMB:
        gameover();
        gameover2();
        break;
    }
}
void snakehearts()
{
            switch (snakelife){
		case 5:
			isgameover=false;
			break;
		case 4:
			isgameover=false;
			drawMenuBoard();
			drawBoard1();
			tall=0;
			initsnake1();
			eraseheart(1,3);
			board1[1][3]=EMPTY;
			snakelife--;
			break;
		case 2:
			isgameover=false;
			drawMenuBoard();
			drawBoard1();
			tall=0;
			initsnake1();
			eraseheart(1,2);
			board1[1][2]=EMPTY;
			snakelife--;
			break;
		case 0:
			eraseheart(1,1);
			board1[1][1]=EMPTY;
			gameover();
			break;
            }
   }
//---- The Fire Functions----//
void startFire()
{
    isFireStarted = true;
    fireLocation = getnexthead1();
    fireDirection = snakeDirection1;
    drawFire(fireLocation.r,fireLocation.c);
}
void stopFire()
{
    isFireStarted=false;
    eraseFire(fireLocation.r,fireLocation.c);
	board1[fireLocation.r][fireLocation.c]=EMPTY;
}
void moveFire()
{
    if(isFireStarted)
    {
        location1 nextFireLoc = getnextFireLocation();
        drawFire(nextFireLoc.r,nextFireLoc.c);
        eraseFire(fireLocation.r,fireLocation.c);
		switch(board1[fireLocation.r][fireLocation.c])
		{
         case SNOWFLAKE:
         case BOMB:
            eraseFire(fireLocation.r,fireLocation.c);
			board1[fireLocation.r][fireLocation.c]=EMPTY;
			break;
         case WALL:
			isFireStarted=false;
			break;
        }
    fireLocation = nextFireLoc;
    }
}
//-----Game control functions-----//
void changesnakedirection1(char ch)
{
    switch(ch)
    {
    case KEY_UP:
        snakeDirection1=UP ;
        break;
    case KEY_DOWN:
        snakeDirection1=DOWN ;
        break;
    case KEY_LEFT:
        snakeDirection1=LEFT ;
        break;
    case KEY_RIGHT:
        snakeDirection1=RIGHT ;
        break;
    }
}
void changesnakedirection2(int con)
{
    switch(con)
    {
    case 119:
        snakeDirection2=W ;
        break;
    case 115:
        snakeDirection2=S ;
        break;
    case 97:
        snakeDirection2=A ;
        break;
    case 100:
        snakeDirection2=D ;
        break;
    }
}
	//---------Check Keys Input-----------//
void KEYINPUTTEST()
{
    int key;
    char ch;
    if(kbhit())
    {
        ch = key = getch();
       if(ch==0)
       {
           ch = getch();
           changesnakedirection1(ch);
       }else if((key==97)||(key==100)||(key==115)||(key==119))
              {
                changesnakedirection2(key);
              }else if(key==32)//SpaceBar
                     {
                        if(!isFireStarted)
                            startFire();
                     }

    }
}
//--------Enter&Retry BUTTON----------//
void checkEnterButton()
{
    int button;
    button=getch();
    while(button!=13) //ASCII code for ENTER key is 13
    {
        button=getch();
    }
}
//------------EXIT BUTTON-----------//
void checkExitButton()
{
    int Exit;
    Exit=getch();
    while(Exit!=27)//ASCII code for EXIT key is 27
    {
     Exit=getch();
    }
    closegraph(ALL_WINDOWS);
}
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
void Game()
{
    closegraph(ALL_WINDOWS);
    system("cls");
    snakelife=5;
    board1[1][3]=HEART;
    board1[1][2]=HEART;
    board1[1][1]=HEART;
    eatAppleScore1=0;
    eatAppleScore2=0;
    initwindow(45 * CELL_SIZE, 35 * CELL_SIZE,"Islam ELsayed & Ahmed Adel Snake Game ");
    int levelnum;
    int gametimer=0;
    isgameover=false;
    drawislam();
    checkEnterButton();
    drawahmed();
    checkEnterButton();
	MenuBoardSingleorMulti();
	levelnum = getch();
    while((levelnum !=49)&&(levelnum !=50))
    {
    levelnum =getch();
    }
    switch(levelnum)
    {
    case 49:
		choosesnakecolor();
        drawBoard1();
        initsnake1();
        while(!isgameover)
        {
         if (gametimer==INT_MAX)
                gametimer=0;
         if(gametimer % 500000==0){
            moveFire();}
         if(gametimer%speed1==0)
           {
            movesnake1();
           }
            gametimer++;
            KEYINPUTTEST();
            snakehearts();
         if(movescore2==0){
         if (eatAppleScore1==10)
          {
            eatAppleScore1++;
			generatewall();
          }}

        }
        break;
		case 50:
            drawBoard1();
            board1[1][3]=EMPTY;
            drawempty(1,3);
            board1[1][2]=EMPTY;
            drawempty(1,2);
            board1[1][1]=EMPTY;
            drawempty(1,1);
            mcolor=YELLOW;
            initsnake1();
            initsnake2();
            while(!isgameover)
            {
             if (gametimer==INT_MAX)
                    gametimer=0;
             if(gametimer%speed1==0 && gametimer%speed2==0)
              {
                movesnake2();
                movescore2++;
                movesnake1();
              }
                gametimer++;
                KEYINPUTTEST();
                KEYINPUTTEST();

            if(movescore2!=0)
             {
                if(eatAppleScore1==10)
                 {
                  gameover();
                  gameover2();
                 }else if(eatAppleScore2==10)
                        {
                        gameover();
                        gameover1();
                        }
             }
            }
            break;
    }
		setcolor(WHITE);
        setbkcolor(BLACK);
        settextstyle(BOLD_FONT,HORIZ_DIR, 3);
        outtextxy(400,350,"Retry:'Enter' ");
		outtextxy(400,370,"EXIT:'ALT + ESC' ");
        checkEnterButton();
        return;
        checkExitButton();

    while(! kbhit());
    closegraph( );
}
int main()
{
    while(1)
    {
        Game();
    }
}
