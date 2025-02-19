# 2025-02-19 11:36    

# 领接矩阵MGrphy设计思路    
*** 
## 1. 首先定义邻接矩阵

+ 邻接矩阵是一种表示图的方式,使用一个二维数组来存储图中顶点的关系
  >  A --10-- B 
  >  |        |
  >  5        15
  >  |        |
  >  C --20-- D
+ 如果顶点x和顶点y之间有边,则用矩阵元素matrix[x][y]存储这边的权值
+ 如果顶点x和y之间没有边,则用矩阵元素matrix存储INFINTY(无穷大)    
+ 对角线矩阵元素matrix[x][y]通常存储0
  > A   0   10    5    ∞
  > B  10    0    ∞   15
  > C   5    ∞    0   20
  > D   ∞   15   20    0
+ 代码结构
```c
#define MAXVEX  100
#define INFINTY  65535
typedef int Status  //函数返回的状态
typedef char VertexType //顶点类型
typedef int EdgeType  //边上的权值类型应由用户定义
typedef struct {
  VertexType vexs[MAXVEX];
  EdgeType  arc[MAXVEX][MAXVEX];
  int numNodes, numEdges; //图中当前顶点和边数
}MGraph;
```
***
## 2. 创建邻接矩阵CreateMGraph

1.  输入图的基本信息
```c
printf("输入当前顶点和边数\n");
scanf("%d,%d",G->numNodes,G->numEdges);
```
2.  输入顶点信息
```c
for(i = 0; i<MAXVEX;  i++)
   scanf("%d,",G->vexs[i]);
```
3. 初始化一个邻接矩阵,为INFINTY
```c
for(int i = 0; i < G->numNodes; i++)
    for(int j = 0; j < G->numNodes; j++)
    G->arc[i][j] = INFINTY;

```
4. 构建领接矩阵,确定每个顶点的距离
```c
  int i, j , k, w;
  for(int k = 0; k < G->numEdges;k++){
    scanf("%d,%d,%d",&i,&j,&w);
    G->arc[i][j] = w;//顶点的权值
    G->arc[j][i] = w;//正反邻接顶点权之一样
  }
```
***


