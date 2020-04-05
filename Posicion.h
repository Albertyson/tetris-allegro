#ifndef POSICION_H
#define POSICION_H
using namespace std;
class Posicion{
	int x;
	int y;
	public:
		Posicion(const Posicion&);
		Posicion(int=0,int=0);
		int getX();
		int getY();
		void setX(int);
		void setY(int);
};
#endif