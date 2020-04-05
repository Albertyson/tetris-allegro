#ifndef PIEZAO_H
#define PIEZAO_H
#include "Pieza.h"
#include "Posicion.h"
#include <vector>
class PiezaO : public Pieza{
	public:
		PiezaO(const Pieza&);
		virtual ~PiezaO();
		PiezaO();		
		int menor(vector<int>);
		virtual void mover(Pieza&,int,char **)const; 
};
#endif
