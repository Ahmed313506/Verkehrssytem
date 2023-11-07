/*
 * New.h
 *
 *  Created on: 2 Nov 2023
 *      Author: ahmedhossammohamed
 */

#pragma once // Alternative for ifdef and def
#include <iostream>
#include <string>
#include <iomanip> // library used for formatting as setw
#include <limits>
using namespace std;

extern double dGlobaleZeit;

class Fahrzeug {



	protected:
	string p_sName = "";
	const int p_iID = 0;
	double p_dMaxGeschwindigkeit=0;
	double p_dGesamtStrecke=0;
	double p_dGesamtZeit=0;
	double p_dZeit=0;

	static int p_iMaxID; // Es sollte in private sein

	public:


	Fahrzeug();

	Fahrzeug(string name);
	Fahrzeug(string name, double maxGeschwindigkeit);
	Fahrzeug(const Fahrzeug &fahrzeug) = delete;
	static void vKopf();
	 virtual void vAusgeben();
	virtual void vSimulieren();
	virtual double dTanken(double dMenge =numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit()  {
		 return p_dMaxGeschwindigkeit;
	 };
	virtual int check_type(){ return 0; };
	 virtual void vAusgeben(ostream& oStream);
	bool operator <(const Fahrzeug& fahrzeug);
	Fahrzeug& operator =(const Fahrzeug& fahrzeug);
	void test();
	virtual ~Fahrzeug();
};

ostream& operator<<(ostream& oStream, Fahrzeug& fahrzeug);

