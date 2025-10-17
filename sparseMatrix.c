#include<stdio.h>

typedef struct { 
    int row;
    int col;
} Dimension;

typedef struct {
  int x[100];
  int y[100];
  int val[100];
  Dimension dim;
  int size;
} Matrix;

void read_matrix(Matrix *p) {
  int i;
  for(i=0;i<p->size;i++) {
    printf("Position & value: ");
    scanf("%d%d%d", &p->x[i], &p->y[i], &p->val[i]);
  }
}

void echo_matrix(Matrix *p) {
  int i;
  for(i=0;i<p->size;i++)
      printf("%d(%d,%d)  ", p->val[i], p->x[i], p->y[i]);
  printf("\n");
}

void add_matrix(Matrix *a, Matrix *b, Matrix *c) {
  int i=0, j=0, k=0, temp;

  while(i<a->size && j<b->size) {
    if((a->x[i] < b->x[j]) || ((a->x[i] == b->x[j]) && (a->y[i] < b->y[j]))) {
      c->x[k] = a->x[i];
      c->y[k] = a->y[i] ;
      c->val[k] = a->val[i] ;
      i++;
      k++;
    }
    else if((a->x[i] > b->x[j]) || ((a->x[i] == b->x[j]) && (a->y[i] > b->y[j]))) {
      c->x[k] = b->x[j];
      c->y[k] = b->y[j];
      c->val[k] = b->val[j];
      j++;
      k++;
    }
    else {
      temp = a->val[i] + b->val[j];
      if(temp != 0){
        c->x[k] = a->x[i];
        c->y[k] = a->y[j];
        c->val[k] = temp;
        k++;
      }
      i++;
      j++;
    }
  }
 
  while(i<a->size) {
    c->x[k] = a->x[i];
    c->y[k] = a->y[i];
    c->val[k] = a->val[i];
    i++;
    k++;
  }
 
  while(j<b->size) {
    c->x[k] = b->x[j];
    c->y[k] = b->y[j];
    c->val[k] = b->val[j];
    j++;
    k++;
  }

  c->size = k;
}

int main() {

  Matrix a, b, c;

  printf("Give dimension of a: ");
  scanf("%d%d", &a.dim.row, &a.dim.col);

  printf("Give dimension of b: ");
  scanf("%d%d", &b.dim.row, &b.dim.col);

  if((a.dim.row == b.dim.row) && (a.dim.col == b.dim.col)) {
    printf("Give size of a: ");
    scanf("%d", &a.size);
    printf("Give size of b: ");
    scanf("%d", &b.size);
    printf("\n");

    printf("Give first matrix in order\n");
    read_matrix(&a);
    printf("\n");

    printf("Give second matrix in order\n");
    read_matrix(&b);
    printf("\n");

    echo_matrix(&a);
    echo_matrix(&b);
    printf("\n");

    add_matrix(&a, &b, &c);
    echo_matrix(&c);

  }

  else{
    printf("Matrix dimensions are unable to add!");
  }

return 0;
}

