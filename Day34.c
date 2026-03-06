// Problem: Evaluate Postfix Expression - Implement using linked list with dynamic memory allocation.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL;

void push(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

int pop() {
    struct Node* temp = top;
    int value = temp->data;
    top = top->next;
    free(temp);
    return value;
}

int main() {
    char expression[200];

    fgets(expression, sizeof(expression), stdin);

    char* token = strtok(expression, " \n");

    while (token != NULL) {

        if ((strlen(token) == 1) &&
            (token[0] == '+' || token[0] == '-' ||
             token[0] == '*' || token[0] == '/')) {

            int b = pop();
            int a = pop();
            int result;

            if      (token[0] == '+') result = a + b;
            else if (token[0] == '-') result = a - b;
            else if (token[0] == '*') result = a * b;
            else                      result = a / b;

            push(result);

             } else {
                 push(atoi(token));
             }

        token = strtok(NULL, " \n");
    }
    printf("%d\n", pop());
    return 0;
}