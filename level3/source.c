#include <stdlib.h>
#include <stdio.h>

int m;

void v(void) {
    char str[512];

    fgets(str, 512, stdin);
    printf(str);

    if (m == 64) {
        puts("Wait what ?!\n");
        system("/bin/sh");
    }
}

int main(void) {
    v();
    return 0;
}