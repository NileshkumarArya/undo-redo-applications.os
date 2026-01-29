#include <stdio.h>
#include <string.h>

#define MAX 100
#define TEXT_SIZE 1000


typedef struct {
    char data[MAX][TEXT_SIZE];
    int top;
} Stack;


void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char text[]) {
    if (!isFull(s)) {
        s->top++;
        strcpy(s->data[s->top], text);
    }
}

void pop(Stack *s, char text[]) {
    if (!isEmpty(s)) {
        strcpy(text, s->data[s->top]);
        s->top--;
    }
}

void clearStack(Stack *s) {
    s->top = -1;
}

int main() {
    Stack undoStack, redoStack;
    char currentText[TEXT_SIZE] = "";
    char newText[TEXT_SIZE];
    int choice;

    initStack(&undoStack);
    initStack(&redoStack);

    while (1) {
        printf("\n--- UNDO REDO TEXT EDITOR ---\n");
        printf("1. Add Text\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Display Text\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {

        case 1:
            push(&undoStack, currentText);   
            clearStack(&redoStack);        

            printf("Enter text to add: ");
            fgets(newText, TEXT_SIZE, stdin);
            newText[strcspn(newText, "\n")] = '\0';

            strcat(currentText, newText);
            break;

        case 2:
            if (!isEmpty(&undoStack)) {
                push(&redoStack, currentText);
                pop(&undoStack, currentText);
                printf("Undo successful!\n");
            } else {
                printf("Nothing to undo!\n");
            }
            break;

        case 3:
            if (!isEmpty(&redoStack)) {
                push(&undoStack, currentText);
                pop(&redoStack, currentText);
                printf("Redo successful!\n");
            } else {
                printf("Nothing to redo!\n");
            }
            break;

        case 4:
            printf("\nCurrent Text:\n%s\n", currentText);
            break;

        case 5:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
