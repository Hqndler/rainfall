#include <iostream>
#include <string.h>

class N {
    private:
        int number;
        char annotation[100];
    
    public:
        N(int x) : number(x) {}
        void setAnnotation(char *a) {memcpy(annotation, a, strlen(a));}
        virtual int operator+(N &r) {return number + r.number;}
        virtual int operator-(N &r) {return number - r.number;}
};

int main(int argc, char **argv) {
    if (argc < 2)
        return 1;
 
    N *x = new N(5);
    N *y = new N(6);
    N &fiv = *x;
    N &six = *y;

    fiv.setAnnotation(argv[1]);

    return fiv + six;
}