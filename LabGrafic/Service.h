#pragma once

#include <string>
#include "Comparare.h"
#include "Oferta_turistica.h"
#include "Repo.h"
#include <assert.h>
#include <algorithm>
#include <vector>
#include "Validator_oferta.h"
//#include "VectorDinamicTemplate.h"
#include "undo.h"
#include "Observer.h"
#include<map>
using namespace std;
using std::vector;
using std::sort;
using std::unique_ptr;
using std::make_unique;


class Service: public Observable
{
private:
	Repo& repo;
	vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	Service(Repo& repo) : repo{ repo } {

	}
	Service(const Service& ot) = delete;
	Service() = default;
	/*
	* denumire - string
	* destinatie - string
	* tip - string
	* pret - double
	* creeaza o entitate de tip oferta turistica si o valideaza
	* apeleaza functia adauga() din repo
	*/
	void add(string denumire, string destinatie, string tip, double pret) {
		Oferta_turistica of{ denumire,destinatie,tip,pret };
		valideaza_oferta(of);
		repo.adauga(of);
		undoActions.push_back(make_unique<UndoAdauga>(repo, of));
	}
	/*
	* apeleaza functia get_all() din repo
	*/

	//const VectDinNewDeleteT<Oferta_turistica>& get_all() {
	const vector<Oferta_turistica>& get_all() {
		return repo.get_all();
	}
	/*
	* denumire - string
	* destinatie - string
	* apeleaza functia sterge() din repo
	*/
	void remove(string denumire) {
		const Oferta_turistica rez = repo.cauta(denumire);

		cout << rez.get_denumire() << endl;
		cout << rez.get_destinatie() << endl;
		cout << rez.get_tip() << endl;
		cout << rez.get_pret() << endl;

		repo.sterge(denumire);
		//Oferta_turistica o1 = { rez.get_denumire(),rez.get_destinatie(),rez.get_tip(),rez.get_pret() };
		//Oferta_turistica o1 = { "a","b","c",4};
		undoActions.push_back(make_unique<UndoSterge>(repo, rez));
	}
	/*
	* denumire - string
	* destinatie - string
	* tip - string
	* pret - double
	* apeleaza functia modifica() din repo
	*/
	void modify(string denumire, string destinatie, string tip, double pret) {
		const Oferta_turistica rez = repo.cauta(denumire);
		repo.modifica(denumire, destinatie, tip, pret);
		undoActions.push_back(make_unique<UndoModifica>(repo, rez));
	}
	int sizer() {
		return repo.size_repo();
	}
	//s ar putea sa nu fie buna referinta
	const Oferta_turistica& search(const string& denumire) {
		return repo.cauta(denumire);
	}
	//VectDinNewDeleteT<Oferta_turistica> filtre_name(std::string filtre);
	/*

	VectDinNewDeleteT<Oferta_turistica> filtre_name(std::string filtre)
	{
		VectDinNewDeleteT<Oferta_turistica> lista;
		VectDinNewDeleteT<Oferta_turistica> oferte=get_all();
		for (const auto& prod :oferte)
		{
			if (prod.get_denumire().find(filtre) != std::string::npos)
				lista.add(prod);
		}
		if (lista.size() == 0)
			throw std::exception("Nu exista produse care satisfac criteriul!\n");
		return lista;
	}*/


	/*
	VectDinNewDeleteT<Oferta_turistica> filtreaza(std::function <bool(const Oferta_turistica&)> fct) {
		VectDinNewDeleteT<Oferta_turistica> lista = repo.get_all();
		VectDinNewDeleteT<Oferta_turistica> rez;
		for (auto it = lista.begin(); it != lista.end(); ++it) {
			if (fct(it.element()))
				rez.add(it.element());
		}
		//s ar putea sa tb sa eliberez aici memoria
		return rez;}


	VectDinNewDeleteT<Oferta_turistica> filtreazaPret(float pretMin, float pretMax) {
		return filtreaza([=](const Oferta_turistica& of) {
			return of.get_pret() >= pretMin && of.get_pret() <= pretMax;
			});
	}

	VectDinNewDeleteT<Oferta_turistica> filtreazaDestinatie(const string& destinatie) {
		return filtreaza([=](const Oferta_turistica& of) {
			return of.get_destinatie()==destinatie;
			});
	}
	*/
	/*
	* criteriu - string
	* destinatie - string
	* pretMin - float
	* pretMax - float
	* sorteaza vectorul in functie de criteriu
	* arunca eroare daca nu exista criteriul dat
	*/
	vector <Oferta_turistica> filtreaza(const string& criteriu, const string& destinatie, float pretMin, float pretMax) {
		vector<Oferta_turistica> dest;
		vector<Oferta_turistica> lista = repo.get_all();
		if (criteriu == "destinatie")
			std::copy_if(lista.begin(), lista.end(), std::back_inserter(dest), [=](const Oferta_turistica& of) {
			return of.get_destinatie() == destinatie; });
		else if (criteriu == "pret")
			std::copy_if(lista.begin(), lista.end(), std::back_inserter(dest), [=](const Oferta_turistica& of) {
			return of.get_pret() >= pretMin && of.get_pret() <= pretMax; });
		else
			throw Repo_Exception("criteriu inexistent!\n");
		return dest;
	}

	/*
	* criteriu - string
	* sorteaza vectorul in functie de criteriu
	* arunca eroare daca nu exista criteriul dat
	*/
	vector<Oferta_turistica> generalSortSTL(const string& criteriu) {
		vector<Oferta_turistica> sortata = repo.get_all();
		if (criteriu == "denumire")
			sort(sortata.begin(), sortata.end(), [](const Oferta_turistica& of1, const Oferta_turistica& of2) {
			return of1.get_denumire() < of2.get_denumire();
				});
		else if (criteriu == "destinatie")
			sort(sortata.begin(), sortata.end(), [](const Oferta_turistica& of1, const Oferta_turistica& of2) {
			return of1.get_destinatie() < of2.get_destinatie();
				});
		else if (criteriu == "tip+pret")
			sort(sortata.begin(), sortata.end(), [](const Oferta_turistica& of1, const Oferta_turistica& of2) {
			if (of1.get_tip() != of2.get_tip())
				return of1.get_tip() < of2.get_tip();
			else return of1.get_pret() < of2.get_pret();
				});
		else throw Repo_Exception("criteriu invalid!\n");
		return sortata;

	}


	//VectDinNewDeleteT<Oferta_turistica> sortare_generala(bool (*comparare) (const Oferta_turistica&, const Oferta_turistica&));
	vector<Oferta_turistica> sortare_generala(bool (*comparare) (const Oferta_turistica&, const Oferta_turistica&));


	//VectDinNewDeleteT<Oferta_turistica> sortare_denumire();
	vector<Oferta_turistica> sortare_denumire();


	//VectDinNewDeleteT<Oferta_turistica> sortare_destinatie();
	vector<Oferta_turistica> sortare_destinatie();
	//VectDinNewDeleteT<Oferta_turistica> sortare_prof_tip();
	vector<Oferta_turistica> sortare_prof_tip();
	/*
	vector<Oferta_turistica> sortare_prof_tip_stl() {
		vector<Oferta_turistica> lista = repo.get_all();
		sort(lista.begin(),lista.end(),)
	}
	vector<Oferta_turistica> sortare_destinatie_stl();
	vector<Oferta_turistica> sortare_denumire_stl();
	*/
	/*
	* apeleaza functia adauga_in_cos din repo
	*/
	void add_in_wishlist(const string& denumire) {
		repo.adauga_in_cos(denumire);
		notify();
	}
	/*
	* apeleaza functia golire_cos din repo
	*/
	void empty_wishlist() {
		repo.golire_cos();
		notify();
	}
	/*
	* apeleaza functia genereaza_cos din repo
	*/
	void generate_wishlist(int nr) {
		repo.genereaza_cos(nr);
		notify();
	}
	/*
	* apeleaza functia get_all_cos din repo
	*/
	const vector<Oferta_turistica>& get_all_wishlist() {
		return repo.get_all_cos();
	}

	map<string, int> raport() const {
		vector<Oferta_turistica> elems = repo.get_all();
		map<string, int> rap;
		for (const auto& el : elems) {
			string destinatie = el.get_destinatie();
			map<string, int>::iterator it = rap.find(destinatie);
			if (it == rap.end()) {
				rap.insert(make_pair(destinatie, 1));
			}
			else {
				it->second++;
			}
		}
		return rap;
	}
	void exportFile(string fName) {
		repo.exportCSV(fName);
	}
	void undo() {
		if (undoActions.empty()) {
			throw Repo_Exception("Nu mai exista operatii\n");
		}
		undoActions.back()->doUndo();
		undoActions.pop_back();
	}
};


void test_service();
void test_undo();

