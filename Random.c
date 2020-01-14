//
//  Ranodom.c
//  MAZEGAME
//
//  Created by nieaowei on 2019/1/10.
//  Copyright 漏 2019 nieaowei. All rights reserved.
//
#include "Random.h"

int RandomNum(int start,int end,int edge_num){
	static int rj=0;
	int i,n;
	srand((unsigned int)(rand()*time(NULL)));
	if(start==0)
		n=rand();
    else
	    n=rand()%end+start;
	for(i=0;i<edge_num;i++){
		if(Random.Storage[i]==n) return n=rand()%end+start;	
	}
	Random.Storage[rj]=n;
	//printf("%d\n",Random.Storage[j]);//调试输出
	rj=(rj+1)%edge_num;//静态变量初始化
	return n;
}

void InitiRandom(int num){
	int i;
	Random.Num=RandomNum;
	Random.Storage=(int *)malloc(num*sizeof(int));
	for(i=0;i<num;i++) Random.Storage[i]=0;
}