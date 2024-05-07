.PHONY:all
all:A B

B:ProcessB.cc
	g++ -o $@ $^ -std=c++11
A:ProcessA.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f A B