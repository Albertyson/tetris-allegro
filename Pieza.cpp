#include "Posicion.h"
#include "Pieza.h"
using namespace std;
//constructor de copia
Pieza::Pieza(const Pieza& p){
	minos=p.minos;
	id=p.id;
	tetrimino=p.tetrimino;
	for(int i=0;i<minos;i++)
		tetrimino[i]=p.tetrimino[i];
}
//constructor de pieza
Pieza::Pieza(int m,char i){
	setMinos(m);
	setId(i);
	tetrimino=new Posicion [m];
}
//destructor
Pieza::~Pieza(){
	delete [] tetrimino;;
}
//getters & setters
int Pieza::getMinos(){
	return minos;
}
char Pieza::getId(){
	return id;
}
Posicion* Pieza::getTetrimino()const{
	return tetrimino;
}
void Pieza::setMinos(int m){
	minos=m;
}
void Pieza::setId(char i){
	id=i;
}
void Pieza::setTetrimino(Posicion* tt,const int n){
	//Posicion* tetrimino=new Posicion [n];
	for(int i=0;i<n;i++){
		tetrimino[i]=tt[i];
	}
}
void Pieza::rotari(Pieza& p,int& n,int& m,char ** t)const{
	//return p;
} 
void Pieza::rotard(Pieza& p,int& n,int& m,char ** t)const{
	//return p;
} 
void Pieza::mover(Pieza& p,int n,char** t)const{
	//return p;
}
/*Pieza& Pieza::operator=(Pieza& p){
	this->id=p.getId();
	this->minos=p.getMinos();
	for(int i=0;i<4;i++){
		this->tetrimino[i]=p.tetrimino[i];
	}	
	return *this;
}*/