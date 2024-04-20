/*
    Exercise 1-19.
    Write a function reverse(s) that reverses the character string s. 
    Use it to write a program that reverses its input a line at a time.
*/

/*
    -- PROGRAM STRUCTURE --
    while (input len > 0)
        reverse input
        print line
*/

#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int len);
void reverse(char s[], int len);

int main() {
    int len;            // current line length
    char line[MAXLINE];     // current input line

    while ((len = getline(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s\n", line);
    }
    printf("-- PROGRAM END --\n");
}

// getline: read a line into "line", return length
int getline(char s[], int lim) {
    int i, c;

    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// reverse: reverse the given string
void reverse(char s[], int len) {
    char t;
    for (int i = 0; i < (len-1) / 2; i++) {
        t = s[(len-2) - i];
        s[(len-2)-i] = s[i];
        s[i] = t;
    }
}