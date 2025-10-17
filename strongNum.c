#include<stdio.h>

int fact(int n){
  int a=1,i;
  for(i=1;i<n+1;i++)
      a*=i;
  return a;
}

int main(){
  int n,remind,num,sum=0;

  printf("Give the number: ");
  scanf("%d",&num);

  n=num;
  while (n>0) {
    remind=n%10;
    n/=10;
    sum+=fact(remind);
  }

  if(num==sum)
    printf("%d is a Strong number.\n",num);
  else printf("%d is not a Strong number.\n",num);
}
