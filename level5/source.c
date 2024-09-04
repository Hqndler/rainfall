#include <stdlib.h>
#include <stdio.h>

void o(void) {
    system("/bin/sh");
    exit(1);
}

void n(void) {
    char str[512];

    fgets(str, 512, stdin);
    print(str);
    exit(1);
}

int main(void) {
    n();
    return 0;
}