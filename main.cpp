#pragma warning( disable : 4290 )
#include <iostream>
#include "Simulationsobjekt.h"
#include "Fahrrad.h"
#include "Fahrzeug.h"
#include <random>
#include "PKW.h"
#include "Weg.h"
#include "SimuClient.h"
#include "Fahrausnahme.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"
#include <vector>

using namespace std;

//Deklaration von globale Zeit
double dGlobaleZeit = 0.0;

void vAufgabe_1() {
	//Erzeugung von statische elemente
	Fahrzeug test1Sta;
	//Erzeugung von dynamsche elemente
	Fahrzeug* test1Dyn = new Fahrzeug();
	delete test1Dyn;


	auto car1 = make_unique<Fahrzeug>();
	auto car2 = make_unique<Fahrzeug>();
	auto car3 = make_shared<Fahrzeug>();
	cout << car3.use_count() << endl; // 1
	auto car4 = car3;
	cout << car3.use_count() << endl; // 2
	// use_count ist nicht für unique_ptr definiert

	vector<unique_ptr<Fahrzeug>> v1;
	v1.push_back(move(car1));
	v1.push_back(move(car2));
	//v1.push_back(car3); ist ein Fehler
	//v1.push_back(car4); ist ein Fehler
	cout << car1 << endl << car2 << endl;
	// car1 und car2 sind jetzt nullptr
	v1.clear();

	vector<shared_ptr<Fahrzeug>> v2;
	//v2.push_back(car1); ist ein Fehler
	//v2.push_back(car2); ist ein Fehler
	v2.push_back(car3);
	v2.push_back(move(car4));
	cout << car3.use_count() << endl; // 3 (nicht 4 weil move())
}

void vAufgabe_1a() {

	vector<unique_ptr<Fahrzeug>> v1;

	//Erzeugung von 3 Fahrzeuge
	v1.push_back(make_unique<Fahrzeug>("VW", 30));
	v1.push_back(make_unique<Fahrzeug>("BMW", 40));
	v1.push_back(make_unique<Fahrzeug>("Audi", 20));

	//Simulieren für 2 Stunden
	while (dGlobaleZeit < 2) {


		dGlobaleZeit += dZeittakt;
		Fahrzeug::vKopf();
		cout << endl;

		//Iteration über die 3 Fahrzeuge
		for (auto& i : v1) {
			i->vSimulieren();
			i->vAusgeben();
			cout << endl;
		}
	}
}

void vAufgabe_2() {
	double ZietMonitor = 3.0; //3 stunden
	vector<unique_ptr<Fahrzeug>> v1;

	// 2 PKW und ein Fahrrad
	v1.push_back(make_unique<Fahrrad>("Youssef", 30));
	v1.push_back(make_unique<PKW>("BMW", 70, 9));
	v1.push_back(make_unique<PKW>("Audi", 80, 8));
	//*Fahrzeug typ kann auf einem PKW oder Fahrrad zeigen weil es Pointer ist

	//Simulieren für 2 Stunden
	while (dGlobaleZeit < 5) {


		dGlobaleZeit += dZeittakt;
		ZietMonitor -= dZeittakt;//jeder schritt substraktieren wir die Zeittakt von den 3 Stunden
		bool flag = true;

		Fahrzeug::vKopf();
		cout << endl;

		//Iteration über die 3 Fahrzeuge
		for (auto& i : v1) {
			i->vSimulieren();
			if (ZietMonitor <= 0 && flag) { //Wenn es negativ oder gleich null ist, dann sind die 3 Stunden überschritten
				i->dTanken();
				flag = false;
			}
			i->vAusgeben();
			cout << endl;
		}


	}
}

void vAufgabe_3() {
	PKW P1("BMW", 150, 8);
	Fahrrad F1("Youssef", 20);
	dGlobaleZeit = 1;
	Fahrzeug::vKopf();
	P1.vSimulieren();
	F1.vSimulieren();

	//testen die "<<" und "<" Operatoren
	cout << P1 << endl << F1 << endl << (F1 < P1) << endl; 

	//Fahrrad F2 = F1; bzw. PKW P2 = P1; sind Fehler
	Fahrrad F2;
	PKW P2;

	// testen der Zuweisungsoperator
	F2 = F1;
	P2 = P1;

	cout << P2 << endl << F2 << endl;
}

void vAufgabe_4() {
	Weg weg("weg", 100);
	Weg::vKopf();
	cout << weg << endl;
}

void vAufgabe_5() {
	Weg weg("weg", 100);
	auto p1 = make_unique<PKW>("BMW", 180, 5);
	auto p2 = make_unique<PKW>("Audi", 100, 10);
	auto f1 = make_unique<Fahrrad>("BMX", 20);

	weg.vAnnahme(move(p1));
	weg.vAnnahme(move(p2), 0.5);
	weg.vAnnahme(move(f1));

	Weg::vKopf();
	weg.vSimulieren();
	cout << weg << endl;

	dGlobaleZeit = 1;

	weg.vSimulieren();
}

void vAufgabe_6() {
	bInitialisiereGrafik(800, 500);
	vSetzeZeit(dGlobaleZeit);
	Weg weg1("Hin", 500);
	Weg weg2("Her", 500, Tempolimit::Landstrasse);
	int koordinaten[4] = { 700 , 250 , 100 , 250 };
	bZeichneStrasse("Hin", "Her", 400, 2, new int[4]{ 100, 200, 400, 400});
	auto p1 = make_unique<PKW>("BMW", 200, 1);
	auto p2 = make_unique<PKW>("Audi", 100, 1);
	auto p3 = make_unique<PKW>("VW", 120, 10);
	auto f1 = make_unique<Fahrrad>("BMX", 20);

	weg1.vAnnahme(move(p1));
	weg1.vAnnahme(move(p2), 5);
	weg2.vAnnahme(move(f1));
	weg2.vAnnahme(move(p3));

	weg1.vSimulieren();
	weg2.vSimulieren();

	Weg::vKopf();
	cout << weg1 << endl << weg2 << endl;

	while (dGlobaleZeit < 10) {

		dGlobaleZeit += 0.3;
		vSetzeZeit(dGlobaleZeit);
		weg1.vSimulieren();
		weg2.vSimulieren();
		vSleep(100);
	}

	vBeendeGrafik();
	
}

void vAufgabe_6a() {
	vertagt::VListe<int> Vliste;

	static mt19937 device(0);
	uniform_int_distribution <int> dist(1, 10);

	//Liste erzeugen
	for (int i = 0; i < 10; i++) {
		Vliste.push_back(dist(device));
	}

	Vliste.vAktualisieren();
	
	//Liste ausgeben
	for (auto const& v : Vliste) {
		cout << v << " ";
	}
	cout << endl;

	list<int>::iterator it = Vliste.begin();

	//Elemente > 5 löschen
	for (auto& const v : Vliste) {
		
		if (v > 5) {
			Vliste.erase(it);
		}
		it++;
	}

	//Liste ausgeben
	for (auto const& v : Vliste) {
		cout << v << " ";
	}
	cout << endl;

	Vliste.vAktualisieren();

	//Liste ausgeben
	for (auto const& v : Vliste) {
		cout << v << " ";
	}
	cout << endl;

	Vliste.push_back(dist(device));
	Vliste.push_front(dist(device));

	Vliste.vAktualisieren();

	//Liste ausgeben
	for (auto const& v : Vliste) {
		cout << v << " ";
	}
	cout << endl;
}

void vAufgabe_7() {
	auto kr1 = make_shared<Kreuzung>("Kr1", 0);
	auto kr2 = make_shared<Kreuzung>("Kr2", 10001);
	auto kr3 = make_shared<Kreuzung>("Kr3", 0);
	auto kr4 = make_shared<Kreuzung>("Kr4", 0);

	Kreuzung::vVerbinde("W12", "W21", 40, kr1, kr2, Tempolimit::Innerorts);
	Kreuzung::vVerbinde("W23a", "W32a", 115, kr2, kr3, Tempolimit::Autobahn);
	Kreuzung::vVerbinde("W23b", "W32b", 40, kr2, kr3, Tempolimit::Innerorts);
	Kreuzung::vVerbinde("W24", "W42", 55, kr2, kr4, Tempolimit::Innerorts);
	Kreuzung::vVerbinde("W34", "W43", 85, kr3, kr4, Tempolimit::Autobahn);
	Kreuzung::vVerbinde("W44a", "W44b", 130, kr4, kr4, Tempolimit::Landstrasse);

	bInitialisiereGrafik(1000, 600);
	vSetzeZeit(dGlobaleZeit);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	bZeichneStrasse("W12", "W21", 40, 2, new int[4]{ 680, 40, 680, 300 });
	bZeichneStrasse("W23a", "W32a", 115, 6, new int[12]{ 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 });
	bZeichneStrasse("W23b", "W32b", 40, 2, new int[4]{ 680, 300, 680, 570 });
	bZeichneStrasse("W24", "W42", 55, 2, new int[4]{ 680, 300, 320, 300 });
	bZeichneStrasse("W34", "W43", 85, 5, new int[10]{ 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 });
	bZeichneStrasse("W44a", "W44b", 130, 7, new int[14]{ 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 });

	auto p1 = make_unique<PKW>("BMW", 120, 9);
	auto p2 = make_unique<PKW>("Audi", 100, 8.8);
	auto p3 = make_unique<PKW>("VW", 110, 10);
	auto f1 = make_unique<Fahrrad>("BMX", 20);

	kr1->vAnnahme(move(p1));
	kr1->vAnnahme(move(p2), 3.0);
	kr1->vAnnahme(move(p3));
	kr1->vAnnahme(move(f1));

	while (dGlobaleZeit < 100) {

		vSetzeZeit(dGlobaleZeit);
		kr1->vSimulieren();
		kr2->vSimulieren();
		kr3->vSimulieren();
		kr4->vSimulieren();
		vSleep(100);
		dGlobaleZeit += 0.1;
	}

	vBeendeGrafik();
}


int main() {
	vAufgabe_7();
}