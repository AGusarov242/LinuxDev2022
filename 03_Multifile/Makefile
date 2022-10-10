CFLAGS = -Wall -fPIC
GENERATES = prog prog-a prog-so *.a *.so
TRASH = *.o *~ o.* *.txt

all: prog prog-a prog-so

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^
	
liboutput.so: const.o fun.o
	cc -shared $^ -o $@

%.o: %.c
	cc $< $(CFLAGS) -c -o $@

prog: const.o fun.o prog.o
	cc $^ -o $@
	
prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@
	
prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@
	
test_prog: prog
	./$< 2> /dev/null 1> $@_0.txt
	./$< a1 1> $@_1.txt
	./$< a1 a2 a3 1> $@_3.txt

test_prog_a: prog-a
	./$< 2> /dev/null 1> $@_0.txt
	./$< a1 1> $@_1.txt
	./$< a1 a2 a3 1> $@_3.txt
	
test_prog_so: prog-so
	LD_LIBRARY_PATH=`pwd` ./$< 2> /dev/null 1> $@_0.txt
	LD_LIBRARY_PATH=`pwd` ./$< a1 1> $@_1.txt
	LD_LIBRARY_PATH=`pwd` ./$< a1 a2 a3 1> $@_3.txt

test: test_prog test_prog_a test_prog_so
	cmp $<_0.txt $<_a_0.txt
	cmp $<_0.txt $<_so_0.txt
	cmp $<_so_0.txt $<_a_0.txt
	cmp $<_1.txt $<_a_1.txt
	cmp $<_1.txt $<_so_1.txt
	cmp $<_so_1.txt $<_a_1.txt
	cmp $<_3.txt $<_a_3.txt
	cmp $<_3.txt $<_so_3.txt
	cmp $<_so_3.txt $<_a_3.txt

clean: 
	rm -rf $(TRASH) $(GENERATES)
