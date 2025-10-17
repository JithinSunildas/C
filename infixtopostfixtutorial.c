#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_ITEMS = 100 };
enum tag_t { VAL, BEGIN, END, PLUS, MINUS, MUL, DIV, COMPL, EXP };
typedef enum tag_t tag_t;

// helper function to convert tag to a string
const char *tag2str(tag_t x) {
    switch (x) {
    case PLUS:
        return "+";
    case MUL:
        return "*";
    case MINUS:
        return "-";
    case DIV:
        return "/";
    case EXP:
        return "^";
    case COMPL:
        return "~";
    case BEGIN:
        return "(";
    case END:
        return ")";
    case VAL:
        return "VAL";
    default:
        return "?";
    }
}

typedef struct token_t token_t;
struct token_t {
    tag_t tag;
    int val;
};

tag_t get_tag(token_t t) { return t.tag; }
int get_val(token_t t) {
    assert(get_tag(t) == VAL);
    return t.val;
}
token_t token_new(tag_t t) {
    token_t ret = {t, 0};
    return ret;
}
token_t token_new2(tag_t t, int val) {
    token_t ret = {t, val};
    return ret;
}

struct stack_t {
    token_t data[MAX_ITEMS];
    int size;
};
typedef struct stack_t stack_t;

struct growable_array_t {
    token_t data[MAX_ITEMS];
    int size;
};
typedef struct growable_array_t growable_array_t;

void init_stack(stack_t *s) { s->size = 0; }
void init_array(growable_array_t *s) { s->size = 0; }

void add_back(growable_array_t *s, token_t t) {
    assert(s->size < MAX_ITEMS);
    s->data[s->size] = t;
    s->size++;
}

void push(stack_t *s, token_t t) {
    assert(s->size < MAX_ITEMS);
    s->data[s->size] = t;
    s->size++;
}

token_t top(stack_t *s) {
    assert(s->size > 0);
    return s->data[s->size - 1];
}

void pop(stack_t *s) {
    assert(s->size > 0);
    s->size--;
}

bool empty(stack_t *s) { return s->size == 0; }

// helper function: precedence of an op
int prec(tag_t a) {
    switch (a) {
    case PLUS:
    case MINUS:
        return 1;
    case MUL:
    case DIV:
        return 2;
    case COMPL:
        return 3;
    case EXP:
        return 4;
    default:
        return 0;
    }
}

// helper function: is the op LEFT associative or not
bool left_assoc(tag_t a) {
    switch (a) {
    case PLUS:
    case MINUS:
    case MUL:
    case DIV:
        return true;
    case COMPL:
    case EXP:
        return false;
    default:
        return false;
    }
}

// helper function: compare token prec and assoc
int cmp(tag_t a, tag_t b) {
    if (prec(a) > prec(b)) {
        return 1;
    } else if (prec(a) < prec(b)) {
        return -1;
    } else {
        if (left_assoc(a))
            return 1;
        else
            return -1;
    }
}

void print_stack(const char *name, stack_t *x);
void print_array(const char *name, growable_array_t *x);
void print_token(token_t t);

/**
 * Convert given infix expression to a postfix expression using a stack
 */
void in2post(const growable_array_t *input, growable_array_t *output) {
    stack_t stack;
    init_stack(&stack);
    init_array(output);

    for (int i = 0; i < input->size; i++) {
        token_t current_token = input->data[i];
        tag_t tag = current_token.tag;

        switch (tag) {
        case VAL:
            add_back(output, current_token);
            break;

        case BEGIN:
            push(&stack, current_token);
            break;

        case PLUS:
        case MINUS:
        case MUL:
        case DIV:
        case COMPL:
        case EXP: {
            while (!empty(&stack) && top(&stack).tag != BEGIN) {
                if (cmp(top(&stack).tag, tag) >= 0) {
                    add_back(output, top(&stack));
                    pop(&stack);
                } else {
                    break;
                }
            }
            push(&stack, current_token);
        } break;

        case END: {
            while (!empty(&stack) && top(&stack).tag != BEGIN) {
                add_back(output, top(&stack));
                pop(&stack);
            }
            if (!empty(&stack) && top(&stack).tag == BEGIN) {
                pop(&stack); // Pop the opening parenthesis
            }
        } break;
        }
        // print statements for debugging are commented out for cleaner output
        // printf("\n%d token: ", i);
        // print_token(current_token);
        // print_stack(" stack ", &stack);
        // print_array(" output ", output);
    }
    // Pop any remaining operators from the stack
    while (!empty(&stack)) {
        add_back(output, top(&stack));
        pop(&stack);
    }
}

// helper function: evaluate unary oper
int eval1(tag_t op, int val1) {
    switch (op) {
    case COMPL:
        return -val1;
    default:
        assert(false);
        return 0; // To silence compiler warnings
    }
}

// helper function: evaluate binary oper
int eval2(tag_t op, int val1, int val2) {
    switch (op) {
    case PLUS:
        return val1 + val2;
    case MINUS:
        return val1 - val2;
    case MUL:
        return val1 * val2;
    case DIV:
        assert(val2 != 0); // Prevent division by zero
        return val1 / val2;
    case EXP:
        return (int)pow(val1, val2);
    default:
        assert(false);
        return 0; // To silence compiler warnings
    }
}

// helper function: is given op a unary or binary op
int numops(tag_t a) {
    if (a == COMPL) {
        return 1;
    } else {
        return 2;
    }
}

/**
 * Evaluate a postfix expression
 */
int evalPostfix(const growable_array_t *input) {
    stack_t stack;
    init_stack(&stack);

    for (int i = 0; i < input->size; i++) {
        tag_t tag = input->data[i].tag;
        if (tag == VAL) {
            push(&stack, input->data[i]);
        } else {
            switch (numops(tag)) {
            case 2: {
                if (stack.size < 2) {
                    printf("Error: Not enough operands for binary operator\n");
                    exit(1);
                }
                int val2 = get_val(top(&stack));
                pop(&stack);
                int val1 = get_val(top(&stack));
                pop(&stack);
                int val = eval2(tag, val1, val2);
                push(&stack, token_new2(VAL, val));
            } break;
            case 1: {
                if (stack.size < 1) {
                    printf("Error: Not enough operands for unary operator\n");
                    exit(1);
                }
                int val1 = get_val(top(&stack));
                pop(&stack);
                int val = eval1(tag, val1);
                push(&stack, token_new2(VAL, val));
            } break;
            default:
                assert(false);
            }
        }
    }
    if (stack.size != 1) {
        printf("Error: Malformed postfix expression\n");
        exit(1);
    }
    token_t ret = top(&stack);
    return get_val(ret);
}

void print_token(token_t t) {
    if (t.tag == VAL) {
        printf(" %d ", t.val);
    } else {
        printf(" %s ", tag2str(t.tag));
    }
}
void print_stack(const char *name, stack_t *x) {
    printf("%s (size=%d): ", name, x->size);
    for (int i = 0; i < x->size; i++) {
        print_token(x->data[i]);
    }
    printf("\n");
}
void print_array(const char *name, growable_array_t *x) {
    printf("%s (size=%d): ", name, x->size);
    for (int i = 0; i < x->size; i++) {
        print_token(x->data[i]);
    }
    printf("\n");
}

void read_array(const char *name, growable_array_t *x) {
    char s[100];
    printf("Enter %s: ", name);
    fgets(s, sizeof(s), stdin);
    init_array(x);
    for (char *p = &s[0]; *p != 0; p++) {
        if (isspace(*p)) {
            continue;
        }
        switch (*p) {
        case '+':
            add_back(x, token_new(PLUS));
            break;
        case '-':
            add_back(x, token_new(MINUS));
            break;
        case '*':
            add_back(x, token_new(MUL));
            break;
        case '/':
            add_back(x, token_new(DIV));
            break;
        case '~':
            add_back(x, token_new(COMPL));
            break;
        case '^':
            add_back(x, token_new(EXP));
            break;
        case '(':
            add_back(x, token_new(BEGIN));
            break;
        case ')':
            add_back(x, token_new(END));
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            add_back(x, token_new2(VAL, *p - '0'));
            break;
        default:
            break;
        }
    }
}

int main() {
    growable_array_t input;
    growable_array_t output;

    read_array("infix", &input);
    print_array("infix", &input);

    in2post(&input, &output);
    print_array("postfix", &output);

    int val = evalPostfix(&output);
    printf("VAL: %d\n", val);

    return 0;
}
