//
//  Game_Core.h
//  MAZEGAME
//
//  Created by nieaowei on 2019/1/10.
//  Copyright 漏 2019 nieaowei. All rights reserved.
//
//

#ifndef Game_Core_h
#define Game_Core_h

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Random.h"

#define WALL_LEFT 0xa8
#define WALL_RIGHT 0x80
#define PaintWall printf("%c%c",WALL_LEFT,WALL_RIGHT);
#define PaintRoad printf("  ");
#define WALL 0
#define ROAD 1
#define START 3
#define END 4
#define MAXINT 32767

#define new(type,n) (type)malloc(n*sizeof(type))

//extern Random;
//位置类,二元一维数组
typedef struct Place{
	int x;//位置
	int y;//位置
}Place;
//角色类
typedef struct Role{
	char Char;//角色字符
	int x,y;//角色当前位置
	void (*Move)();//移动
}Role;
//图类
typedef struct Graph{
	int Vex_Num;//图的顶点数
	int Ege_Num;//图的边数
	int **Array;//图的邻接矩阵
}Graph;
//地图类
typedef struct Map{
	int **Array;//地图矩阵
	Place *VexPlace;//地图辅助定位位置矩阵
	Place *EgePlace;//二元一维矩阵，存储边的两点
	int m,n;//地图的m,n行列
	//void (*CreateVexPlace)();
	//void (*CreateArray)();
}Map;
//游戏类
struct Game{
	int m,n;//m行n列
	Map Map;//游戏地图
	Graph Graph;//游戏地图生成辅助图
	Role Role;//游戏角色
	void (*Start)();//游戏启动
	void (*Initi)();//游戏初始化
	void (*Repaint)();//地图重绘
	void (*Control)();//游戏控制
}Game;
/*
地图相关
*/
Place *CreateArrayXY(int lenth);//创建二元一维矩阵
void InitiGame();//游戏初始化
void InitiGraph();//图初始化
void Repaint(Map map);//重绘地图
void CreateMap(int m,int n);//生成m行n列的地图
void CreateGraph(int m,int n);//生成mn行mn列的图
void CreateArray_F(int m,int n);//创建地图定位辅助矩阵
int ** Create_Array(int m,int n);//创建m行n列的二维数组，并返回该数组指针
Place *Prim_ArrayXY(Graph G,int index);//普利姆算法，返回二元一维位置矩阵
int Min_ArrayXY(Place *ArrayAL,int lenth,char opt,int opt1);//普利辅助二元数组最小值算法
/*
调试相关
*/
void printxy(Place *place,int lenth);//输出二元一维矩阵
void print(int **p,int m,int n);//打印二维数组
/*
角色控制相关
*/
void Control();//
void Move(void (*p)());//*p 左移，右移，上移，下移
void Left();//左移
void Right();//右移
void Up();//上移
void Down();//下移
int OrEnd(Role role,Map map);//

#endif /* Game_Core_h */
