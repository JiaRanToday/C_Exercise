#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define SIZE (sizeof(set) / sizeof(set[0]))
/******************集合的概念**********************/
// set:一些确定的对象或者事物
int set[SIZE] = {1, 2, 3};
// element: 集合中的元素
int a = set[0];
int b = set[1];
int c = set[2];
// element和set的关系 属于 不属于
bool elementIsbelongSet(int element, int *set, int size) {

  if (set == NULL) {
    printf("set is NULL");
    return false;
  }
  for (int i = 0; i < size; i++) {
    if (element == set[i]) {
      return true;
      printf("a belong the set\r\n");
    } else if (element != set[i]) {
      printf("a not belong the set\r\n");
      return false;
    }
  }
}
// 按照SIZE是否有穷分为 有穷和无穷
/******************集合的概念**********************/

/*******************集合的表示方法*****************/
// 列举法

int set2[SIZE] = {1, 3, 5, 7, 9};

// 描述法
// z这个函数会返回一个{a | 1 <= a <= 9, a为奇数} 关于a可能性的集合
int *descriptionFunction(int set[]) {
  srand(time(NULL)); // 以当前时间为随机种子
  int set[] = {0};   // 初始化一个集合
  bool flag = true;

  for (int i = 0; i < 9; i++) {
    int x = 1 + rand() % 10; // 生成一个符合1<= x <= 9属于该集合随机数

    if ((x >= 1 && x <= 9) && (x % 2 == 1)) // 如果满足 1 <= x <= 9 且 为基数
    {
      printf("x满足集合的所要求的范围\r\n");
      int j = i;
      while (--j && flag == true) // 集合中的元素要求没有重复
      {
        if (set[j] == x) {
          flag = false;
          break;
        }
        flag = true;
      }

      if (flag == true) {
        printf("x在集合中是唯一的\r\n");
        printf("把x加入集合\r\n");
        set[i] = x;
      }
    }
  }
  int count = 0;
  while (count++ < 9) {
    printf("set[%d] = %d\r\n", count - 1, set[count - 1]);
  }
  return set;
}

/*******************集合的表示方法*****************/
/*********************一些通用集合表示方法**********/
// 自然数
// 下面函树可以打印count个自然数序列
void normalNum(int count) {
  unsigned int N = 0;
  while (count--) {
    printf("自然数 N集合 N = { %u", N++);
  }
}

// 实数
// 下面这个函数可以判断是否是实数 R R+ R- R*
enum NUMRETRURN {
  NOTREALNUM = -2 NEGATIVE = -1,
  ZERO = 0,
  POSITIVE = 1,
} NUMRETRURN;
NUMRETRURN isReadNum(double realnum) {
  if (isfinite(realnum)) {
    if (realnum > 0) {
      printf("rrealnum是一个正实数");
      return POSITIVE;
    } else if (realnum < 0) {
      printf("rrealnum是一个正实数");
      return NEGATIVE;
    }
    return ZERO;
  }
  return NOTREALNUM;
}
// isfinite函数可以判断一个浮点型函数是否是一个有限的实数
// Z是整数
bool is_integer(double num) {
  // 使用 floor() 或 ceil() 判断
  return (num == floor(num));
}
// floor函数返回小于等于num的最大整数值如果num本身是整数,floor则返回真

/*********************一些通用集合表示方法**********/
/***********************子集************************/
// a is belong A
// 判断集合A是否包含元素a
bool contains(int arr[], int size, int a) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == a) {
      return true; // 如果找到了a，返回true
    }
  }
  return false; // 如果没有找到a，返回false
}
// A is contained B
// B contains A

// 判断集合A是否包含于集合B
bool isContainedIn(int A[], int sizeA, int B[], int sizeB) {
  for (int i = 0; i < sizeA; i++) {
    if (!contains(B, sizeB, A[i])) {
      return false; // 如果A中的某个元素不在B中，返回false
    }
  }
  return true; // A中的所有元素都在B中，返回true
}

/*
 * 集合 C 中存储的是其他集合：
 * 也就是说，集合 C 是一个包含集合的集合（集合的集合），
 * 而我们需要判断集合 A 是否是 C 中的一个元素。
 * 集合 C 中存储的是元素而不是集合：
 * 在这种情况下，
 * 我们只能判断集合 A 中的元素是否都属于集合 C
 * （即检查集合 A 是否是集合 C 的子集）。
 * */
// 判断集合A是否等于集合B
bool isEqual(int A[], int sizeA, int B[], int sizeB) {
  if (sizeA != sizeB) {
    return false; // 大小不同，直接返回false
  }

  for (int i = 0; i < sizeA; i++) {
    bool found = false;
    for (int j = 0; j < sizeB; j++) {
      if (A[i] == B[j]) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false; // 如果A中的某个元素不在B中，返回false
    }
  }

  return true; // A和B相等
}

// 判断集合A是否属于集合C（C是集合的集合）
bool isContainedInSetOfSets(int C[][3], int sizeC, int A[], int sizeA) {
  for (int i = 0; i < sizeC; i++) {
    if (isEqual(C[i], 3, A, sizeA)) {
      return true; // 如果C中有一个集合与A相等，返回true
    }
  }
  return false; // 没有找到相等的集合，返回false
}

bool isAequalB(int A[], int sizeA, int B[], int sizeB) {
  if (!(sizeA == sizB)) {
    printf("ABC长度不等必然不等") return false;
  }
  if (isContainedIn(A, sizeA, B, sizeB) & isContainedIn(B, sizeB, A, sizeA)) {
    return true;
  }
  return false;
}

bool isEmptySet(int A[], int sizeA) {
  if (sizeA == 0) {
    printf("是空集\r\n");
    return true;
  }
  return false;
}

/***********************子集************************/
/************************子集的运算*****************/
int *setAnd(int A[], int sizeA, int B[], int sizeB, int *sizeC) {
  *sizeC = sizeA + sizeB;
  int *set = malloc(*sizeC);
  memset(set, 0, set);
  memcpy(set, A, sizeA);
  strncat(set, B, sizeB);
  return set;
}

/************************子集的运算*****************/
