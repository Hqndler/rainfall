#include <stdlib.h>

int main(int argc, char **argv) {
    if (atoi(argv[1]) == 432)
        system("/bin/sh");
    return 0;
}