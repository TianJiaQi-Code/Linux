.PHONY:all
all:A B

B:ProcessB.c
	gcc -o $@ $^
A:ProcessA.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f A B