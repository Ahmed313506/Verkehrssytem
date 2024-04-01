
#include "Verhalten.h"

class Streckenende;

class Fahren :
    public Verhalten
{
public:
    Fahren(Weg&);
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) throw(Streckenende) override;
};
