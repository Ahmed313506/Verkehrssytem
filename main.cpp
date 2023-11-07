//============================================================================
// Name        : New.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Fahrzeug.h"
#include"PKW.h"
#include"Fahrrad.h"
#include<memory>
#include<vector>
#include<iomanip>
using namespace std;
double dGlobaleZeit;
double dEpsilon = 0.001;

void vAufgabe_Probe() {
    Fahrzeug* pF1 = new PKW("Audi", 150, 8);  //8 = fuelConsumptionRate  , 150 = geschwindigkeit
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 3.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
   cout << *pF1 << endl;
    delete pF1;
    char c;
    cin >> c;
    //stepFuelConsumption = (vehicleSpeed * timeInterval / 100) * fuelConsumptionRate;
}

void vAufgabe_1() { //4.2.4


	cout << "Aufgabenblock 1, Aufgabe 1: " << endl;
	Fahrzeug f1("Audi");
	Fahrzeug f2("Wolkswagen");
	Fahrzeug *f3 = new Fahrzeug("Porsche911");
	Fahrzeug *f4 = new Fahrzeug();
	unique_ptr<Fahrzeug> f5(new Fahrzeug("Bugatti Veyron"));
	unique_ptr<Fahrzeug> f6(new Fahrzeug("RX8"));
	shared_ptr<Fahrzeug> f7 = make_shared<Fahrzeug>("BoxterSpyder");
	shared_ptr<Fahrzeug> f8 = make_shared<Fahrzeug>("Lambo");
	shared_ptr<Fahrzeug> f9 = f7;
	cout << "f7.use_count() = " << f7.use_count() << endl; // 2

	vector<unique_ptr<Fahrzeug> > v1; // debugger Teil
	v1.push_back(move(f5));
	v1.push_back(move(f6));
	v1.clear(); //delete f5,f6

	vector<shared_ptr<Fahrzeug> > v2;
	v2.push_back(f7); // it isn't deleted because it shares the ownership not only with the vector but also with object Fahrzeug itself
	v2.push_back(move(f8));
	v2.clear(); //delete f8

	delete f3; // manually deleted pointers to avoid the memory leaks
	delete f4;


}

void vAufgabe_1a() { //Aufgabe 4.2.9
	cout << "Aufgabenblock 1, Aufgabe 1a: " << endl;
	vector<shared_ptr<Fahrzeug> > Fahrzeuglist;
	string name;
	double maxGeschwindigkeit;
	for (int i = 0; i < 3; i++) {
		cout << "Geben Sie einen Fahrzeugsname und die Maximalgeschwindigkeit:";
		cin >> name >> maxGeschwindigkeit;
		shared_ptr<Fahrzeug> fz = make_shared<Fahrzeug>(name, maxGeschwindigkeit);
		Fahrzeuglist.push_back(move(fz));
	}
	double dZeitschritt = 1;
	for (int i = 0; i < 3; i++) {
		dGlobaleZeit += dZeitschritt;
		cout << "GlobaleZeit=" << dGlobaleZeit << endl;
		Fahrzeug::vKopf();
		for (int k = 0; k < 3; k++) {
			Fahrzeuglist[k]->vSimulieren();
			Fahrzeuglist[k]->vAusgeben();
			cout << endl;
		}
		cout << endl;
	}
}

void vAufgabe_2() { //4.3.4
	cout << "Aufgabenblock 1, Aufgabe 2: " << endl;
	vector<shared_ptr<Fahrzeug> > Fahrzeuglist;
	string name;
		shared_ptr<Fahrzeug> fz = make_shared<PKW>("EvolutionX", 600, 13, 300);
	Fahrzeuglist.push_back(move(fz));
	fz = make_shared<PKW>("MazdaRX8", 500, 20);
	Fahrzeuglist.push_back(move(fz));
	fz = make_shared<Fahrrad>("Biker1", 100);
	Fahrzeuglist.push_back(move(fz));
	fz = make_shared<Fahrrad>("Biker2", 200);
	Fahrzeuglist.push_back(move(fz));


	int listSize = Fahrzeuglist.size();

	double dGesamtzeit = 6.0;
	double dTankzeit = 3.0;
	for (dGlobaleZeit = 0; dGlobaleZeit <= dGesamtzeit; dGlobaleZeit += 1) {
		cout << "dGlobaleZeit=" << dGlobaleZeit << endl;
		Fahrzeug::vKopf();
		for (int i = 0; i < listSize; i++) {

			Fahrzeuglist[i]->vSimulieren();
			Fahrzeuglist[i]->vAusgeben();
			cout << endl;
			if (dGlobaleZeit == dTankzeit
					&& Fahrzeuglist[i]->check_type() == 1) {
				Fahrzeuglist[i]->dTanken(-1);
			}
		}
		cout << endl;
	}



}

void vAufgabe_3() { //4.4
	cout << "Aufgabenblock 1, Aufgabe 3: " << endl;

	PKW PKW1("Lambo", 150, 8);
	Fahrrad Fahrrad1("BMX", 20);
	dGlobaleZeit = 3;
	Fahrzeug::vKopf();
	PKW1.vSimulieren();
	Fahrrad1.vSimulieren();
	cout << PKW1 << endl <<
			Fahrrad1 << endl
			<< (PKW1 < Fahrrad1) << endl; // Wir testen hier sowie Ausgabe operator als auch Vergleichsoperator


	// Weder PKW Lamborgini Hurricane = Audi noch Fahrrad BMX1 = BMX2 sind richtig, da es gar kein Copy Konstruktor finden sollte.
	PKW PKW2  ;
	Fahrrad Fahrrad2;

	//Alternativ koennen wir ein Vergleich operator benutzen
	PKW2=PKW1;
	Fahrrad2=Fahrrad1;
	cout << PKW2 << endl << Fahrrad2 << endl;

}



int main() {


	vAufgabe_1();
//	vAufgabe_1a();
//	vAufgabe_2();
//	vAufgabe_3();
//	vAufgabe_Probe();
	return 0;
}
