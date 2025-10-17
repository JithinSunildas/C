#include<stdio.h>
static int n,k;

void readArr(int a[]){
  int i;
  printf("Give array elements: ");
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
}

void rotate(int a[]){
  int i,j,buffer;
  for(i=0;i<k;i++){
    buffer=a[n-1];
    for(j=n-1;j>=0;j--)
      a[j]=a[j-1];
    a[0]=buffer;
  }
}

void display(int a[]){
  int i;
  for(i=0;i<n;i++)
    printf("%d  ",a[i]);
  printf("\n");
}

int main(){
  printf("Give limit of array: ");
  scanf("%d",&n);
  int arr[20];
  readArr(arr);
  printf("Give limit for rotaton: ");
  scanf("%d",&k);
  display(arr);
  rotate(arr);
  display(arr);

  return 0;
}
