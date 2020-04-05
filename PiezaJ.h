#ifndef PIEZAJ_H
#define PIEZAJ_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaJ : public Pieza{
	public:
		PiezaJ(const Pieza&);
		virtual ~PiezaJ();
		PiezaJ();		
		int menor(vector<int>);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
