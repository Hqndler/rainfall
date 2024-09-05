#include <stdio.h>
#include <string.h>

void p(char *s1, char *s2) {
    char buffer[4096];

    puts(s2);
    read(0, buffer, sizeof(buffer));
    char *tmp = strchr(buffer, '\n');
    tmp[0] = 0;
    strncpy(s1, buffer, 20);
}

void pp(char *str) {
    char first[20];
    char last[20];

    p(first, " - ");
    p(last, " - ");

    strcpy(str, first);
    strcpy(str, " ");
    strcpy(str, last);
}

int main(int argc, char **argv) {
    char str[42];

    pp(str);
    printf("%s\n", str);
    return 0;
}