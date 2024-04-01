#include "Simulationsobjekt.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Deklaration von static Variable von Klasse Simulationsobjekt
int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt():
    p_iID(++p_iMaxID)
{
}

Simulationsobjekt::Simulationsobjekt(string Name):
	p_sName(Name), p_iID(++p_iMaxID)
{
}


Simulationsobjekt::~Simulationsobjekt()
{
	cout << "Destruktor von Objekt " << p_iID << endl;
}

void Simulationsobjekt::vAusgeben()
{
    cout
        << setiosflags(ios::left)
        << "  "
        << setw(3)
        << p_iID
        << setw(23)
        << p_sName;
}

void Simulationsobjekt::vAusgeben(ostream& o) const
{
    o
        << setiosflags(ios::left)
        << "  "
        << setw(4)
        << p_iID
        << setw(23)
        << p_sName;
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& S)
{
    if (this == nullptr) {
        return false;
    }
    return p_iID == S.p_iID;
}

ostream& operator<<(ostream& o, const Simulationsobjekt& S)
{
    S.vAusgeben(o);
    return o;
}
