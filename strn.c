#include<stdio.h>

int main() {
  char arr[100];
  printf(">>>");
  scanf("%[^\n]",arr);

  //counting the total chars.
  int n=0,i=0;
  while (arr[i]!='\0'){
    n++;
    i++;
  }

  //printing backwards.
  for(i=n-1;i>=0;i--)
    printf("%c",arr[i]);
  printf("\n");

  return 0;
}
