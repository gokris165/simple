#include <stdio.h>

void lower(char *this);

int main() {
    char this[10];
    scanf("%s", &this);
    lower(this);
}

void lower(char *this) {
    char temp[10];
    for (int i = 0; this[i] != '\0'; i++) {
        if (this[i] < 97) temp[i] = (32 + this[i]);
        else temp[i] = this[i];
    }

    printf("%s\n", temp);
}

