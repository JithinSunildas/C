#include<stdio.h>
void main()
{
  int i=1,n,f=1;
  printf("Enter the number");
  scanf("%d",&n)
  
  for(i=1;i<=n;i++){
    f=f*i;
  }
  printf("Factorial of %d is %d ",n,f)
}