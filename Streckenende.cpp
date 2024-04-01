#include "Streckenende.h"
#include <iostream>
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Weg.h"
#include <iomanip>

Streckenende::Streckenende(Fahrzeug& F, Weg& W):
	Fahrausnahme(F, W)
{
}

void Streckenende::vBearbeiten()
{
	if (weg.getZiel() != nullptr) {
		shared_ptr<Kreuzung> kreuzung = weg.getZiel();
		kreuzung->vTanken(fahrzeug);
		Weg& neuWeg = kreuzung->pZufaelligerWeg(weg);
		neuWeg.vAnnahme(weg.pAbgabe(fahrzeug));
		fahrzeug.vSimulieren();
		fahrzeug.vZeichnen(neuWeg);

		cout
			<< setiosflags(ios::fixed)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setw(10)
			<< "ZEIT"
			<< setw(3)
			<< ":"
			<< dGlobaleZeit
			<< endl
			<< setw(10)
			<< "KREUZUNG"
			<< setw(3)
			<< ":"
			<< setw(10)
			<< kreuzung->getName()
			<< kreuzung->getTankstelle()
			<< endl
			<< setw(10)
			<< "WECHSEL"
			<< setw(3)
			<< ":"
			<< weg.getName()
			<< "-> "
			<< neuWeg.getName()
			<< endl
			<< setw(10)
			<< "FAHRZEUG"
			<< setw(3)
			<< ":"
			<< endl;
		fahrzeug.vKopf();
		cout << fahrzeug << endl << endl << string(81, '*') << endl << endl;
	}
}
