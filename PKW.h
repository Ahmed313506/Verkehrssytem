/*
 * PKW.h
 *
 *  Created on: 5 Nov 2023
 *      Author: ahmedhossammohamed
 */


#pragma once
#include "Fahrzeug.h"
class PKW :
	public Fahrzeug
{
private:
	double p_dVerbrauch=0;
	double p_dTankvolumen=0;
	double p_dTankinhalt=0;

public:


	PKW(); // default konstruktor
	PKW(string sName);
	PKW(string sName, double dMaxGeschwindigkeit);
	PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen=550);

	virtual void vAusgeben() override;
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity())override ;
	virtual void vSimulieren() override;
	virtual int check_type(){ return 1; };
	 virtual void vAusgeben(ostream& os) override ;
	 PKW& operator=(const PKW& P);

	virtual ~PKW();


};
