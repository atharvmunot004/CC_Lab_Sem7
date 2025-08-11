#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 100

// List of keywords
const char *keywords[] = {
    "int", "float", "if", "else", "while", "return", "for", "char", "double", "void"
};
int isKeyword(const char *str) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[MAX_LEN];
    int i = 0;
    FILE *fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Identifiers and keywords
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_')
                buffer[i++] = ch;
            buffer[i] = '\0';
            i = 0;
            fseek(fp, -1, SEEK_CUR);
            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
        }
        // Numbers
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(fp)))
                buffer[i++] = ch;
            buffer[i] = '\0';
            i = 0;
            fseek(fp, -1, SEEK_CUR);
            printf("Number: %s\n", buffer);
        }
        // Operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
                 ch == '<' || ch == '>' || ch == '!' || ch == '&' || ch == '|') {
            char op = ch;
            ch = fgetc(fp);
            if ((op == '=' && ch == '=') || (op == '!' && ch == '=') ||
                (op == '<' && ch == '=') || (op == '>' && ch == '=') ||
                (op == '&' && ch == '&') || (op == '|' && ch == '|')) {
                printf("Operator: %c%c\n", op, ch);
            } else {
                printf("Operator: %c\n", op);
                fseek(fp, -1, SEEK_CUR);
            }
        }
        // Special symbols
        else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            printf("Special Symbol: %c\n", ch);
        }
        // Ignore whitespace
        else if (isspace(ch)) {
            continue;
        }
    }

    fclose(fp);
    return 0;
}