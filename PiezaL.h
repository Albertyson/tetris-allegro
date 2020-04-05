#ifndef PIEZAL_H
#define PIEZAL_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaL : public Pieza{
	public:
		PiezaL(const Pieza&);
		virtual ~PiezaL();
		PiezaL();
		int menor(vector<int>);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
