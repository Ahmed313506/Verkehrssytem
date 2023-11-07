/*
 * Fahrrad.cpp
 *
 *  Created on: 5 Nov 2023
 *      Author: ahmedhossammohamed
 */

#include "Fahrrad.h"

#include <math.h>

Fahrrad::Fahrrad() : Fahrzeug(){

}
Fahrrad::Fahrrad(string sName, double dMaxGeschwindigkeit):Fahrzeug(sName, dMaxGeschwindigkeit)
{
}

double Fahrrad::dGeschwindigkeit(){ //4.3.3
	int iPower=(int)(p_dGesamtStrecke / 20);
	double dGeschwindigkeit = p_dMaxGeschwindigkeit*pow(0.9,iPower);
	if (dGeschwindigkeit < 12) dGeschwindigkeit = 12;
	return dGeschwindigkeit;
}
void Fahrrad::vSimulieren(){
	Fahrzeug::vSimulieren();
}
void Fahrrad::vAusgeben(){
	Fahrzeug::vAusgeben();

}


Fahrrad::~Fahrrad()
{
}

