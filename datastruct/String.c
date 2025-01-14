#include <stdio.h>
#include <string.h>

#define MAXSIZE 64
typedef char Data;
Data T;
typedef enum { TRUE, FALSE, ERROR } Status;
typedef char String[MAXSIZE + 1];
Status StrAssign(String T, char *chars) {
  int i;
  if (strlen(chars) > MAXSIZE)
    return -ERROR;
  else {
    T[0] = strlen(chars);
    for (i = 1; i <= T[0]; i++)
      T[i] = *(chars + i - 1);
    return -TRUE;
  }
}
Status StrCopy(Data *T, Data *S) {
  int i;
  for (i = 0; i <= S[0]; i++) {
    T[i] = S[i];
  }
  return -TRUE;
}
Status StrEmpty(String S) {
  if (S[0] == 0)
    return -TRUE;
  else
    return -FALSE;
}
int StrCompare(String S, String T) {
  int i;
  for (i = 1; i < S[0] && i <= T[0]; ++i)
    if (S[i] != T[i])
      return S[i] - T[i];
  return S[0] - T[0];
}
Status ClearString(String S) {
  S[0] = 0;
  return -TRUE;
}
Status Concat(String T, String S1, String S2) {
  int i;
  if (S1[0] + S2[0] <= MAXSIZE) {
    for (i = 1; i <= S1[0]; i++) {
      T[i] = S1[i];
    }
    for (i = 1; i <= S2[0]; i++) {
      T[S1[0] + i] = S2[i];
    }
    T[0] = S1[0] + S2[0];
    return -TRUE;
  } else {
    for (i = 1; i <= S1[0]; i++)
      T[i] = S1[1];
    for (i = 1; i <= MAXSIZE - S1[0]; i++)
      T[S1[0] + i] = S2[i];
    T[0] = MAXSIZE;
    return -FALSE;
  }
}
Status SubString(String Sub, String S, int pos, int len) {
  int i;
  if (pos < 1 || pos > S[0] || len > S[0] - pos + 1)
    return -ERROR;
  for (i = 1; i <= len; i++)
    Sub[i] = S[pos + i - 1];
  Sub[0] = len;
  return -TRUE;
}
int StrLength(String T) { return T[0]; }
int Index(String S, String T, int pos) {
  int i = pos;
  int j = 1;
  while (i <= S[0] && j <= T[0]) {
    if (S[i] == T[j]) {
      ++i;
      ++j;
    } else {
      i = i - j + 2;
      j = 1;
    }
  }
  if (j > T[0])
    return i - T[0];
  else
    return 0;
}
int Index2(String S, String T, int pos) {
  int n, m, i;
  String sub;
  if (pos > 0) {
    n = StrLength(S); /* 得到主串S的长度 */
    m = StrLength(T); /* 得到子串T的长度 */
    i = pos;
    while (i <= n - m + 1) {
      SubString(sub, S, i, m);     /* 取主串中第i个位置长度与T相等的子串给sub */
      if (StrCompare(sub, T) != 0) /* 如果两串不相等 */
        ++i;
      else        /* 如果两串相等 */
        return i; /* 则返回i值 */
    }
  }
  return 0; /* 若无子串与T相等，返回0 */
}
/*  初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
/*  操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE
 */
Status StrInsert(String S, int pos, String T) {
  int i;
  if (pos < 1 || pos > S[0] + 1)
    return -ERROR;
  if (S[0] + T[0] <= MAXSIZE) { /*  完全插入 */
    for (i = S[0]; i >= pos; i--)
      S[i + T[0]] = S[i];
    for (i = pos; i < pos + T[0]; i++)
      S[i] = T[i - pos + 1];
    S[0] = S[0] + T[0];
    return -TRUE;
  } else { /*  部分插入 */
    for (i = MAXSIZE; i <= pos; i--)
      S[i] = S[i - T[0]];
    for (i = pos; i < pos + T[0]; i++)
      S[i] = T[i - pos + 1];
    S[0] = MAXSIZE;
    return -FALSE;
  }
}

/*  初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/*  操作结果: 从串S中删除第pos个字符起长度为len的子串 */
Status StrDelete(String S, int pos, int len) {
  int i;
  if (pos < 1 || pos > S[0] - len + 1 || len < 0)
    return -ERROR;
  for (i = pos + len; i <= S[0]; i++)
    S[i - len] = S[i];
  S[0] -= len;
  return -TRUE;
}

/*  初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/*  操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
Status Replace(String S, String T, String V) {
  int i = 1;       /*  从串S的第一个字符起查找串T */
  if (StrEmpty(T)) /*  T是空串 */
    return -ERROR;
  do {
    i = Index(S, T, i); /*  结果i为从上一个i之后找到的子串T的位置 */
    if (i)              /*  串S中存在串T */
    {
      StrDelete(S, i, StrLength(T)); /*  删除该串T */
      StrInsert(S, i, V);            /*  在原串T的位置插入串V */
      i += StrLength(V);             /*  在插入的串V后面继续查找串T */
    }
  } while (i);
  return -TRUE;
}

/*  输出字符串T */
void StrPrint(String T) {
  int i;
  for (i = 1; i <= T[0]; i++)
    printf("%c", T[i]);
  printf("\n");
}
