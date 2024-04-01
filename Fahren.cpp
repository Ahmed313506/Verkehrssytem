#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& weg) :
	Verhalten(weg)
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) throw(Streckenende)
{
	double Strecke = aFzg.dGeschwindigkeit() * dZeitIntervall + aFzg.getAbschnittStrecke();
	if (Strecke > p_pWeg.getLaenge()) {
		if (p_pWeg.getLaenge() - aFzg.getAbschnittStrecke() <= 0.001) {
			Streckenende exception(aFzg, p_pWeg);
			throw exception;
		}
		return p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();
		
	}
	else if (Strecke < p_pWeg.getLaenge()) {
		return aFzg.dGeschwindigkeit() * dZeitIntervall;
	}
}
