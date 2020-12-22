main: main.c 
	gcc -o main main.c linkedListFunctions.c

.PHONY: all run clean

clean:
	del -f main.exe test.exe

run: main
	./main

test: test.c
	gcc -o test test.c linkedListFunctions.c
runtest: test
	./test
