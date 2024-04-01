#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include "Tempolimit.h"
#include <memory>

class Weg;
class Fahrzeug;

class Kreuzung :
    public Simulationsobjekt
{
public:
    Kreuzung(string Name, double Tank);
    static void vVerbinde(string, string, double, shared_ptr<Kreuzung>, shared_ptr<Kreuzung>, Tempolimit);

    void vTanken(Fahrzeug&);
    void vAnnahme(unique_ptr<Fahrzeug> F);
    void vAnnahme(unique_ptr<Fahrzeug> F, double);
    void vSimulieren();
    Weg& pZufaelligerWeg(Weg&);

    double getTankstelle() { return p_dTankstelle; };

private:
    list<shared_ptr<Weg>> p_pWege;
    double p_dTankstelle;
};

