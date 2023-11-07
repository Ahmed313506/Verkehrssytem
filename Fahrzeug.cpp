/*
 * New.cpp
 *
 *  Created on: 2 Nov 2023
 *      Author: ahmedhossammohamed
 */

#include "Fahrzeug.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

int Fahrzeug::p_iMaxID =0;


Fahrzeug::Fahrzeug(): p_iID(++p_iMaxID){
		cout << "erzeugtes Fahrzeug: " << p_sName << " " << p_iID << endl;
	}

Fahrzeug::Fahrzeug(string name) :
		p_sName(name),
		p_iID(++p_iMaxID)
	{
		cout << "erzeugtes Fahrzeug: " << p_sName << " " << p_iID << endl;
	}



Fahrzeug::~Fahrzeug(){
		cout << "geloeschtes Fahrzeug: " << p_sName << " " << p_iID << endl;
	}

Fahrzeug::Fahrzeug(string name, double maxGeschwindigkeit): //4.2.5
		p_sName(name),
		p_dMaxGeschwindigkeit(maxGeschwindigkeit>0? maxGeschwindigkeit:0),
		p_iID(++p_iMaxID)
	{
		cout << "erzeugtes Fahrzeug: " << p_sName << " maxGeschwindigkeit=" << p_dMaxGeschwindigkeit << endl;
	}


void Fahrzeug::vKopf(){// Aufgabe 4.2.6
	cout << setiosflags(ios::left)
		<< setw(5) << "ID"
		<< setiosflags(ios::right)
		<< setw(10) << "Name"
		<< setw(30) << "MaxGeschwindigkeit(km/h)"
		<< setw(20) << "Gesamtstrecke(km)"
		<< setw(25) << "Geschwindigkeit(km/h)"
		<< setw(20) << "Tankinhalt(L)"
		<< endl;
	cout << setfill('-') << setw(110)<<"" << setfill(' ')<<endl;

}

void Fahrzeug::vSimulieren(){ //Aufgabe 4.2.8 Simulation

	if (dGlobaleZeit != p_dZeit){
	double dZeitraum = dGlobaleZeit -   p_dZeit;
	p_dGesamtZeit += dZeitraum;
	p_dZeit = dGlobaleZeit;
	p_dGesamtStrecke += dGeschwindigkeit() * dZeitraum;
	}
}

void Fahrzeug::vAusgeben(){// Aufgabe 4.2.6a
	cout << setiosflags(ios::right)
		<< setw(6) << p_iID
		<< setw(10) << p_sName
		<< setw(20) << p_dMaxGeschwindigkeit
		<< setw(20) << p_dGesamtStrecke
		<< setw(25) << dGeschwindigkeit();




}
double Fahrzeug::dTanken(double dMenge){ // Ergibt sich 0 wenn es kein PKW gibt
	return 0;
}

void Fahrzeug::vAusgeben(ostream& os){// Aufgabe 4.4.1
	os << setiosflags(ios::right)
		<< setw(5) << this->p_iID
		<< setw(10) << this->p_sName
		<< setw(20) << this->p_dMaxGeschwindigkeit
		<< setw(20) << this->p_dGesamtStrecke
		<< setw(25) << this->dGeschwindigkeit();
}

ostream& operator<<(ostream& os, Fahrzeug& fahrzeug){ // 4.4.2 Ausgabeoperator
	fahrzeug.vAusgeben(os);
	return os;
}

bool Fahrzeug::operator<(const Fahrzeug& fahrzeug){ //4.4.4 vergleichsoperator
	return (p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke);
}

Fahrzeug& Fahrzeug::operator =(const Fahrzeug &fahrzeug){// 4.4.5 Zuweisungsoperator
	 //p_ID kann nicht kopiert werden, weil es eine konstante variable ist
	    //nur die Stammdaten kopieren
	p_sName = fahrzeug.p_sName;
	p_dGesamtStrecke = fahrzeug.p_dGesamtStrecke;
	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
	p_dGesamtZeit = fahrzeug.p_dGesamtZeit;
	p_dZeit = fahrzeug.p_dZeit;
	return *this;
}




