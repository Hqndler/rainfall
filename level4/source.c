#include <stdlib.h>
#include <stdio.h>

int m;

void p(char *str) {
    printf(str);
}

void n(void) {
    char str[512];

    fgets(str, 512, stdin);
    p(str);
    if (m == 0x1025544) {
        system("/bin/cat /home/user/level5/.pass");
    }
}

int main(void) {
    n();
    return 0;
}