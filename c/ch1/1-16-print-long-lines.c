/*
    Exercise 1-16.
    Revise the main routine of the longest-line program so it will
    correctly print the length of arbitrary long input lines, and 
    as much as possible of the text.
*/

#include <stdio.h>
#define MAXLINE 1000        // maximum input line length
#define PRINTABLE 20        // printable input line length

int getline(char line[], int maxline);
void copy(char to[], char from[]);

// print longest and arbitrarily long lines
int main() {
    int len;        // current line length
    int max;        // max length seen so far
    char line[MAXLINE];     // current input line
    char longest[MAXLINE];  // longest line saved

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
        if (len > PRINTABLE) 
            printf("%s", line);
    }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

// getline: read a line into s, return length
int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// copy: copy characters array "from" to "to"
void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}