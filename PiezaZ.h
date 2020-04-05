#ifndef PiezaZ_H
#define PiezaZ_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaZ : public Pieza{
	public:
		PiezaZ(const Pieza&);
		virtual ~PiezaZ();
		PiezaZ();
		int menor(vector<int>);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
