#include "PKW.h"
#include "Fahren.h"
#include "Parken.h"
#include "Verhalten.h"
#include "Weg.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include <math.h>
#include <limits>

PKW::PKW(string Name):
	Fahrzeug(Name)
{
}

PKW::PKW(string Name, double Geschwindigkeit):
	Fahrzeug(Name, Geschwindigkeit)
{
}

PKW::PKW(string Name, double Geschwindigkeit, double Verbrauch, double Tankvolumen):
	Fahrzeug(Name, Geschwindigkeit),
	p_dVerbrauch(Verbrauch),
	p_dTankvolumen(Tankvolumen),
	p_dTankinhalt(Tankvolumen/2.0)
{
}

double PKW::dTanken(double dMenge)
{
	if (dMenge > (p_dTankvolumen - p_dTankinhalt)) {
		double Menge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return Menge;
	}
	else {
		p_dTankinhalt += dMenge;
		return dMenge;
	}

}

void PKW::vSimulieren()
{
	try {
		if (dGlobaleZeit != p_dZeit && p_dTankinhalt != 0) {
			double Zeitdiff = dGlobaleZeit - p_dZeit;
			double Strecke = p_pVerhalten->dStrecke(*this, Zeitdiff);
			p_dGesamtStrecke += Strecke;
			p_dAbschnittStrecke += Strecke;
			p_dGesamtZeit += Zeitdiff;
			p_dTankinhalt = (Strecke / 100.0) * p_dVerbrauch > p_dTankinhalt ? 0 :
				p_dTankinhalt - (Strecke / 100.0) * p_dVerbrauch;
			p_dZeit = dGlobaleZeit;
		}
	}catch (Fahrausnahme& exception) {
		exception.vBearbeiten();
	}
}

void PKW::vAusgeben()
{
	Fahrzeug::vAusgeben();
	cout
		<< setiosflags(ios::fixed)
		<< setprecision(2)
		<< setw(12)
		<< (p_dGesamtStrecke / 100.0) * p_dVerbrauch
		<< setw(8)
		<< setprecision(2)
		<< p_dTankinhalt;
}

void PKW::vAusgeben(ostream& o) const
{
	Fahrzeug::vAusgeben(o);
	o
		<< setiosflags(ios::fixed)
		<< setprecision(2)
		<< setw(12)
		<< (p_dGesamtStrecke / 100.0) * p_dVerbrauch
		<< setw(8)
		<< setprecision(2)
		<< p_dTankinhalt;
}

double PKW::dGeschwindigkeit() const
{
	Weg& weg = p_pVerhalten->getWeg();
	if (p_dMaxGeschwindigkeit > weg.getTempolimit()) {
		return weg.getTempolimit();
	}
	else {
		return p_dMaxGeschwindigkeit;
	}
}

void PKW::vZeichnen(Weg& W) const
{
	bZeichnePKW(p_sName, W.getName(), p_dAbschnittStrecke/W.getLaenge() > 1? 1: fabs(p_dAbschnittStrecke / W.getLaenge()), dGeschwindigkeit(), p_dTankinhalt);
}

PKW& PKW::operator=(const PKW& P)
{
	Fahrzeug::operator=(P);
	p_dVerbrauch = P.p_dVerbrauch;
	p_dTankvolumen = P.p_dTankvolumen;
	return *this;
}
