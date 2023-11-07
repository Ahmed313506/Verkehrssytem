/*
 * Fahrrad.h
 *
 *  Created on: 5 Nov 2023
 *      Author: ahmedhossammohamed
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug // inhertiance of the derived class Fahrrad to the public attributes and methods of the superclass/basis class

{
public:
	Fahrrad();
	Fahrrad(string name, double maxGeschwindigkeit);

	virtual double dGeschwindigkeit() override  ;
	virtual void vAusgeben() override;
	virtual void vSimulieren() override;

	virtual int check_type(){ return 2; };
//	virtual void vAusgabe(ostream& oStream) override;

	virtual ~Fahrrad();
};
#endif /* FAHRRAD_H_ */
