CFLAGS = -fno-stack-protector -z execstack -no-pie -m32 -g

all: vuln
vuln: $(SRC)
	gcc $(CFLAGS) -o vuln vuln.c

clean:
	rm -f vuln
