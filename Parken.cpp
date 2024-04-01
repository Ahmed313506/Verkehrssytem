#include "Parken.h"
#include "Fahrzeug.h"
#include <iostream>
#include "Losfahren.h"
#include <cmath>

Parken::Parken(Weg& weg, double StartZeit):
	Verhalten(weg), p_dStart(StartZeit)
{
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) throw(Fahrausnahme)
{
	if ((p_dStart - dGlobaleZeit) > 0.0000001 ) {
		return 0.0;
	}
	else {
		aFzg.setZeit(p_dStart);
		Losfahren exception(aFzg, p_pWeg);
		throw exception;
	}
}
