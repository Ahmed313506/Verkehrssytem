#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

Fahrrad::Fahrrad(string Name):
    Fahrzeug(Name)
{
}

Fahrrad::Fahrrad(string Name, double Geschwindigkeit):
    Fahrzeug(Name, Geschwindigkeit)
{
}

double Fahrrad::dGeschwindigkeit() const
{
    //pro 20 km von Gesamtstrecke ist die Geschwidingkeit des Fahrrads um 10 Prozent reduziert
    //oder mit 0,9 multipliziert
    double neuGeschwindigkeit = p_dMaxGeschwindigkeit * pow(0.9, floor(p_dGesamtStrecke / 20));
    //Die Geschwindigkeit muss minimal 12 km/h sein
    return neuGeschwindigkeit > 12 ? neuGeschwindigkeit : 12;
}

void Fahrrad::vZeichnen(Weg& W) const
{
    bZeichneFahrrad(p_sName, W.getName(), p_dAbschnittStrecke / W.getLaenge() > 1 ? 1 : fabs(p_dAbschnittStrecke / W.getLaenge()), dGeschwindigkeit());
}
