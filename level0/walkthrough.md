First we have the binary `level0`
We try to run it with no variables - segmentation fault
We try with more variables, different ones and we get - `No!`
So we run gdb on the binary and then `disas main`
We try to look fo the cmp functin in the asm code and first we see these 2 lines
```
   0x08048ed9 <+25>:    cmp    $0x1a7,%eax
   0x08048ede <+30>:    jne    0x8048f58 <main+152>

```
So a condition checking the value of argv in the eax register. So as we try to print the value of  `0x1a7` we get `$1 = 423`
Now when we try to run the binary 
```
level0@RainFall:~$ ./level0 423
$ whoami
level1
$ cd /home/user/level1
$ cat .pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a

```
