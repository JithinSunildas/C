#include<stdio.h>

typedef struct {
  int exp[100];
  int coeff[100];
  int size;
} Poly;

void read_poly(Poly *p) {
  int i;
  for(i=0;i<p->size;i++) {
    printf("Coefficient and exponent: ");
    scanf("%d%d", &p->coeff[i], &p->exp[i]);
  }
}

void echo_poly(Poly *p) {
  int i;
  for(i=0;i<p->size;i++)
      printf("%dx^%d  ", p->coeff[i], p->exp[i]);
  printf("\n");
}

void add_poly(Poly *a, Poly *b, Poly *c) {
  int i=0, j=0, k=0, temp;

  while(i<a->size && j<b->size) {
    if(a->exp[i] == b->exp[j]) {
      temp = a->coeff[i] + b->coeff[j];
      if(temp != 0){
        c->exp[k] = a->exp[i];
        c->coeff[k] = temp;
        k++;
      }
      i++;
      j++;
    }
    else if(a->exp[i] < b->exp[j]) {
      c->exp[k] = a->exp[i];
      c->coeff[k] = a->coeff[i] ;
      i++;
      k++;
    }
    else {
      c->exp[k] = b->exp[j];
      c->coeff[k] = b->coeff[j];
      j++;
      k++;
    }
  }
 
  while(i<a->size) {
    c->exp[k] = a->exp[i];
    c->coeff[k] = a->coeff[i];
    i++;
    k++;
  }
 
  while(j<b->size) {
    c->exp[k] = b->exp[j];
    c->coeff[k] = b->coeff[j];
    j++;
    k++;
  }

  c->size = k;
}

int main() {

  Poly a, b, c;

  printf("Give size of a: ");
  scanf("%d", &a.size);
  printf("Give size of b: ");
  scanf("%d", &b.size);
  printf("\n");

  printf("Give first poly in order\n");
  read_poly(&a);
  printf("\n");
  // printf("%dx^%d  here", a.coeff[0], a.exp[0]);
  printf("Give second poly in order\n");
  read_poly(&b);
  printf("\n");

  echo_poly(&a);
  echo_poly(&b);
  printf("\n");

  add_poly(&a, &b, &c);
  echo_poly(&c);

  return 0;
}
