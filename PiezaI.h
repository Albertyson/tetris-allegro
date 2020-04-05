#ifndef PiezaI_H
#define PiezaI_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaI : public Pieza{
	public:
		PiezaI(const Pieza&);
		virtual ~PiezaI();
		PiezaI();
		int menor(vector<int>);
		virtual void rotari(Pieza&,int&,int&,char**)const;
		virtual void rotard(Pieza&,int&,int&,char**)const;
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
