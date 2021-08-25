main.out: main.o foo.o bar.o
	gcc -o main.out main.o foo.o bar.o

main.o: def.h main.c
	gcc -c -o main.o main.c
foo.o: def.h foo.c
	gcc -c -o foo.o foo.c
bar.o: def.h bar.c
	gcc -c -o bar.o bar.c
