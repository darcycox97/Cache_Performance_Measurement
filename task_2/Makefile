 OPT = -O1 				

default: assignment

# use different targets for the different assignment tasks
# example:
assignment: assignment.o 
	gcc $(OPT) -o assignment assignment.o

assignment.o: assignment.c
	gcc $(OPT) -c assignment.c


clean:
	rm -f *.o
	rm -f assignment

