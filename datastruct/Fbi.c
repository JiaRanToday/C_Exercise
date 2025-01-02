#include <stdio.h>
int Fbi(int i) {
  if (i < 2) {
    return i == 0 ? 0 : 1;
  }
  return Fbi(i - 1) + Fbi(i - 2);
}
int main() {
  printf("please input a Fbi number: ");
  int i = 0;
  scanf("%d", &i);
  printf("\nFbi = %d\r\n", Fbi(i));
  return 0;
}
