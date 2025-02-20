# 2025-02-20 16:07
# CreateALGraph.c邻接表的创建解析
***
##  首先分析ALGraph的定义
+  邻接表是一种图的存储方式,他结合了数组和链表的优点,每个顶点对应一个链表,链表中存储了和该顶尖相邻的所有顶点
***
## ALGraph数据结构组成
1.  顶点表:一个数组,存储所有顶点
```c
#define MAXVEX 100
typedef char VertexType //顶尖类型
typedef int EdgeType  //边上的权值类型

typedef struct VertexNode
{
  VertexType data;
  EdgeType *firstedge;
}VertexNode, AdjList[MAXVEX];
```
2.  边表:每个顶点对应一个链表,存储该顶点相连的边
```c
typedef struct EdgeNode
{
  int adjvex;
  EdgeType  info;
  struct EdgeNode *next;
}EdgeNode;
```
3.  邻接表所用到的配置
```c
typedef structh
{
  AdjList adjlist;
  int numNodes,numEdges;
}GraphAdjList;
```
***
##  创建过程
1.  初始化阶段
  + 输入图的基本信息(顶点数和边数量)
  ```c
GraphAdjList g;
GraphAdjList *G = &g;
EdgeNode *e;
printf("input Edgenum and Vertexnum");
scanf("%d,%d",&G->numNodes,&G->numEdges);//输入邻接表的边数和顶点数
```
  + 创建顶点表,存储哥哥顶点的信息
  + 将每个顶点的边表初始化为NULL
  ```c
for(i = 0; i< G->numNodes;i++)
{
  scanf("%d",&G->adjList[i].data);
  G->adjlist[i].firstedge = NULL;
}//先初始化每个顶点;
```
2. 构建边的关系
  + 输入每个顶点所连接的边
  + 采用头插法插入新边这样输入效率最高,
  + 因为是无向图,每次都要存储两次
```c
int i,j,k;
for(int k = 0; k < G->numEdges; k++)
{
    printf("input Edge(vi,vj) numbers");
    scanf("%d,%d",&i,&j);
  e = (EdgeNode*)malloc(sizeof(EdgeNode));
  e->adjList = j;
  e->next = G->AdjList[i].firstedge;
  G->adjlist[i].firstedge = e;

  e = (EdgeNode*)malloc(sizeof(EdgeNode));
  e->adjList = i;
  e->next = G->AdjList[j].firstedge;
  G->adjlist[j].firstedge = e;
}
```
***





