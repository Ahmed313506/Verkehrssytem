#pragma once
#include "Simulationsobjekt.h"
#include<list>
#include <memory>
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include<string>

using namespace std;
class Fahrzeug;
class Kreuzung;

class Weg :
    public Simulationsobjekt
{
public:

    //konstruktoren
    Weg() = default;
    Weg(string Name, double Laenge, Tempolimit = Tempolimit::Autobahn, weak_ptr<Kreuzung> Ziel = weak_ptr<Kreuzung>());

    //Methoden
    void vSimulieren() override;
    void vAusgeben() override;
    void vAusgeben(ostream&) const override;
    static void vKopf();
    void vAnnahme(unique_ptr<Fahrzeug> F);
    void vAnnahme(unique_ptr<Fahrzeug> F, double);
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

    //setters und getters
    double getTempolimit() { return  (double)p_eTempolimit; };
    double getLaenge() { return p_dLaenge; };
    shared_ptr<Weg> getRueckweg() { return p_pRueckweg.lock(); }
    shared_ptr<Kreuzung> getZiel() { return p_pZiel.lock(); }
    void setRueckweg(shared_ptr<Weg> Weg) { p_pRueckweg = Weg; }
protected:
    Tempolimit p_eTempolimit;
    double p_dLaenge;
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
    weak_ptr<Weg> p_pRueckweg;
    const weak_ptr<Kreuzung> p_pZiel;
};

