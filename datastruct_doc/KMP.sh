#!/bin/bash

# A simple bash script to display function comments based on input function name

# Define function descriptions
function_str_assign="StrAssign: 生成一个其值等于chars的串T"
function_clear_string="ClearString: 清空字符串S"
function_str_print="StrPrint: 输出字符串T"
function_next_print="NextPrint: 输出Next数组值"
function_str_length="StrLength: 返回串的元素个数"
function_index="Index: 朴素的模式匹配法"
function_get_next="get_next: 通过计算返回子串T的next数组"
function_index_kmp="Index_KMP: 返回子串T在主串S中第pos个字符之后的位置 (KMP算法)"
function_get_nextval="get_nextval: 求模式串T的next函数修正值并存入数组nextval"
function_index_kmp1="Index_KMP1: 返回子串T在主串S中第pos个字符之后的位置 (KMP改良算法)"

# Prompt the user for a function name
echo "Enter the function name (e.g., StrAssign, ClearString, StrPrint, etc.):"
read function_name

# Display the description based on the input
case "$function_name" in
"StrAssign")
  echo "$function_str_assign"
  ;;
"ClearString")
  echo "$function_clear_string"
  ;;
"StrPrint")
  echo "$function_str_print"
  ;;
"NextPrint")
  echo "$function_next_print"
  ;;
"StrLength")
  echo "$function_str_length"
  ;;
"Index")
  echo "$function_index"
  ;;
"get_next")
  echo "$function_get_next"
  ;;
"Index_KMP")
  echo "$function_index_kmp"
  ;;
"get_nextval")
  echo "$function_get_nextval"
  ;;
"Index_KMP1")
  echo "$function_index_kmp1"
  ;;
*)
  echo "Unknown function name: $function_name"
  ;;
esac
