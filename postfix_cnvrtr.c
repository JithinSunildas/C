#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

int prec(char operator) {
    switch (operator) {
    case '^':
        return 3;
    case '%':
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void In2Post(char infix[], char postfix[]) {
    int i = 0, j = 0;
    while (infix[i]) {
        char c = infix[i];

        if (isdigit(c)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            while (top != -1 &&
                   ((prec(stack[top]) > prec(c)) || (prec(stack[top]) == prec(c) && c != '^'))) {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            push(c);
        }
        i++;
    }

    while (top != -1) {
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

int Eval(char postfix[]) {
    int stack1[MAX], t = -1;
    int i = 0;

    while (postfix[i]) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            stack1[++t] = num;
        } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' ||
                   postfix[i] == '/' || postfix[i] == '%' || postfix[i] == '^') {
            if (t < 1) {
                printf("Error: Invalid postfix expression\n");
                return 0;
            }

            int b = stack1[t--];
            int a = stack1[t--];

            switch (postfix[i]) {
            case '+':
                stack1[++t] = a + b;
                break;
            case '-':
                stack1[++t] = a - b;
                break;
            case '*':
                stack1[++t] = a * b;
                break;
            case '/':
                if (b == 0) {
                    printf("Error: Division by zero\n");
                    return 0;
                }
                stack1[++t] = a / b;
                break;
            case '%':
                if (b == 0) {
                    printf("Error: Division by zero\n");
                    return 0;
                }
                stack1[++t] = a % b;
                break;
            case '^':
                stack1[++t] = (int)pow(a, b);
                break;
            }
        }
        i++;
    }
    return (t == 0) ? stack1[t] : 0;
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix Expression: ");
    fgets(infix, MAX, stdin);

    In2Post(infix, postfix);

    printf("Postfix : %s\n", postfix);
    printf("Result  : %d\n", Eval(postfix));

    return 0;
}
