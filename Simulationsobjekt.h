#include <string>
#pragma once
using namespace std;

//abstrakte Oberklasse
class Simulationsobjekt
{
public:
	//konstruktoren
	Simulationsobjekt();
	Simulationsobjekt(string Name);
	virtual ~Simulationsobjekt();
	Simulationsobjekt(const Simulationsobjekt&) = delete; //Copy-Konstruktor verboten

	//Methoden
	virtual void vAusgeben();
	virtual void vAusgeben(ostream&) const;
	virtual void vSimulieren() = 0;

	//setters und getters
	string getName() { return p_sName; };
	void setZeit(double Zeit) { p_dZeit = Zeit; };

	//Operator "==" Überladung
	bool operator==(const Simulationsobjekt& S);
protected:
	//variablen
	string p_sName = "";
	int p_iID;
	double p_dZeit = 0;
	static int p_iMaxID;
};
//Operator "<<" Überladung
ostream& operator<<(ostream&, const Simulationsobjekt&);

