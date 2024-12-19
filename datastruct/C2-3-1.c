#include <stdio.h>

int factorial(int start, int end) {
  int n = start <= end ? end - start + 1 : start - end + 1;
  int sum = 0;
  sum = (start + end) * n / 2;
  return sum;
}

int factorial2(int start, int end) {
  static int sum = 0;
  if (start < end) {
    sum += start + end;
    start++;
    end--;
    factorial2(start, end);
  }
  if (start == end) {
    sum += start;
  }
  return sum;
}
int main() {
  int sum = factorial2(100, 1);
  printf("sum = %d\r\n", sum);
  return 0;
}
