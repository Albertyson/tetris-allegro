#include "Posicion.h"
using namespace std;
Posicion::Posicion(const Posicion& p){
	x=p.x;
	y=p.y;
}
Posicion::Posicion(int xx,int yy){
	x=xx;
	y=yy;
}
int Posicion::getX(){
	return x;
}
int Posicion::getY(){
	return y;
}
void Posicion::setX(int xx){
	x=xx;
}
void Posicion::setY(int yy){
	y=yy;
}