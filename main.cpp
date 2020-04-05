#include <ncurses.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "Pieza.h"
#include "PiezaL.h"
#include "PiezaJ.h"
using namespace std;
void printtab(char**);
//void delay(int);
int main(int argc, char * argv[]){
	PiezaJ pl=PiezaJ();
	char ** tablero=new char*[17];
	for(int i=0;i<17;i++){
		tablero[i]=new char[12];
	}
	for(int i=0;i<17;i++){
		for(int j=0;j<12;j++){
			if((i==16)||(i==0)||(j==0)||(j==11))
				tablero[j][i]='*';
			else
				tablero[j][i]='-';
		}
	}
	initscr();
	printtab(tablero);
	int mov=0;
	int delay=0;
	int rot=4;//rotar a la izquierda
	int rot2=4;//rotar a la derecha
	do{
		//dibujar la pieza
		for(int k=0;k<4;k++)
			tablero[pl.getTetrimino()[k].getX()][pl.getTetrimino()[k].getY()]=pl.getId();
		printtab(tablero);
		char movimiento=getch();
		//borrar la posicion anterior
		for(int k=0;k<4;k++){
			tablero[pl.getTetrimino()[k].getX()][pl.getTetrimino()[k].getY()]='-';
			printtab(tablero);
		}
		clear();
		if(movimiento=='e'){
			//rotar a la derecha
			if((rot2==4)||(rot2==0)||(rot==4)||(rot==0)){
				rot2=1;
				rot=3;
			}else{
				rot2++;
				rot--;
			}
		}else if(movimiento=='q'){
			//rotar a la izquierda
			if((rot==4)||(rot==0)||(rot2==4)||(rot2==0)){
				rot=1;
				rot2=3;
			}else{
				rot++;
				rot2--;
			}
		}else if(movimiento=='a'){//mover hacia la izquierda
			mov=1;
		}else if(movimiento=='d'){//mover hacia la derecha
			mov=2;
		}else if(movimiento=='s'){//mover hacia abajo
			mov=3;
		}
		
		if(movimiento=='e'){
				pl.rotard(pl,rot,rot2,tablero);
		}else if(movimiento=='q'){
				pl.rotari(pl,rot,rot2,tablero);
		}
		if((movimiento=='a')||(movimiento=='s')||(movimiento=='d')){
				pl.mover(pl,mov,tablero);
		}
	}while(mov>=0);//fin del do
	endwin();
	return 0;
}
void printtab(char ** tab){
	stringstream ss;
	clear();
	for(int i=0;i<17;i++){
		for(int j=0;j<12;j++){
			ss<<tab[j][i];
		}
		ss<<"\n";
	}
	const char * c=(ss.str()).c_str();
	printw("%s",c);
	refresh();
}
/*void delay(int secs){
	 for(int i = ((float)time(NULL) + secs/1000.0f); time(NULL) != i; time(NULL));
}*/