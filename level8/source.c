#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strct {
    char b[32];
    int a;
} t_struct;

int main(void) {
    t_struct *auth;
    char *service;
    char s[128];

    printf("%ld\n", sizeof(auth));

    while (1) {
        printf("%p, %p\n", auth, service);
        
        if (fgets(s, 128, stdin) == 0)
            break;
        
        if (!strncmp(s, "auth ", 5)) {
            auth = malloc(sizeof(auth)); // sizeof(ptr) = 4 for 32bit sys
            memset(auth, 0, sizeof(auth));
            if (strlen(s + 5) < 31) // instruction repz scas (strlen)
                strcpy(auth->b, s + 5);
        }
        if (!strncmp(s, "reset", 5))
            free(auth);

        if (!strncmp(s, "service", 6))
            service = strdup(s + 7);
        
        if (!strncmp(s, "login", 5)) {
            if (auth->a)
                system("/bin/sh");
            else
                fwrite("Password:\n", 1, 10, stdout);
        }
    }
}