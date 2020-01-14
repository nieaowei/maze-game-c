//
//  Game_Core.h
//  MAZEGAME
//
//  Created by nieaowei on 2019/1/10.
//  Copyright © 2019 nieaowei. All rights reserved.
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
//λ����,��Ԫһά����
typedef struct Place{
	int x;//λ��
	int y;//λ��
}Place;
//��ɫ��
typedef struct Role{
	char Char;//��ɫ�ַ�
	int x,y;//��ɫ��ǰλ��
	void (*Move)();//�ƶ�
}Role;
//ͼ��
typedef struct Graph{
	int Vex_Num;//ͼ�Ķ�����
	int Ege_Num;//ͼ�ı���
	int **Array;//ͼ���ڽӾ���
}Graph;
//��ͼ��
typedef struct Map{
	int **Array;//��ͼ����
	Place *VexPlace;//��ͼ������λλ�þ���
	Place *EgePlace;//��Ԫһά���󣬴洢�ߵ�����
	int m,n;//��ͼ��m,n����
	//void (*CreateVexPlace)();
	//void (*CreateArray)();
}Map;
//��Ϸ��
struct Game{
	int m,n;//m��n��
	Map Map;//��Ϸ��ͼ
	Graph Graph;//��Ϸ��ͼ���ɸ���ͼ
	Role Role;//��Ϸ��ɫ
	void (*Start)();//��Ϸ����
	void (*Initi)();//��Ϸ��ʼ��
	void (*Repaint)();//��ͼ�ػ�
	void (*Control)();//��Ϸ����
}Game;
/*
��ͼ���
*/
Place *CreateArrayXY(int lenth);//������Ԫһά����
void InitiGame();//��Ϸ��ʼ��
void InitiGraph();//ͼ��ʼ��
void Repaint(Map map);//�ػ��ͼ
void CreateMap(int m,int n);//����m��n�еĵ�ͼ
void CreateGraph(int m,int n);//����mn��mn�е�ͼ
void CreateArray_F(int m,int n);//������ͼ��λ��������
int ** Create_Array(int m,int n);//����m��n�еĶ�ά���飬�����ظ�����ָ��
Place *Prim_ArrayXY(Graph G,int index);//����ķ�㷨�����ض�Ԫһάλ�þ���
int Min_ArrayXY(Place *ArrayAL,int lenth,char opt,int opt1);//����������Ԫ������Сֵ�㷨
/*
�������
*/
void printxy(Place *place,int lenth);//�����Ԫһά����
void print(int **p,int m,int n);//��ӡ��ά����
/*
��ɫ�������
*/
void Control();//
void Move(void (*p)());//*p ���ƣ����ƣ����ƣ�����
void Left();//����
void Right();//����
void Up();//����
void Down();//����
int OrEnd(Role role,Map map);//

#endif /* Game_Core_h */
