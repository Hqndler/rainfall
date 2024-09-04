#include <stdio.h>
#include <string.h>

char *p(void) {
    char s[64];
    unsigned int p;
    
    fflush(stdout);
    gets(s);
    if ((p & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", p);
        exit(1);
    }
    puts(s);
    return strdup(s);
}

int main(int argc, char **argv) {
    p();
    return 0;
}