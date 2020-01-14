//
//  Game_Core.c
//  MAZEGAME
//
//  Created by nieaowei on 2019/1/10.
//  Copyright 漏 2019 nieaowei. All rights reserved.
//

#include "Game_Core.h"
//打印二元一维矩阵
void printxy(Place *place,int lenth){
	//int lenth=(sizeof(place)/sizeof(place[0])+1);
	int i;
	for(i=0;i<lenth;i++){
		printf("(%d,%d) ",place[i].x,place[i].y);}
	printf("\n");
}
//
void Control(Role role){
		char ch;
		ch=getch();
	//	printf("%c",ch);
		switch(ch)
		{
		case 'w' :role.Move(Up);break;
	//	case 72:role.Move(Up);break;
	//	case 80:role.Move(Down);break;
	//	case 75:role.Move(Left);break;
	//	case 77:role.Move(Right);break;
		case 's' :role.Move(Down);break;
		case 'a' :role.Move(Left);break;
		case 'd' :role.Move(Right);break;
		case 27: Main();break;
		}
}
void Left(){
	if(Game.Map.Array[Game.Role.x][Game.Role.y-1]==ROAD) Game.Role.y-=1;
}
void Right(){
	if(Game.Map.Array[Game.Role.x][Game.Role.y+1]==ROAD||Game.Map.Array[Game.Role.x][Game.Role.y+1]==END) Game.Role.y+=1;
}
void Up(){
	if(Game.Map.Array[Game.Role.x-1][Game.Role.y]==ROAD) Game.Role.x-=1;
}
void Down(){
	if(Game.Map.Array[Game.Role.x+1][Game.Role.y]==ROAD) Game.Role.x+=1;
}

void Move(void (*p)()){
	p();
}
//创建二元一维矩阵
Place *CreateArrayXY(int lenth){
	Place *ArrayXY=(Place *)malloc(lenth*sizeof(Place));
	return ArrayXY;
}
//普利姆算法，返回二元一维矩阵
Place *Prim_ArrayXY(Graph G,int index){
	int i,j,k,q;
	Place *ArrayAL=CreateArrayXY(G.Vex_Num);
	Place *ArrayXY=CreateArrayXY(G.Vex_Num-1);
	k=index;
	for(i=0;i<G.Vex_Num;i++){
		if(i!=k) {
			ArrayAL[i].x=k;
			ArrayAL[i].y=G.Array[k][i];
		}
	}
	ArrayAL[k].y=0;
	for(i=1,j=0;i<G.Vex_Num;i++,j++){
		//printxy(ArrayAL,G.Vex_Num);//调试输出
		k=Min_ArrayXY(ArrayAL,G.Vex_Num,'y',2);
	//	print(Game.Graph.Array,9,9);//调试输出
	//	printf("%d\n",k);//调试输出
		ArrayXY[j].x=ArrayAL[k].x;
		ArrayXY[j].y=k;
	//	printf("(%d,%d)\n",ArrayXY[j].x,ArrayXY[j].y);//调试输出
		ArrayAL[k].y=0;
		for(q=0;q<G.Vex_Num;q++){
			if(G.Array[k][q]<ArrayAL[q].y){
				ArrayAL[q].x=k;
				ArrayAL[q].y=G.Array[k][q];
			}
		}
	}
	//	printxy(ArrayXY,G.Vex_Num-1);//调试输出

	return ArrayXY;
}
//二元一维数组求单元的最小值,opt1选择返回值1或位序2
int Min_ArrayXY(Place *ArrayAL,int lenth,char opt,int opt1){
	int i;
    int min=MAXINT,locate=-1;
	if(opt=='x'){
		for (i=0; i<lenth; i++) {
			if(min>ArrayAL[i].x) {
				min=ArrayAL[i].x;
				locate=i;
			}
		}
	}else if(opt=='y'){
		for (i=0; i<lenth; i++) {
			if(min>ArrayAL[i].y&&ArrayAL[i].y!=0) {
				min=ArrayAL[i].y;
				locate=i;
			}
		}
	}
	if(opt1==1)
			return min;
		else if(opt1==2)
			return locate;
		return 0;
}
//地图重绘
void Repaint(Map map){
	int i,j;
	system("cls");
	for(i=0;i<map.m;i++){
		for(j=0;j<map.n;j++){
			if(i==Game.Role.x&&j==Game.Role.y){
				printf("%c%c",Game.Role.Char,Game.Role.Char);
				continue;
			}else{
				switch(map.Array[i][j]){
				case WALL:  
					PaintWall;
					break;
				case ROAD:
					PaintRoad;
					break;
				case START:
					printf("入");
					break;
				case END:
					printf("出");
					break;
			}}
		}
		printf("\n");
	}

}
//创建二维矩阵并返回
int ** Create_Array(int m,int n){
	int **Map=(int **)malloc(sizeof(int *) * m);
	int i;
	for(i=0; i<m; i++)	
	{
		Map[i] = (int *)malloc(sizeof(int) * n); //分配每个指针所指向的数组
	}
	return Map;
}
//生成地图
void CreateMap(int m,int n){
	Game.Map.Array=Create_Array(m+m+1,n+n+1);
	Game.Map.VexPlace=CreateArrayXY(m*n);//创定位位置矩阵
	//Game.Map.EgePlace=CreateArrayXY(m*n-1);
	Game.Map.m=m+m+1;
	Game.Map.n=n+n+1;
}
//创建地图定位辅助矩阵
void CreateArray_F(int m,int n){
	int i,j,l;
	Place *Array;
	Array=CreateArrayXY(m*n);
	for(i=0,l=0;i<m;i++){
		for(j=0;j<n;j++,l++){
			Array[l].x=i;
			Array[l].y=j;
		}
	}
	for(i=1,l=0;i<=m;i++){
		for(j=1;j<=n;j++,l++){
			Game.Map.VexPlace[l].x=Array[l].x+i;
			Game.Map.VexPlace[l].y=Array[l].y+j;
		}
	}
	//printxy(Array,m*n);
	
}

//创建图矩阵
void CreateGraph(int m,int n){
	Game.Graph.Array=Create_Array(m*n,m*n);
	Game.Graph.Vex_Num=m*n;
	Game.Graph.Ege_Num=2*m*n-m-n;
}
//初始化随机权值图
void InitiGraph(int m,int n){
	int i,j;
	CreateGraph(m,n);
	InitiRandom(Game.Graph.Ege_Num);
	for(i=0;i<Game.Graph.Vex_Num;i++){
		for(j=0;j<Game.Graph.Vex_Num;j++){
			Game.Graph.Array[i][j]=MAXINT;
		}
	}
	for(i=0,j=0;i<Game.Graph.Vex_Num-1;i++){
		if((i+1)%Game.n==0) {
			Game.Graph.Array[i][i+n]=Random.Num(1,Game.Graph.Ege_Num,Game.Graph.Ege_Num);
			Game.Graph.Array[i+n][i]=Game.Graph.Array[i][i+n];
			//printf("%d\n",Game.Graph.Array[i][i+n]);//调试输出
			
		}
		else if(i>=((Game.m*Game.n)-Game.n)&&i<(Game.Graph.Vex_Num-1)) {
			Game.Graph.Array[i][i+1]=Random.Num(1,Game.Graph.Ege_Num,Game.Graph.Ege_Num);
			Game.Graph.Array[i+1][i]=Game.Graph.Array[i][i+1];
			//printf("%d\n",Game.Graph.Array[i][i+1]);//调试输出
		}
		else {
			Game.Graph.Array[i][i+n]=Random.Num(1,Game.Graph.Ege_Num,Game.Graph.Ege_Num);
			Game.Graph.Array[i+n][i]=Game.Graph.Array[i][i+n];
			Game.Graph.Array[i][i+1]=Random.Num(1,Game.Graph.Ege_Num,Game.Graph.Ege_Num);
			Game.Graph.Array[i+1][i]=Game.Graph.Array[i][i+1];
		//	printf("%d\n",Game.Graph.Array[i][i+n]);//调试输出
		//	printf("%d\n",Game.Graph.Array[i][i+1]);//调试输出
		}
	}
}
//初始化地图
void InitiMap(int m,int n){
	int i,j;
	CreateMap(m,n);//创建地图
	CreateArray_F(m,n);//生成定位矩阵
//	printxy(Game.Map.VexPlace,m*n);
	Game.Map.EgePlace=Prim_ArrayXY(Game.Graph,0);//边，二元一维矩阵
//	printxy(Game.Map.EgePlace,m*n-1);
	for(i=0;i<Game.Map.m;i++){
		for(j=0;j<Game.Map.n;j++){
			Game.Map.Array[i][j]=WALL;
		}
	}
	Game.Map.Array[1][0]=START;
	Game.Map.Array[Game.Map.m-2][Game.Map.n-1]=END;
	for(i=0;i<Game.Map.m-1;i+=2){
		for(j=0;j<Game.Map.n-1;j+=2){
			Game.Map.Array[i+1][j+1]=ROAD;
		}
	}
	//print(Game.Map.Array,Game.Map.m,Game.Map.n);//调试输出
	//print(Game.Graph.Array,m*n,m*n);//调试输出
	i=0,j=0;
	//printf("%d",Game.Map.VexPlace[0].x);
	for(i=0;i<Game.Graph.Vex_Num-1;i++){
		//printf("%d",Game.Map.EgePlace[i].x);
		if(Game.Map.VexPlace[Game.Map.EgePlace[i].x].x==Game.Map.VexPlace[Game.Map.EgePlace[i].y].x){
			if(Game.Map.VexPlace[Game.Map.EgePlace[i].x].y>Game.Map.VexPlace[Game.Map.EgePlace[i].y].y){
				Game.Map.Array[Game.Map.VexPlace[Game.Map.EgePlace[i].x].x][Game.Map.VexPlace[Game.Map.EgePlace[i].x].y-1]=ROAD;
			}else
				Game.Map.Array[Game.Map.VexPlace[Game.Map.EgePlace[i].x].x][Game.Map.VexPlace[Game.Map.EgePlace[i].y].y-1]=ROAD;
		}
		else if(Game.Map.VexPlace[Game.Map.EgePlace[i].x].y==Game.Map.VexPlace[Game.Map.EgePlace[i].y].y){
			if(Game.Map.VexPlace[Game.Map.EgePlace[i].x].x>Game.Map.VexPlace[Game.Map.EgePlace[i].y].x){
				Game.Map.Array[Game.Map.VexPlace[Game.Map.EgePlace[i].x].x-1][Game.Map.VexPlace[Game.Map.EgePlace[i].x].y]=ROAD;
			}else
				Game.Map.Array[Game.Map.VexPlace[Game.Map.EgePlace[i].y].x-1][Game.Map.VexPlace[Game.Map.EgePlace[i].y].y]=ROAD;
		}
		//	printf(" ");
			
	}
	//print(Game.Graph.Array,m*n,m*n);//调试输出
	//printxy(Game.Map.VexPlace,m*n);
//	print(Game.Map.Array,Game.Map.m,Game.Map.n);//调试输出
//	printxy(Game.Map.EgePlace,m*n-1);
}
//如果角色位置值等于end游戏结束
int OrEnd(Role role,Map map){
	if(map.Array[role.x][role.y]==END)
		return 1;
	else return 0;
}
//初始化游戏
void InitiGame(){
	//printf(请根据您的屏幕大小输入合适的);
	printf("请输入行数(M):");
	scanf("%d",&Game.m);
	printf("请输入列数(N):");
	scanf("%d",&Game.n);
//	Game.m=3;
//	Game.n=3;
	Game.Role.Char=(char)(001);
	Game.Role.x=1;
	Game.Role.y=0;
	Game.Repaint=Repaint;
	Game.Role.Move=Move;
	InitiGraph(Game.m,Game.n);
	InitiMap(Game.m,Game.n);
	Game.Repaint(Game.Map);
//	printf("%d",Game.m);
}

//输出二维矩阵
void print(int **p,int m,int n){
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("%d ",p[i][j]);
		}
		printf("\n");
	}
}