#ifndef PIEZAT_H
#define PIEZAT_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaT : public Pieza{
	public:
		PiezaT(const Pieza&);
		virtual ~PiezaT();
		PiezaT();
		int menor(vector<int>);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
