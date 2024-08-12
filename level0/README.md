```
0x8048ed4 <main+20>     call   0x8049710 <atoi>
0x8048ed9 <main+25>     cmp    $0x1a7,%eax
```

We can see atoi is called and the retrun is compared to 0x1a7 -> (423).

By testing with args we can easy understand that argv[1] is being atoied.

level0 without any args will segfault.

./level0 432
> whoami
> level1
> cat /home/user/level1/.pass