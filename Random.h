//
//  Random.h
//  MAZEGAME
//
//  Created by nieaowei on 2019/1/10.
//  Copyright © 2019 nieaowei. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
struct Random{
	int *Storage;//������洢����
	int (*Num)();//�������
	//void (*StorageArray)();
}Random;

void InitiRandom(int num);//��ʼ���������
int RandomNum(int start,int end,int edge_num);//�������
//void StorageArray(int num);