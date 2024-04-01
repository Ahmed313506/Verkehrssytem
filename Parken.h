#pragma once
#include "Verhalten.h"

class Losfahren;
class Parken :
    public Verhalten
{
public:
    Parken(Weg& weg, double StartZeit);

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) throw(Losfahren) override;
private:
    double p_dStart;
};

