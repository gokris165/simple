#include <stdio.h>

main(){

    int c, nl, bl, nt;
    int program_choice;
    printf("Choose a program: \n");
    printf("1: blank, new line, tab counter\n");
    printf("2: white space eliminator\n");
    printf("3: visible escape chars\n");
    printf("Enter a number: ");
    program_choice = getchar();

    if (program_choice == '1'){
        nl, bl, nt = 0;
        while((c = getchar()) != EOF){
            if(c == '\n')
                ++nl;
            if(c == ' ')
                ++bl;
            if(c == '\t')
                ++nt;
        }
        printf("new line: %d, blanks: %d, tabs: %d\n", nl, bl, nt);
    }
    else if (program_choice == '2') {
        int previous;
        while ((c = getchar()) != EOF) {
            if (c == '\t' && previous == c)
                continue;
            if (c == ' ' && previous == c)
                continue;
            previous = c;
            if (c == '\t')
                putchar(' ');
            else
                putchar(c);
        }
    }
    else if (program_choice == '3') {
        while ((c = getchar()) != EOF) {
            if (c == '\t')
                printf("\\t");
            else if (c == '\b')
                printf("\\b");
            else if (c == '\\')
                printf("\\\\");
            else
                putchar(c);
        }
    }
}