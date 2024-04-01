#pragma once
#include <string>
#include <limits>
#include <memory>
#include "Simulationsobjekt.h"


using namespace std;
class Verhalten;
class Weg;

//GlobaleZeit ist im "main.cpp" deklariert
extern double dGlobaleZeit;
const double dZeittakt = 0.2;

class Fahrzeug : public Simulationsobjekt
{
public:
	//Konstruktoren
	Fahrzeug();
	Fahrzeug(string Name);
	Fahrzeug(string Name, double Geschwindigkeit);
	virtual ~Fahrzeug(); //Destruktor
	Fahrzeug(const Fahrzeug&) = delete; //Verboten Copy-Konstruktor

	//Methoden
	static void vKopf();
	virtual void vAusgeben() override;
	virtual void vAusgeben(ostream&) const;
	virtual void vSimulieren() override;
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit() const;
	void vNeueStrecke(Weg& weg);
	void vNeueStrecke(Weg& weg, double);
	virtual void vZeichnen(Weg&)const;

	double getAbschnittStrecke() { return p_dAbschnittStrecke; };
	
	//Operatoren Überladung
	bool operator<(const Fahrzeug& F);
	Fahrzeug& operator=(const Fahrzeug& F);

protected:
	//Klassenmitglieder
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dAbschnittStrecke = 0;
	double p_dGesamtZeit = 0;
	unique_ptr<Verhalten> p_pVerhalten;
};

