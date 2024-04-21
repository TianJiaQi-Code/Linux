# ---------- 静态库 ----------
# libmymath.a:sub.o add.o
# 	ar -rc $@ $^

# %.o:%.c
# 	gcc -c $<

# .PHONY:clean
# clean:
# 	rm -rf *.o output libmymath.a

# .PHONY:output
# output:
# 	mkdir output
# 	cp -rf *.h output
# 	cp libmymath.a output

# ---------- 动态库 ----------
libmymath.so:add.o sub.o
	gcc -shared -o $@ $^

%.o:%.c
	gcc -fPIC -c $<

.PHONY:clean
clean:
	rm -rf libmymath.so *.o DynamicLib

.PHONY:DynamicLib
DynamicLib:
	mkdir DynamicLib
	cp *.h DynamicLib
	cp libmymath.so DynamicLib