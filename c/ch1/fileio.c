#include <stdio.h>

main(){
    int c;

    // c = getchar();
    // while (c != EOF){
    //     putchar(c);
    //     c = getchar();
    // }

    long nc = 0;

    printf("EOF = %d\n", EOF);
    while ((c = getchar()) != EOF) {
        ++nc;
        putchar(c);
    }
    printf("%ld\n", nc);

}