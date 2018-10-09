 OPT = -O1 				

default: matrix1 matrix2 matrix3

matrix1: matrix1.o 
	gcc $(OPT) -o matrix1 matrix1.o

matrix1.o: matrix1.c
	gcc $(OPT) -c matrix1.c

matrix2: matrix2.o 
	gcc $(OPT) -o matrix2 matrix2.o

matrix2.o: matrix2.c
	gcc $(OPT) -c matrix2.c

matrix3: matrix3.o 
	gcc $(OPT) -o matrix3 matrix3.o

matrix3.o: matrix3.c
	gcc $(OPT) -c matrix3.c

clean:
	rm -f *.o
	rm -f matrix1
	rm -f matrix2
	rm -f matrix3

