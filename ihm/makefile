FLAGS = -std=c99 -Wall -Wextra #-pedantic

carOxyIhm: main.o dataBuffer.o dataBuffer.o fenetre.o lecture.o button.o
	gcc $(FLAGS) main.o dataBuffer.o fenetre.o lecture.o button.o -o carOxyIhm.exe -lmingw32 -lSDLmain -lSDL -lSDL_ttf -mwindows

main.o: main.c dataBuffer.h fenetre.h lecture.h button.h
	gcc -c main.c $(FLAGS)

dataBuffer.o: dataBuffer.c dataBuffer.h fenetre.h
	gcc -c dataBuffer.c $(FLAGS)

fenetre.o: fenetre.c fenetre.h
	gcc -c fenetre.c $(FLAGS)

lecture.o: lecture.c lecture.h
	gcc -c lecture.c $(FLAGS)

button.o: button.c button.h
	gcc -c button.c $(FLAGS)

clean:
	rm -rf *.o carOxyIhm.exe