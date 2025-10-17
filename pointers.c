#include<stdio.h>
static int n;

void readArr(int *p){
  int i;
  printf("Give %d elements: ",n);
  for(i=0;i<n;i++){
    scanf("%d",p);
    p++;
  }
}

void printArr(int *p){
  int i;
  for(i=0;i<n;i++){
    printf("%d  ",*p);
    p++;
  }
}

int min(int a[]){
  int i,min;
  min=a[0];
  for(i=1;i<n;i++){
    if (a[i] < min) {
      min = a[i];
    } 
    else {
      continue;
    }
  }
  return min;
}

int max(int a[]){
  int i,max;
  max=a[0];
  for(i=1;i<n;i++){
    if (a[i] > max) {
      max= a[i];
    } 
    else {
      continue;
    }
  }
  return max;
}

int main(){
  int i;
  int *p1;
  printf("Give limit: ");
  scanf("%d",&n);
  int arr[n];
  p1=&arr[0];
  readArr(p1);
  printArr(p1);
  printf("\nMin element = %d\nMax element = %d\n",min(arr),max(arr));
  return 0;
}
