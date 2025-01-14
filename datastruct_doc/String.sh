#!/usr/bin/bash
# 设置文件名
output_file="StringDataStructure_Documentation.md"
# 创建或清空文档文件
echo "# 串数据结构文档" > $output_file
echo "生成时间: $(date)" >> $output_file
echo "--------------------" >> $output_file

# 添加简介部分
echo "## 简介" >> $output_file
echo "串是一种特殊的线性数据结构，表示一系列字符的集合。它通常用于存储和操作字符串，在计算机程序中广泛应用。" >> $output_file
echo "" >> $output_file

# 添加结构定义部分
echo "## 数据结构定义" >> $output_file
echo "```c" >> $output_file
echo "#define OK 1" >> $output_file
echo "#define ERROR 0" >> $output_file
echo "#define TRUE 1" >> $output_file
echo "#define FALSE 0" >> $output_file
echo "" >> $output_file
echo "#define MAXSIZE 40 /* 存储空间初始分配量 */" >> $output_file
echo "" >> $output_file
echo "typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */" >> $output_file
echo "typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */" >> $output_file
echo "typedef char String[MAXSIZE+1]; /* 0号单元存放串的长度 */" >> $output_file
echo " " >> $output_file

# 添加功能描述
echo "## 功能函数" >> $output_file

# StrAssign函数
echo "### StrAssign - 赋值操作" >> $output_file
echo " 该函数用于生成一个其值等于chars的串T。" >> $output_file
echo "Status StrAssign(String T, char *chars)" >> $output_file
echo "{" >> $output_file
echo "    int i;" >> $output_file
echo "    if(strlen(chars) > MAXSIZE)" >> $output_file
echo "        return ERROR;" >> $output_file
echo "    else" >> $output_file
echo "    {" >> $output_file
echo "        T[0] = strlen(chars);" >> $output_file
echo "        for(i = 1; i <= T[0]; i++)" >> $output_file
echo "            T[i] = *(chars + i - 1);" >> $output_file
echo "        return OK;" >> $output_file
echo "    }" >> $output_file
echo "}" >> $output_file
echo "```" >> $output_file
echo "" >> $output_file

# StrCopy函数
echo "### StrCopy - 复制操作" >> $output_file
echo "该函数用于将串S的内容复制到串T。" >> $output_file
echo "```c" >> $output_file
echo "Status StrCopy(String T, String S)" >> $output_file
echo "{" >> $output_file
echo "    int i;" >> $output_file
echo "    for(i = 0; i <= S[0]; i++)" >> $output_file
echo "        T[i] = S[i];" >> $output_file
echo "    return OK;" >> $output_file
echo "}" >> $output_file
echo "" >> $output_file

# StrCompare函数
echo "### StrCompare - 比较操作" >> $output_file
echo "该函数用于比较串S和串T的大小。" >> $output_file
echo "int StrCompare String S, String T" >> $output_file
echo "{" >> $output_file
echo "    int i;" >> $output_file
echo "    for(i = 1; i <= S[0] && i <= T[0]; ++i)" >> $output_file
echo "        if(S[i] != T[i])" >> $output_file
echo "            return S[i] - T[i];" >> $output_file
echo "    return S[0] - T[0];" >> $output_file
echo "}" >> $output_file
echo "" >> $output_file

# Concat函数
echo "### Concat - 串连接操作" >> $output_file
echo "该函数用于连接两个串S1和S2，并返回新串T。" >> $output_file
echo "Status Concat(String T, String S1, String S2)" >> $output_file
echo "{" >> $output_file
echo "    int i;" >> $output_file
echo "    if(S1[0] + S2[0] <= MAXSIZE)" >> $output_file
echo "    {" >> $output_file
echo "        for(i = 1; i <= S1[0]; i++)" >> $output_file
echo "            T[i] = S1[i];" >> $output_file
echo "        for(i = 1; i <= S2[0]; i++)" >> $output_file
echo "            T[S1[0] + i] = S2[i];" >> $output_file
echo "        T[0] = S1[0] + S2[0];" >> $output_file
echo "        return TRUE;" >> $output_file
echo "    }" >> $output_file
echo "    else" >> $output_file
echo "    {" >> $output_file
echo "        for(i = 1; i <= S1[0]; i++)" >> $output_file
echo "            T[i] = S1[i];" >> $output_file
echo "        for(i = 1; i <= MAXSIZE - S1[0]; i++)" >> $output_file
echo "            T[S1[0] + i] = S2[i];" >> $output_file
echo "        T[0] = MAXSIZE;" >> $output_file
echo "        return FALSE;" >> $output_file
echo "    }" >> $output_file
echo "}" >> $output_file
echo "" >> $output_file

# 总结部分
echo "## 总结" >> $output_file
echo "本篇文档介绍了串数据结构的基本操作，包括赋值、复制、比较、连接等常见操作。使用这些操作，我们能够实现串数据的高效管理和操作，进而为嵌入式开发中的字符串处理提供基础支持。" >> $output_file
echo "" >> $output_file

# 完成消息
echo "文档生成成功: $output_file"


