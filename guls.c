#include<stdio.h>
typedef struct{
int coef;
int exp;
}poly;

void read_poly(poly *p,int size){
int i;
for(i=0;i<size;i++){
printf("enter the coefficient");
scanf("%d",&p->coef);
printf("enter the exponential");
scanf("%d",&p->exp);
p++;}
}

void print_poly(poly *p,int size){
int i;
for(i=0;i<size;i++){
printf("%dx^%d",p->coef,p->exp);
p++;}
printf("/n");
}

void main(){
int m,n;
printf("enter the length 1st polynomials");
scanf("%d",&m);
poly a[m];
read_poly(&a[0],m);
printf("enter the length 2nd polynomials");
scanf("%d",&n);
poly b[n];
read_poly(&b[0],n);
print_poly(&a[0],m);
print_poly(&b[0],n);
}
