#ifndef PIEZA_H
#define PIEZA_H
#include "Posicion.h"
using namespace std;
class Pieza{
	
	int minos;
	char id;
	Posicion* tetrimino;
	public:
		Pieza(const Pieza&);
		Pieza(int,char);
		virtual ~Pieza();
		int getMinos();
		char getId();
		Posicion* getTetrimino()const;
		void setTetrimino(Posicion*,const int);
		void setMinos(int);
		void setId(char);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char**)const;
		//Pieza& operator=(Pieza&);
};
#endif
