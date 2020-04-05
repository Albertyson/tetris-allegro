#ifndef PiezaS_H
#define PiezaS_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaS : public Pieza{
	public:
		PiezaS(const Pieza&);
		virtual ~PiezaS();
		PiezaS();
		int menor(vector<int>);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
