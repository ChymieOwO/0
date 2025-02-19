#include <stdio.h>
#include <stdlib.h>
#define ROW 8
#define COL 8
int count_access = 1;//使用全局变量以应对多条通路的情况

void PrintLaby(int *Laby,int row,int col)
{
    for(int i = 0;i < row;i++)
    {
        for(int j = 0 ; j < col ; j++)
        {
            if(*(Laby+i*col+j)==2)
            printf("X ");
            else
            printf("%d ", *(Laby+i*col+j));//Laby[i][j] = *(Laby+i*col+j)
        }
        printf("\n");
    }
}

void LabyBackTracing(int *Laby,int row,int col,int out_row,int out_col,int* find)
{
    if(*(Laby+row*COL+col)==1)
    {
        printf("输入的坐标点存在阻碍，");
        return ;
    }
    *(Laby+row*COL+col)=2;
    if(row == out_row && col == out_col)
    {
        printf("找到通路%d:\n",count_access);
        PrintLaby(Laby,ROW,COL);
        *find = 1;
        count_access++;
        return ;//此时的row,col即为终点，可以直接退出
    }
    if(TestMove(Laby,row+1,col))//尝试向下移动
    {
        LabyBackTracing(Laby,row+1,col,out_row,out_col,find);
        *(Laby+(row+1)*COL+col)=0;//如果走入了死路则将其还原
    }
    if(TestMove(Laby,row-1,col))//尝试向上移动
    {
        LabyBackTracing(Laby,row-1,col,out_row,out_col,find);
        *(Laby+(row-1)*COL+col)=0;
    }
    if(TestMove(Laby,row,col-1))//尝试向左移动
    {
        LabyBackTracing(Laby,row,col-1,out_row,out_col,find);
        *(Laby+row*COL+col-1)=0;
    }
    if(TestMove(Laby,row,col+1))//尝试向右移动
    {
        LabyBackTracing(Laby,row,col+1,out_row,out_col,find);
        *(Laby+row*COL+col+1)=0;
    }
}

int TestMove(int *Laby,int row,int col)
{
    if(row<ROW && row>=0 && col<COL && col>=0 )
    {
        return (*(Laby + row*COL + col) == 0);
    }
    else
    return 0;
}

int main()
{
    int find=0;
    int *p_find;
    int Laby[ROW][COL]=
    {
        {0,0,0,0,0,0,1,0},
        {0,1,1,0,1,0,0,0},
        {0,1,1,0,1,1,1,0},
        {0,0,1,0,0,0,1,0},
        {1,0,1,1,1,0,1,0},
        {0,0,1,1,0,0,1,0},
        {1,0,0,0,0,1,1,0},
        {0,1,1,1,0,0,0,0}
    };
    int *p = (int*)Laby;
    int x=1,y=1;
    p_find=&find;
    /*srand(time(NULL));
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL ; j++)
        {
            Laby[i][j]=(rand()%2);
        }
    }*/
    printf("迷宫已生成，0表示通路，1表示阻碍\n");
    PrintLaby(p,ROW,COL);
    printf("请输入入口的坐标，格式为(a,b)，最左上角点的坐标为(1,1)\n");
    scanf("(%d,%d)",&y,&x);
    LabyBackTracing(p,x-1,y-1,ROW-1,COL-1,p_find);
    if(find == 0)
    {
        printf("无法找到路线。");
    }
    return 0;
}