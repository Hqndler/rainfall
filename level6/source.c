#include <stdlib.h>
#include <stdio.h>

void n(void) {
    system("/bin/cat /home/user/level7/.pass");
}

void m(void) {
    puts("Nope");
}

int main(int argc, char **argv) {
    char *str = malloc(64);
    void (*f)(void) = malloc(4);

    f = &m;
    strcpy(str, argv[1]);
    f();
    return 0;
}