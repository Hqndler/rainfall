typedef struct source
{
    char str1[40];
    char str2[32];
    int nb;
} t_struct;

int language = 0;

int greetuser(t_struct var) {
    char str[88]; // ?

    switch (language) {
    case 0:
        strcpy(str, "Hello "); // not called
        break;
    case 1:
        strcpy(str, "Hyvää päivää "); // same
        break;
    case 2:
        strcpy(str, "Goedemiddag! "); // same
        break;
    }
    strcat(str, var.str1);
    puts(str);
}

int main(int argc, char **argv) {
    t_struct var = {0};
    char *lang;

    if (argc != 3)
        return 1;
    
    strncpy(var.str1, argv[1], sizeof(var.str1));
    strncpy(var.str2, argv[2], sizeof(var.str2));
    lang = getenv("LANG");

    if (lang) {
        if (!memcmp(lang, "fi", 2))
            language = 1;
        else if (!memcmp(lang, "nl", 2))
            language = 2;
    }
    return greetuser(var);
}