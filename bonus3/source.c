#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char ptr[132];
    FILE *file = fopen("/home/user/end/.pass", "r"); // who cares ?

    if (!file || argc != 2)
        return -1;

    fread(ptr, 1, 66, file);
    ptr[65] = 0;
    ptr[atoi(argv[1])] = 0; // ok
    fclose(file);
    if (!strcmp(ptr, argv[1])) // lmao
        execl("/bin/sh", "sh", 0);
    else
        puts(&ptr[66]);
    return 0;
}