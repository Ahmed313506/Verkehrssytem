#include "Fahrzeug.h"
#include "Fahren.h"
#include "Parken.h"
#include "Weg.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;


Fahrzeug::Fahrzeug() 
{
	cout << "Default-Konstruktor von Objekt "<< p_iID << endl;
}


Fahrzeug::Fahrzeug(string Name):
    Simulationsobjekt(Name)
{
	cout << "nichtDefault-Konstruktor von Objekt " << p_iID << endl;
}

Fahrzeug::Fahrzeug(string Name, double Geschwindigkeit):
    Simulationsobjekt(Name),
	p_dMaxGeschwindigkeit(Geschwindigkeit > 0 ? Geschwindigkeit: 0)
{

}

Fahrzeug::~Fahrzeug()
{
	
}

void Fahrzeug::vSimulieren()
{
    //Das Fahrzeug muss nur einmal in einem Zeitschritt bearbeitet wird
    //Deshalb muss die Gloable Zeit nicht gleich die Zeit, zu der das Fahrzeug zuletzt simuliert wurde
    try {
        if (dGlobaleZeit != p_dZeit) {

            double Zeitdiff = dGlobaleZeit - p_dZeit;
            double Strecke = p_pVerhalten->dStrecke(*this, Zeitdiff);

            //Aktualisierung von Information des Fahrzeugs
            p_dGesamtStrecke += Strecke;
            p_dAbschnittStrecke += Strecke;
            p_dGesamtZeit += Zeitdiff;
            p_dZeit = dGlobaleZeit;
        }
    } catch (Fahrausnahme& exception) {
        exception.vBearbeiten();
    }
}

double Fahrzeug::dTanken(double dMenge)
{
    //Wenn nicht PKW, macht nichts und liefert 0.0
    return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
    //Wenn nicht Fahrrad, liefert die maximale Geschwindigkeit
    return p_dMaxGeschwindigkeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg)
{
    p_dAbschnittStrecke = 0;
    p_pVerhalten = make_unique<Fahren>(weg);
}

void Fahrzeug::vNeueStrecke(Weg& weg, double Start)
{
    p_dAbschnittStrecke = 0;
    p_pVerhalten = make_unique<Parken>(weg, Start);
}

void Fahrzeug::vZeichnen(Weg&) const
{
}

bool Fahrzeug::operator<(const Fahrzeug& F)
{
    //Vergleicht die gesamte Strecke
    return p_dGesamtStrecke < F.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& F)
{
    //p_ID kann nicht kopiert werden, weil es eine konstante variable ist
    //nur die Stammdaten kopieren
    p_sName = F.p_sName;
    p_dMaxGeschwindigkeit = F.p_dMaxGeschwindigkeit;
    return *this;
}

void Fahrzeug::vKopf()
{
    //Ausgeben von Überschriften
    cout
        << setiosflags(ios::left)
        << setw(6)
        << "ID"
        << setw(10)
        << "Name"
        << setw(20)
        << "MaxGeschwindigKeit"
        << setw(16)
        << "Gesamtstrecke"
        << setw(17)
        << "Gesamtverbrauch"
        << setw(12)
        << "Tankinhalt"
        << endl
        << string(81, '-')
        << endl;
        

}

void Fahrzeug::vAusgeben()
{
    //Ausgeben von Daten
    Simulationsobjekt::vAusgeben();
    cout
        << setw(16)
        << setprecision(2)
        << setiosflags(ios::fixed)
        << dGeschwindigkeit()
        << setw(17)
        << p_dGesamtStrecke;
}

void Fahrzeug::vAusgeben(ostream& o) const
{
    //wir nutzen diese Methode in die "<<" operator Überladung
    Simulationsobjekt::vAusgeben(o);
    o
        << setw(16)
        << setprecision(2)
        << setiosflags(ios::fixed)
        << dGeschwindigkeit()
        << setw(17)
        << p_dGesamtStrecke;
}
