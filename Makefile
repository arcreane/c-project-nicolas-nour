EXEC : main.o file.o
	gcc -o EXEC main.o file.o

main.o : main.c
	gcc -c -Wall main.c

file.o : file.c
	gcc -c -Wall file.c