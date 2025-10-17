#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char oprtr[100];
    int Top;
} Stack;

typedef struct {
    int val[100];
    int Top;
} IntStack;

typedef struct {
    char val[1000];
    int Back;
} Que;

void push(Stack *stack, char ch) {
    if (stack->Top < 99) {
        stack->Top++;
        stack->oprtr[stack->Top] = ch;
    } else {
        printf("Stack overflow!\n");
        exit(1);
    }
}

char pop(Stack *stack) {
    if (stack->Top >= 0) {
        return stack->oprtr[stack->Top--];
    }
    printf("Stack underflow!\n");
    return '\0';
}

void enque(Que *que, char ch) {
    if (que->Back < 999) {
        que->val[que->Back] = ch;
        que->Back++;
        que->val[que->Back] = '\0';
    } else {
        printf("Queue overflow!\n");
        exit(1);
    }
}

void push_int(IntStack *stack, int num) {
    if (stack->Top < 99) {
        stack->Top++;
        stack->val[stack->Top] = num;
    } else {
        printf("Evaluation stack overflow!\n");
        exit(1);
    }
}

int pop_int(IntStack *stack) {
    if (stack->Top >= 0) {
        return stack->val[stack->Top--];
    }
    printf("Evaluation stack underflow!\n");
    exit(1);
    return 0;
}

int pref(char oprtr) {
    switch (oprtr) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void postfix_converter(Que *infix_que, Que *postfix_que, Stack *oprtr_stack) {
    int i = 0;
    char token = infix_que->val[i], popped_op, temp;

    while (token != '\0') {
        if (isspace(token)) {
            i++;
            continue;
        }

        if (isdigit(token)) {
            while (isdigit(infix_que->val[i])) {
                enque(postfix_que, infix_que->val[i]);
                i++;
                printf("%d  ", i);
            }
            i--;
            enque(postfix_que, ' ');
        } else if (token == '(') {
            push(oprtr_stack, token);
        } else if (token == ')') {
            while (oprtr_stack->Top >= 0 && oprtr_stack->oprtr[oprtr_stack->Top] != '(') {
                popped_op = pop(oprtr_stack);
                enque(postfix_que, popped_op);
                enque(postfix_que, ' ');
            }
            if (oprtr_stack->Top >= 0) {
                pop(oprtr_stack);
            }
        } else {
            while (oprtr_stack->Top >= 0 &&
                   pref(oprtr_stack->oprtr[oprtr_stack->Top]) >= pref(token)) {
                popped_op = pop(oprtr_stack);
                enque(postfix_que, popped_op);
                enque(postfix_que, ' ');
            }
            push(oprtr_stack, token);
        }
        i++;
    }

    while (oprtr_stack->Top >= 0) {
        popped_op = pop(oprtr_stack);
        enque(postfix_que, popped_op);
        enque(postfix_que, ' ');
    }
}

int eval_postfix(Que *postfix_que) {
    IntStack value_stack;
    value_stack.Top = -1;
    int i = 0;
    char token = postfix_que->val[i];

    while (token != '\0') {
        if (isspace(token)) {
            i++;
            continue;
        }

        if (isdigit(token)) {
            int num = 0;
            while (isdigit(postfix_que->val[i])) {
                num = num * 10 + (postfix_que->val[i] - '0');
                i++;
            }
            i--;
            push_int(&value_stack, num);
        } else {
            if (value_stack.Top < 1) {
                fprintf(stderr, "Invalid postfix expression: not enough operands for operator.\n");
                exit(1);
            }
            int op2 = pop_int(&value_stack);
            int op1 = pop_int(&value_stack);
            int result;

            switch (token) {
            case '+':
                result = op1 + op2;
                break;
            case '-':
                result = op1 - op2;
                break;
            case '*':
                result = op1 * op2;
                break;
            case '/':
                if (op2 == 0) {
                    printf("Error: Division by zero.\n");
                    exit(1);
                }
                result = op1 / op2;
                break;
            case '%':
                result = op1 % op2;
                break;
            case '^':
                result = (double)pow((double)op1, (double)op2);
                break;
            default:
                printf("Unknown operator: %c\n", token);
                exit(1);
            }
            push_int(&value_stack, result);
        }
        i++;
    }

    if (value_stack.Top != 0) {
        fprintf(stderr, "Invalid postfix expression: too many operands.\n");
        exit(1);
    }

    return pop_int(&value_stack);
}

int main() {
    Que input_que;
    Que output_que;
    Stack oprtr_stack;

    oprtr_stack.Top = -1;
    input_que.Back = 0;
    output_que.Back = 0;
    output_que.val[0] = '\0';

    printf("Enter the infix expression (e.g., 2 + 3 * 4): ");

    if (fgets(input_que.val, sizeof(input_que.val), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    input_que.val[strcspn(input_que.val, "\n")] = 0;

    printf("Infix expression: %s\n", input_que.val);
    printf("Postfix expression: %s\n", output_que.val);

    int result = eval_postfix(&output_que);
    printf("Result: %d\n", result);

    return 0;
}
