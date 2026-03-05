#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

int precedence(char op) {
    if (op == '*' || op == '/' || op == '%') return 3;
    if (op == '+' || op == '-')             return 2;
    if (op == '^')                          return 4;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

void infixToPostfix(char *expr) {
    int i, j = 0;
    int len = strlen(expr);
    char result[MAX];

    for (i = 0; i < len; i++) {
        char c = expr[i];

        if (c == ' ') continue;

        if (isalnum(c)) {
            result[j++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (!isEmpty() && peek() != '(')
                result[j++] = pop();
            pop();
        }
        else if (isOperator(c)) {
            while (!isEmpty() && peek() != '(' &&
                   ((c != '^' && precedence(peek()) >= precedence(c)) ||
                    (c == '^' && precedence(peek()) >  precedence(c)))) {
                result[j++] = pop();
            }
            push(c);
        }
    }
    while (!isEmpty())
        result[j++] = pop();

    result[j] = '\0';
    printf("%s\n", result);
}

int main() {
    char expr[MAX];
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = '\0';
    infixToPostfix(expr);
    return 0;
}