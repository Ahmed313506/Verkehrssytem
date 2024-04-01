#pragma once
#include "Fahrzeug.h"
#include <limits>
#include <iomanip>
#include <iostream>

using namespace std;


class PKW :
    public Fahrzeug //abgeleitet von Fahrzeug
{
public:
    //Konstruktoren
    PKW() = default;
    PKW(string Name);
    PKW(string Name, double Geschwindigkeit);
    PKW(string Name, double Geschwindigkeit, double Verbrauch, double Tankvolumen = 55);
    
    //Methoden
    double dTanken(double dMenge = std::numeric_limits<double>::infinity());
    double getTankinhalt() { return p_dTankinhalt; };
    void vSimulieren() override;
    void vAusgeben();
    void vAusgeben(ostream& o) const override;
    double dGeschwindigkeit() const override;
    void vZeichnen(Weg&) const override;
    
    //Operator "=" Überladung
    PKW& operator=(const PKW& P);
private:
    //Klassenmitglieder
    double p_dVerbrauch = 0;
    double p_dTankvolumen = 0;
    double p_dTankinhalt = 0;
};

