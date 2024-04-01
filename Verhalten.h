#pragma once

class Weg;
class Fahrzeug;

class Verhalten
{
public:
	Verhalten(Weg& weg);
	Verhalten(const Verhalten&) = delete;

	Weg& getWeg() { return p_pWeg; };

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;
protected:
	Weg& p_pWeg;
};

