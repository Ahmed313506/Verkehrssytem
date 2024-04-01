#include "Losfahren.h"
#include <iostream>
#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug& F, Weg& W):
	Fahrausnahme(F,W)
{
}

void Losfahren::vBearbeiten()
{
	weg.vAnnahme(weg.pAbgabe(fahrzeug));
	fahrzeug.vSimulieren();
}
