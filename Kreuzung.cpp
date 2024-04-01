#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <random>

Kreuzung::Kreuzung(string Name, double Tank):
	Simulationsobjekt(Name), p_dTankstelle(Tank)
{
}

void Kreuzung::vVerbinde(string Hin, string Her, double Laenge, shared_ptr<Kreuzung> Start, shared_ptr<Kreuzung> Ziel, Tempolimit Limit)
{
	auto hin = make_shared<Weg>(Hin, Laenge, Limit, Ziel);
	Start->p_pWege.push_back(hin);
	auto her = make_shared<Weg>(Her, Laenge, Limit, Start);
	Ziel->p_pWege.push_back(her);

	hin->setRueckweg(her);
	her->setRueckweg(hin);
}

void Kreuzung::vTanken(Fahrzeug& F)
{
	if (p_dTankstelle != 0) {
		double Menge = F.dTanken();
		p_dTankstelle = fabs(Menge - p_dTankstelle) < 0.00001 ? 0 : p_dTankstelle - Menge;
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> F)
{
	p_pWege.front()->vAnnahme(move(F));
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> F, double Zeit)
{
	if (Zeit <= 0) {
		p_pWege.front()->vAnnahme(move(F));
	}
	else {
		p_pWege.front()->vAnnahme(move(F), Zeit);
	}
}

void Kreuzung::vSimulieren()
{
	for (auto& i : p_pWege) {
		i->vSimulieren();
	}
}

Weg& Kreuzung::pZufaelligerWeg(Weg& weg)
{
	if (p_pWege.size() == 1) {
		return *weg.getRueckweg();
	}
	else {
		while (true) {
			static mt19937 device(0);
			uniform_int_distribution <int> dist(0, p_pWege.size()-1);

			auto it = next(p_pWege.begin(), dist(device));

			if (!(**it == *weg.getRueckweg()) && !(**it == weg)) {
				return **it;
			}
		}
	}
}
