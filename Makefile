EXEC : main.o huffman.o
	gcc -o EXEC main.o huffman.o

main.o : main.c
	gcc -c -Wall main.c

huffman.o : huffman.c
	gcc -c -Wall huffman.c