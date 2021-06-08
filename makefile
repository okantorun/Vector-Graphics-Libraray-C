target: prog

prog:src/main.c src/myheader.c src/myheader.h
	gcc src/main.c src/myheader.c -lm -o run
	./run
