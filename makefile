Tetris: Posicion.o Pieza.o PiezaL.o PiezaJ.o PiezaT.o PiezaO.o PiezaI.o PiezaS.o PiezaZ.o main2.o 
	g++ Posicion.o Pieza.o PiezaL.o PiezaJ.o PiezaT.o PiezaO.o PiezaI.o PiezaS.o PiezaZ.o main2.o `allegro-config --cflags --libs` -o Tetris

Posicion.o: Posicion.cpp Posicion.h
	g++ Posicion.cpp -lncurses -c

Pieza.o: Pieza.cpp Pieza.h
	g++ Pieza.cpp -c

PiezaL.o: PiezaL.cpp PiezaL.h Pieza.h Posicion.h
	g++ PiezaL.cpp -c

PiezaJ.o: PiezaJ.cpp PiezaJ.h Pieza.h Posicion.h
	g++ PiezaJ.cpp -c

PiezaT.o: PiezaT.cpp PiezaT.h Pieza.h Posicion.h
	g++ PiezaT.cpp -lncurses -c

PiezaO.o: PiezaO.cpp PiezaO.h Pieza.h Posicion.h
	g++ PiezaO.cpp -c

PiezaI.o: PiezaI.cpp PiezaI.h Pieza.h Posicion.h
	g++ PiezaI.cpp -c

PiezaS.o: PiezaS.cpp PiezaS.h Pieza.h Posicion.h
	g++ PiezaS.cpp  -c

PiezaZ.o: PiezaZ.cpp PiezaZ.h Pieza.h Posicion.h
	g++ PiezaZ.cpp  -c

main2.o: main2.cpp Pieza.h PiezaL.h PiezaJ.h PiezaT.h PiezaO.h PiezaI.h PiezaS.h PiezaZ.h
	g++ main2.cpp `allegro-config --cflags --libs` -c

