/*
 * PKW.cpp
 *
 *  Created on: 5 Nov 2023
 *      Author: ahmedhossammohamed
 */

#include "PKW.h"



PKW::PKW()
{
	cout << "neuer PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << "/" << p_dTankvolumen << endl;
}
PKW::PKW(string sName):Fahrzeug(sName)
{
	cout << "neuer PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << "/" << p_dTankvolumen << endl;
}
PKW::PKW(string sName, double dMaxGeschwindigkeit) :Fahrzeug(sName, dMaxGeschwindigkeit)
{
	cout << "neuer PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << "/" << p_dTankvolumen << endl;
}
PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :Fahrzeug(sName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),					//Aufgabe 4.3.2
	p_dTankvolumen(dTankvolumen),
	p_dTankinhalt(dTankvolumen / 2.0)
{
	cout << "neuer PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << " " << p_dTankvolumen << endl;
}
double PKW::dTanken(double dMenge){ // 4.3.2 Tanken funktion
	if (dMenge <= 0 || dMenge>(p_dTankvolumen - p_dTankinhalt)){
		dMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dMenge;
	}
	else{
	p_dTankinhalt += dMenge;
	return dMenge;
	}
}
void PKW::vSimulieren(){ //Aufgabe 4.3.2
	if (dGlobaleZeit != p_dZeit && p_dTankinhalt != 0){
		double Zeitraum = dGlobaleZeit - p_dZeit;
				double Strecke = dGeschwindigkeit() * Zeitraum;
				p_dGesamtStrecke += Strecke;
				p_dGesamtZeit += Zeitraum;
				p_dZeit = dGlobaleZeit;
				p_dTankinhalt = (Strecke / 100) * p_dVerbrauch > p_dTankinhalt ? 0 :
					p_dTankinhalt - (Strecke / 100) * p_dVerbrauch;
	}
	double str = p_dGesamtStrecke;
	Fahrzeug::vSimulieren();

	p_dTankinhalt -= p_dVerbrauch / 100 * (p_dGesamtStrecke - str);
	if (p_dTankinhalt < 0)
		p_dTankinhalt = 0;

}
void PKW::vAusgeben(){     //Aufgabe 4.3.2
	Fahrzeug::vAusgeben();
	char spc[20];
	sprintf(spc, "%.2f/%.2f", p_dTankinhalt,p_dTankvolumen);
	cout << setw(20) << spc;
}
void PKW::vAusgeben(ostream& os){
	Fahrzeug::vAusgeben(os);
	char buf[20];
	sprintf(buf, "%.2f/%.2f", p_dTankinhalt, p_dTankvolumen);
	os << setw(20) << buf;
}  // passing the os to print the object throught the basisclass


PKW& PKW::operator=(const PKW& P)
{
	Fahrzeug::operator=(P);
	p_dVerbrauch = P.p_dVerbrauch;
	p_dTankvolumen = P.p_dTankvolumen;
	return *this;
}



PKW::~PKW()
{
	cout << "geloeschter PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << " " << p_dTankvolumen << endl;
}

