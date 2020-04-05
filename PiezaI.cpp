#include "PiezaI.h"
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
#include <ncurses.h>
using namespace std;
PiezaI::PiezaI(const Pieza& pp):Pieza(pp){
}
PiezaI::~PiezaI(){
//	delete [] tetrimino;
}
PiezaI::PiezaI() : Pieza(4,'I'){
	Posicion* tetriminio= new Posicion[4];
	//Establece las posiciones de cada mino
	tetriminio[0].setX(4);
	tetriminio[0].setY(1);
	tetriminio[1].setX(4);
	tetriminio[1].setY(2);
	tetriminio[2].setX(4);
	tetriminio[2].setY(3);
	tetriminio[3].setX(4);
	tetriminio[3].setY(4);
	setTetrimino(tetriminio,4);
}
void PiezaI::rotard(Pieza& p,int& nmov, int& nmovh, char** tab)const{
	//PiezaI pl= PiezaI();
	Posicion* tetrimino= p.getTetrimino();
	bool nodebe=false;
	if((nmov==3)||(nmovh==1)){//90 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX()+2);
		tetrimino[2].setY(tetrimino[2].getY()-2);
		tetrimino[3].setX(tetrimino[3].getX()+3);
		tetrimino[3].setY(tetrimino[3].getY()-3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX()-2);
			tetrimino[2].setY(tetrimino[2].getY()+2);
			tetrimino[3].setX(tetrimino[3].getX()-3);
			tetrimino[3].setY(tetrimino[3].getY()+3);
			nmovh=0;
			nmov=0;
		}
	}
	if((nmov==2)||(nmovh==2)){//180 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX()-2);
		tetrimino[2].setY(tetrimino[2].getY()-2);
		tetrimino[3].setX(tetrimino[3].getX()-3);
		tetrimino[3].setY(tetrimino[3].getY()-3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX()+2);
			tetrimino[2].setY(tetrimino[2].getY()+2);
			tetrimino[3].setX(tetrimino[3].getX()+3);
			tetrimino[3].setY(tetrimino[3].getY()+3);
			nmovh--;
			nmov++;
		}
	}	
	
	if((nmov==1)||(nmovh==3)){//270 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX()-2);
		tetrimino[2].setY(tetrimino[2].getY()+2);
		tetrimino[3].setX(tetrimino[3].getX()-3);
		tetrimino[3].setY(tetrimino[3].getY()+3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX()+2);
			tetrimino[2].setY(tetrimino[2].getY()-2);
			tetrimino[3].setX(tetrimino[3].getX()+3);
			tetrimino[3].setY(tetrimino[3].getY()-3);
			nmovh--;
			nmov++;
		}
	}
	if((nmov==4)||(nmovh==4)){//0 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX()+2);
		tetrimino[2].setY(tetrimino[2].getY()+2);
		tetrimino[3].setX(tetrimino[3].getX()+3);
		tetrimino[3].setY(tetrimino[3].getY()+3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX()-2);
			tetrimino[2].setY(tetrimino[2].getY()-2);
			tetrimino[3].setX(tetrimino[3].getX()-3);
			tetrimino[3].setY(tetrimino[3].getY()-3);
			nmovh=3;
			nmov=1;
		}
	}
	p.setTetrimino(tetrimino,4);
}
void PiezaI::rotari(Pieza& p,int& nmov, int& nmovh,char** tab)const{
	//PiezaI pl= PiezaI();
	Posicion* tetrimino= p.getTetrimino();	
	bool nodebe=false;
	if((nmov==1)||(nmovh==3)){//270 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX()-2);
		tetrimino[2].setY(tetrimino[2].getY()-2);
		tetrimino[3].setX(tetrimino[3].getX()-3);
		tetrimino[3].setY(tetrimino[3].getY()-3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX()+2);
			tetrimino[2].setY(tetrimino[2].getY()+2);
			tetrimino[3].setX(tetrimino[3].getX()+3);
			tetrimino[3].setY(tetrimino[3].getY()+3);
			nmovh=0;
			nmov=0;
		}
	}
	if((nmov==2)||(nmovh==2)){//180 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()-1);
		tetrimino[2].setX(tetrimino[2].getX()+2);
		tetrimino[2].setY(tetrimino[2].getY()-2);
		tetrimino[3].setX(tetrimino[3].getX()+3);
		tetrimino[3].setY(tetrimino[3].getY()-3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()+1);
			tetrimino[2].setX(tetrimino[2].getX()-2);
			tetrimino[2].setY(tetrimino[2].getY()+2);
			tetrimino[3].setX(tetrimino[3].getX()-3);
			tetrimino[3].setY(tetrimino[3].getY()+3);
			nmovh++;
			nmov--;
		}
	}
	if((nmov==3)||(nmovh==1)){//90 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()+1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX()+2);
		tetrimino[2].setY(tetrimino[2].getY()+2);
		tetrimino[3].setX(tetrimino[3].getX()+3);
		tetrimino[3].setY(tetrimino[3].getY()+3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()-1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX()-2);
			tetrimino[2].setY(tetrimino[2].getY()-2);
			tetrimino[3].setX(tetrimino[3].getX()-3);
			tetrimino[3].setY(tetrimino[3].getY()-3);
			nmovh++;
			nmov--;
		}
	}
	if((nmov==4)||(nmovh==4)){//0 grados
		tetrimino[0].setX(tetrimino[0].getX());
		tetrimino[0].setY(tetrimino[0].getY());
		tetrimino[1].setX(tetrimino[1].getX()-1);
		tetrimino[1].setY(tetrimino[1].getY()+1);
		tetrimino[2].setX(tetrimino[2].getX()-2);
		tetrimino[2].setY(tetrimino[2].getY()+2);
		tetrimino[3].setX(tetrimino[3].getX()-3);
		tetrimino[3].setY(tetrimino[3].getY()+3);
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
			tetrimino[0].setY(tetrimino[0].getY());
			tetrimino[1].setX(tetrimino[1].getX()+1);
			tetrimino[1].setY(tetrimino[1].getY()-1);
			tetrimino[2].setX(tetrimino[2].getX()+2);
			tetrimino[2].setY(tetrimino[2].getY()-2);
			tetrimino[3].setX(tetrimino[3].getX()+3);
			tetrimino[3].setY(tetrimino[3].getY()-3);
			nmovh=1;
			nmov=3;
		}
	}
	p.setTetrimino(tetrimino,4);
}
void PiezaI::mover(Pieza& p,int nmov,char ** tab)const{
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
int PiezaI::menor(vector<int> pos){
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