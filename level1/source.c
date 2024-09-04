#include <stdlib.h>
#include <stdio.h>

void run(void) {
    puts("Good... Wait what?\n");
    system("/bin/sh");
}

int main(int argc, char *argv) {
    char buffer[64];

    gets(buffer);
}