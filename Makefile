plate: plate.o bst.o  plate.h
	gcc -g -o plate plate.o bst.o 
plate.o: plate.c plate.h
	gcc -g -c plate.c
bst.o: bst.c plate.h
	gcc -g -c bst.c
clean:
	rm bst.o plate.o plate
