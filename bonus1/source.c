#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char str[40];
    int n = atoi(argv[1]);

    if (n > 9)
        return 1;

    memcpy(str, argv[2], 4 * n);
    if (n == 1464814662) // 0x574f4c46
        execl("/bin/sh", "sh", NULL);
    return 0;
}