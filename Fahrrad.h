#pragma once
#include <math.h>
#include "Fahrzeug.h"


class Fahrrad :
    public Fahrzeug //Abgeleitet von Fahrzeug
{
public:
    //Konstruktoren
    Fahrrad() = default;
    Fahrrad(string Name);
    Fahrrad(string Name, double Geschwindigkeit);

    //Methoden
    double dGeschwindigkeit() const override;
    void vZeichnen(Weg&) const override;
};

