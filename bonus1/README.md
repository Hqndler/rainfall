Read the source.c it will be mush simplier to understand.

We will overflow the value of str into n.

The binary takes 2 argv. The first one needs to be a negative int and the second will be a string to big for memcpy leading to an overflow.

memcpy only take a size_t (aka unsigned int) we will need a negative number that once multiplied by 4 and overflowed give's us 44. -2147483637 will do the job !

`./bonus1 -2147483637 $(python -c "print('a' * 40 + 'FLOW')")`

Why FLOW ? 0x574f4c46 is WOLF in hex in reverse (man ascii).

Wolf ? :thinking: