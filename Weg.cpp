#include "Weg.h"
#include "Fahrrad.h"
#include "Kreuzung.h"
#include <iostream>
#include <iomanip>

using namespace std;

Weg::Weg(string Name, double Laenge, Tempolimit tempolimit, weak_ptr<Kreuzung> Ziel):
    Simulationsobjekt(Name), p_dLaenge(Laenge),p_eTempolimit(tempolimit), p_pZiel(Ziel)
{
}

void Weg::vSimulieren()
{
    p_pFahrzeuge.vAktualisieren();
    for (auto const& i : p_pFahrzeuge) {
        i->vSimulieren();
    }

    p_pFahrzeuge.vAktualisieren();
    for (auto const& i : p_pFahrzeuge) {
        i->vZeichnen(*this);
    }
}

void Weg::vAusgeben()
{
    Simulationsobjekt::vAusgeben();
    p_pFahrzeuge.vAktualisieren();

    cout
        << setw(1)
        << p_dLaenge
        << setw(5)
        << "(";
    string Fahrzeuge = "";
    for (auto const& i : p_pFahrzeuge) {
        Fahrzeuge += i->getName();
        Fahrzeuge += ", ";
    }

    cout
        << Fahrzeuge.substr(0, Fahrzeuge.length() - 2)
        << ")";
}

void Weg::vAusgeben(ostream& o) const
{

    Simulationsobjekt::vAusgeben(o);

    o
        << setw(15)
        << p_dLaenge
        << "("
        << setw(1);

    //ausgeben von Fahrzeugen
    string Fahrzeuge = "";
    for (auto const& i : p_pFahrzeuge) {
        Fahrzeuge += i->getName();
        Fahrzeuge += ", ";
    }

    o
        << Fahrzeuge.substr(0, Fahrzeuge.length() - 2) //es gibt ", " zusäzlich am Ende
        << ")";
}

void Weg::vKopf()
{
    cout
        << setiosflags(ios::left)
        << setw(5)
        << "ID"
        << setw(22)
        << "Name"
        << setw(16)
        << "Laenge"
        << setw(17)
        << "Fahrzeuge"
        << endl
        << string(60, '-')
        << endl;

}

void Weg::vAnnahme(unique_ptr<Fahrzeug> F)
{
    F->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(move(F));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> F, double Start)
{
    F->vNeueStrecke(*this, Start);
    p_pFahrzeuge.push_front(move(F));
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& F)
{
    unique_ptr<Fahrzeug> TempFahrzeug;
    list<unique_ptr<Fahrzeug>>::iterator iterator = p_pFahrzeuge.begin();
    for (auto& i : p_pFahrzeuge) {
        if (*i == F) {
            TempFahrzeug = move(i);
            p_pFahrzeuge.erase(iterator);
            return TempFahrzeug;
        }
        iterator++;
    }
}
