All:main

main:main.o functions.o  sort_func.o
	gcc -fopenmp main.o functions.o sort_func.o -o main -lm

main.o:functions.c main.c sort_func.c functions.h sort.h  
	gcc -c main.c functions.c sort_func.c

functions.o:functions.c functions.h sort.h
	gcc -c functions.c

sort_func.o:sort_func.c sort.h functions.h
	gcc -c sort_func.c
clean:
	rm *.o main
