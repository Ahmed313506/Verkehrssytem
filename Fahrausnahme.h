#pragma once
#include <exception>

using namespace std;
class Weg;
class Fahrzeug;


class Fahrausnahme : public exception
{
public:
	Fahrausnahme(Fahrzeug&, Weg&);
	virtual void vBearbeiten() = 0;
protected:
	Fahrzeug& fahrzeug;
	Weg& weg;
};

