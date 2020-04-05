#include "PiezaS.h"
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
#include <ncurses.h>
using namespace std;
PiezaS::PiezaS(const Pieza& pp):Pieza(pp){
}
PiezaS::~PiezaS(){
//	delete [] tetrimino;
}
PiezaS::PiezaS() : Pieza(4,'S'){
	Posicion* tetriminio= new Posicion[4];
	//Establece las posiciones de cada mino
	tetriminio[0].setX(6);
	tetriminio[0].setY(1);
	tetriminio[1].setX(5);
	tetriminio[1].setY(1);
	tetriminio[2].setX(5);
	tetriminio[2].setY(2);
	tetriminio[3].setX(4);
	tetriminio[3].setY(2);
	setTetrimino(tetriminio,4);
}
void PiezaS::rotard(Pieza& p,int& nmov, int& nmovh, char** tab)const{
	//PiezaS pl= PiezaS();
	Posicion* tetrimino= p.getTetrimino();
	bool nodebe=false;
	if((nmov==3)||(nmovh==1)){//90 grados
		tetrimino[0].setX(tetrimino[0].getX()-2);
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()+1);
		tetrimino[3].setY(tetrimino[3].getY()+1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
				nodebe=true;
				break;
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX()+2);
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()-1);
			tetrimino[3].setY(tetrimino[3].getY()-1);
			nmovh=0;
			nmov=0;
		}
	}
	if((nmov==2)||(nmovh==2)){//180 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY()+2);
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()+1);
		tetrimino[3].setY(tetrimino[3].getY()-1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
				nodebe=true;
				break;
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX());
			tetrimino[0].setY(tetrimino[0].getY()-2);
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()-1);
			tetrimino[3].setY(tetrimino[3].getY()+1);
			nmovh--;
			nmov++;
		}
	}	
	
	if((nmov==1)||(nmovh==3)){//270 grados
		tetrimino[0].setX(tetrimino[0].getX()+2);
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()-1);
		tetrimino[3].setY(tetrimino[3].getY()-1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
				nodebe=true;
				break;
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX()-2);
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()+1);
			tetrimino[3].setY(tetrimino[3].getY()+1);
			nmovh--;
			nmov++;
		}
	}
	if((nmov==4)||(nmovh==4)){//0 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY()-2);
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()-1);
		tetrimino[3].setY(tetrimino[3].getY()+1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX());
			tetrimino[0].setY(tetrimino[0].getY()+2);
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()+1);
			tetrimino[3].setY(tetrimino[3].getY()-1);
			nmovh=3;
			nmov=1;
		}
	}
	p.setTetrimino(tetrimino,4);
}
void PiezaS::rotari(Pieza& p,int& nmov, int& nmovh,char** tab)const{
	//PiezaS pl= PiezaS();
	Posicion* tetrimino= p.getTetrimino();	
	bool nodebe=false;
	if((nmov==1)||(nmovh==3)){//270 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY()+2);
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()+1);
		tetrimino[3].setY(tetrimino[3].getY()-1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
				nodebe=true;
				break;
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX());
			tetrimino[0].setY(tetrimino[0].getY()-2);
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()-1);
			tetrimino[3].setY(tetrimino[3].getY()+1);
			nmovh=0;
			nmov=0;
		}
	}
	if((nmov==2)||(nmovh==2)){//180 grados
		tetrimino[0].setX(tetrimino[0].getX()-2);
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()+1);
		tetrimino[3].setY(tetrimino[3].getY()+1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
				nodebe=true;
				break;
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX()+2);
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()-1);
			tetrimino[3].setY(tetrimino[3].getY()-1);
			nmovh++;
			nmov--;
		}
	}
	if((nmov==3)||(nmovh==1)){//90 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY()-2);
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()-1);
		tetrimino[3].setY(tetrimino[3].getY()+1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX());
			tetrimino[0].setY(tetrimino[0].getY()+2);
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()+1);
			tetrimino[3].setY(tetrimino[3].getY()-1);
			nmovh++;
			nmov--;
		}
	}
	if((nmov==4)||(nmovh==4)){//0 grados
		tetrimino[0].setX(tetrimino[0].getX()+2);
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX());
		tetrimino[2].setY(tetrimino[2].getY());
		tetrimino[3].setX(tetrimino[3].getX()-1);
		tetrimino[3].setY(tetrimino[3].getY()-1);
		for(int k=0;k<4;k++){
			if((tetrimino[k].getX()<=0)||(tetrimino[k].getY()<=0)){
				nodebe=true;
				break;
			}else{
				if(tab[tetrimino[k].getX()][tetrimino[k].getY()]!='-'){
					nodebe=true;
					break;
				}	
			}
		}
		if(nodebe){
			tetrimino[0].setX(tetrimino[0].getX()-2);
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX());
			tetrimino[2].setY(tetrimino[2].getY());
			tetrimino[3].setX(tetrimino[3].getX()+1);
			tetrimino[3].setY(tetrimino[3].getY()+1);
			nmovh=1;
			nmov=3;
		}
	}
	p.setTetrimino(tetrimino,4);
}
void PiezaS::mover(Pieza& p,int nmov,char ** tab)const{
	Posicion* tetrimino= p.getTetrimino();	
	bool nodebe=false;
	vector<int> posx;//posiciones en x
	vector<int> posy;//posiciones en y
	for(int k=0;k<4;k++){
		posx.push_back(tetrimino[k].getX());
		posy.push_back(tetrimino[k].getY());
	}
	if(nmov==1){//izquierda
		for(int k=0;k<4;k++){
			if(tab[posx[k]-1][posy[k]]!='-'){
				nodebe=true;
				break;
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
		for(int k=0;k<4;k++){
			if(tab[posx[k]+1][posy[k]]!='-'){
				nodebe=true;
				break;
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
		for(int k=0;k<4;k++){
			if(tab[posx[k]][posy[k]+1]!='-'){
				nodebe=true;
				break;
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
int PiezaS::menor(vector<int> pos){
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