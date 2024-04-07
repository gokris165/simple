#include <stdio.h>

#define MAX_LEN 10

main() {
    int len[MAX_LEN];
    int i, c;
    for (i = 0; i < MAX_LEN; i++) 
        len[i] = 0;
    
    int length = 0;
    while((c = getchar()) != EOF){
        if (c == ' ' || c == '\n' || c == '\t'){
            if (length > MAX_LEN)
                ++len[MAX_LEN - 1];
            else
                ++len[length];
            length = 0;
        }
        length++;
    }

    for (i = 1; i < MAX_LEN - 1; i++) {
        printf("len %d\t: ", i);
        for (int j = 0; j < len[i]; j++)
            printf("=");
        printf("\n");
    }
    printf("len 10+\t: ");
    for (int j = 0; j < len[MAX_LEN-1]; j++)
        printf("=");
    printf("\n");
}