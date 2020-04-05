#include "PiezaO.h"
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
#include <ncurses.h>
using namespace std;
PiezaO::PiezaO(const Pieza& pp):Pieza(pp){
}
PiezaO::~PiezaO(){
//	delete [] tetrimino;
}
PiezaO::PiezaO() : Pieza(4,'O'){
	Posicion* tetriminio= new Posicion[4];
	//Establece las posiciones de cada mino
	tetriminio[0].setX(4);
	tetriminio[0].setY(1);
	tetriminio[1].setX(4);
	tetriminio[1].setY(2);
	tetriminio[2].setX(5);
	tetriminio[2].setY(1);
	tetriminio[3].setX(5);
	tetriminio[3].setY(2);
	setTetrimino(tetriminio,4);
}
void PiezaO::mover(Pieza& p,int nmov,char ** tab)const{
	Posicion* tetrimino= p.getTetrimino();	
	bool nodebe=false;
	vector<int> posx;//posiciones en x
	vector<int> posy;//posiciones en y
	for(int k=0;k<4;k++){
		posx.push_back(tetrimino[k].getX());
		posy.push_back(tetrimino[k].getY());
	}
	if(nmov==1){//izquierda
		int men=17;
		for(int i=0;i<posx.size();i++){
			if(posx[i]<men){
				men=posx[i];
			}
		}
		for(int k=0;k<4;k++){
			if(posx[k]==men) {
				if(tab[posx[k]-1][posy[k]]!='-'){
					nodebe=true;
					break;
				}					
			}
		}
		if(!nodebe){
			tetrimino[0].setX(tetrimino[0].getX()-1);
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[2].setX(tetrimino[2].getX()-1);
			tetrimino[3].setX(tetrimino[3].getX()-1);
		}
	}
	if(nmov==2){//derecha
		int may=0;
		for(int i=0;i<posx.size();i++){
			if(posx[i]>may){
				may=posx[i];
			}
		}
		for(int k=0;k<4;k++){
			if(posx[k]==may) {
				if(tab[posx[k]+1][posy[k]]!='-'){
					nodebe=true;
					break;
				}					
			}
		}
		if(!nodebe){
			tetrimino[0].setX(tetrimino[0].getX()+1);
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[2].setX(tetrimino[2].getX()+1);
			tetrimino[3].setX(tetrimino[3].getX()+1);
		}
	}
	if(nmov==3){//abajo
		int may=0;
		for(int i=0;i<posy.size();i++){
			if(posy[i]>may){
				may=posy[i];
			}
		}
		for(int k=0;k<4;k++){
			if(posy[k]==may) {
				if(tab[posx[k]][posy[k]+1]!='-'){
					nodebe=true;
					break;
				}					
			}
		}
		if(!nodebe){
			tetrimino[0].setY(tetrimino[0].getY()+1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setY(tetrimino[2].getY()+1);
			tetrimino[3].setY(tetrimino[3].getY()+1);
		}
	}
	p.setTetrimino(tetrimino,4);
}
int PiezaO::menor(vector<int> pos){
	int men=20;
	for(int i=0;i<pos.size();i++){
		if(pos[i]<men){
			men=pos[i];
		}
	}
	return men;
}
/*int mayor(vector<int> pos){
	int may=0;
	for(int i=0;i<pos.size();i++){
		if(pos[i]>may){
			may=posx[i];
		}
	}
	return may;
}*/