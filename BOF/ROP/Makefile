
CFLAGS = -fno-stack-protector -no-pie -m32 -g

all: rop
rop: $(SRC)
	gcc $(CFLAGS) -o rop rop.c

clean:
	rm -f rop
