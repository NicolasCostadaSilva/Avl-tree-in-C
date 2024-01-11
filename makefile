parametrosCompilacao=-Wall #-Wshadow
nomePrograma=trab

all: $(nomePrograma)

$(nomePrograma): main.o avl.o fila.o
	gcc -o $(nomePrograma) main.o avl.o fila.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

avl.o: avl.h avl.c fila.h
	gcc -c avl.c $(parametrosCompilacao)

fila.o: fila.c fila.h
	gcc -c fila.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
