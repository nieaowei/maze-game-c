//
//  Random.h
//  MAZEGAME
//
//  Created by nieaowei on 2019/1/10.
//  Copyright 漏 2019 nieaowei. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
struct Random{
	int *Storage;//随机数存储数组
	int (*Num)();//随机函数
	//void (*StorageArray)();
}Random;

void InitiRandom(int num);//初始化随机数类
int RandomNum(int start,int end,int edge_num);//随机函数
//void StorageArray(int num);