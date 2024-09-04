Well well well, how the turn tables ?

The binary is sTOOpid as hell.

`/home/user/end/.pass` is being open, some bytes are being read to a buffer. buffer[atoi(argv[1])] is being set to \0.

If the buffer and argv[1] are the same then `/bin/sh` will be launch with execl.

Since argv[1] will be atoied then we just need to provide an empty string.

`./bonus3 ''`

Done !