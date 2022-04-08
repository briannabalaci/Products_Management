#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "Oferta_turistica.h"
//#include "VectorDinamicTemplate.h"
#include "POSError.h"
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono>
#include <fstream>
#include <sstream>
#include <map>
using std::map;
using std::cout;
using std::string;
using std::vector;
using std::ofstream;
using std::stringstream;
/*
class Repo_Exception {
	string msg;
public:
	Repo_Exception(string m) :msg(m) {

	}
	string getMessage() {
		return msg;
	}
};
*/
class Repo_Exception :public POSError {
public:
	Repo_Exception(string msg) :
		POSError(msg) {}

};
class Repo
{
private:
	//VectDinNewDeleteT<Oferta_turistica> oferte;
	vector<Oferta_turistica> cos;
	vector<Oferta_turistica> oferte;

public:
	Repo(const Repo& ot) = delete;
	Repo() = default;
	/*
	* o - entitate de tip oferta turistica
	* adauga in repo o entitate de tip oferta turistica
	* arunca exceptie daca oferta turistica se afla deja in repo
	*/
	virtual void adauga(const Oferta_turistica& o) {
		for (const auto& of : oferte) {
			if (of.get_denumire() == o.get_denumire()) {
				throw Repo_Exception("element existent!\n");
			}
		}

		//oferte.add(o);
		oferte.push_back(o);
	}
	/*
	* returneaza totalitatea ofertelor turistice din repo
	*/
	//const VectDinNewDeleteT<Oferta_turistica>& get_all() {
	const vector<Oferta_turistica>& get_all() {
		return oferte;
	}
	/*
	* denumire - string
	* destinatie - string
	* sterge oferta turistica cu dinumirea si destinatie egale cu parametrii functiei
	* ridica eroare daca oferta turistica nu exista
	*/
	virtual void sterge(const string& denumire)
	{
		//unsigned int i;
		//for (i = 0; i < (unsigned int)oferte.size(); i++)
		int it = 0;
		for (Oferta_turistica& of : oferte)
		{
			//if (oferte.get(i).get_denumire() == denumire && oferte.get(i).get_destinatie() == destinatie) {
				//oferte.del(i);
				//return;
			//if (oferte.at(i).get_denumire() == denumire && oferte.at(i).get_destinatie() == destinatie) {
				//oferte.erase(oferte.begin() + i);
				//return;

			if (of.get_denumire() == denumire) {
				oferte.erase(oferte.begin() + it);
				return;
			}

			it++;
		}
		throw Repo_Exception("element inexistent!\n");
	}
	/*
	* denumire - string
	* destinatie - string
	* tip - string
	* pret - double
	* modifica oferta turistica cu dinumirea si destinatie egale cu parametrii functiei
	* ridica eroare daca oferta turistica nu exista
	*/
	virtual void modifica(const string& denumire, const string& destinatie, const string& tip, double pret)
	{
		for (Oferta_turistica& of : oferte) {
			if (of.get_denumire() == denumire) {
				of.set_destinatie(destinatie);
				of.set_tip(tip);
				of.set_pret(pret);
				return;
			}

		}
		throw Repo_Exception("element inexistent!\n");
	}
	/*
	* returneaza marimea repo-ului
	*/
	int size_repo() {
		return (int)oferte.size();

	}
	/*
	* denumire - string
	* destinatie - string
	* cauta in repo elementul cu denumire si destinatia data
	* returneaza elementul cautat cu denumirea si destinaria data
	* arunca exceptie daca nu exista elementul cautat
	*/
	const Oferta_turistica& cauta(const string& denumire) {
		//for (unsigned int i = 0; i < oferte.size(); i++) {
			//if (oferte.get(i).get_denumire() == denumire && oferte.get(i).get_destinatie() == destinatie)
				//return oferte.get(i);
			//if (oferte.at(i).get_denumire() == denumire && oferte.at(i).get_destinatie() == destinatie)
				//return oferte.at(i);

		const auto& rez = find_if(oferte.begin(), oferte.end(), [denumire](const Oferta_turistica& of) {
			return of.get_denumire() == denumire; });
		if (rez != oferte.end())
			return *rez;
		throw Repo_Exception("element inexistent!\n");}

	/*
	* denumire - string
	* adauga in cos o entitate de tip oferta turistica
	* arunca exceptie daca oferta turistica se afla deja in cos
	* arunca exceptie daca oferta turistica nu se afla in repo
	*/
	void adauga_in_cos(const string& denumire) {
		for (const auto& of : cos) {
			if (of.get_denumire() == denumire) {
				throw Repo_Exception("element existent!\n");
			}
		}

		for (const auto& of : oferte)
			if (of.get_denumire() == denumire) {
				cos.push_back(of);
				return;
			}

		throw Repo_Exception("element inexistent!\n");
	}
	/*
	* goleste cos
	*/
	void golire_cos() {
		cos.clear();
	}

	/*
	nr - numar natural
	arunca exceptie daca numarul este mai mare decat numarul de elemente din repo
	genereaza random nr elemente in cos
	*/
	void genereaza_cos(int nr) {
		if (nr > int(size(oferte)))
			throw Repo_Exception("oferte insuficiente!\n");
		vector<Oferta_turistica> generat;
		vector<Oferta_turistica> aux = oferte;
		/*
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();




			std::shuffle(aux.begin(), aux.end(), std::default_random_engine(seed)); //amesteca vectorul v
			generat.push_back(aux.at(0));
			aux.erase(oferte.begin() );
		}*/
		for (int i = 0; i < nr; i++) {
			/*
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, aux.size() - 1);
			int rndNr = dist(mt);// numar aleator intre [0,size-1]
			*/
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> const dist(1, 6);
			const int position = dist(rng) % size(aux);

			generat.push_back(aux.at(position));
			aux.erase(aux.begin() + position);
		}
		cos.clear();
		cos = generat;
		/*
		for (auto el : cos)
			cout << el;
			*/
	}
	/*
	* returneaza totalitatea ofertelor turistice din cos
	*/
	const vector<Oferta_turistica>& get_all_cos() {
		return cos;
	}

	void exportCSV(string fName) {
		fName += ".csv";
		ofstream out(fName);
		if (!out.is_open())
			throw Repo_Exception("Export imposibil!\n");
		for (const auto& it : cos) {
			out << "Denumire :" << it.get_denumire() << "\n";
			out << "Destinatie :" << it.get_destinatie() << "\n";
			out << "Tip :" << it.get_tip() << "\n";
			out << "Pret :" << it.get_pret() << "\n";
			out << "\n";
		}
		out.close();
	}
};
void test_repo();
class RepoFile : public Repo {
private:
	string fName;
	void loadFromFile()
	{
		std::ifstream in(fName);
		string line;

		if (!in.is_open())
			throw Repo_Exception("Error opening file");

		while (std::getline(in, line))
		{
			string denumire, destinatie, tip;
			float pret;
			string parsed;
			stringstream iss(line);

			std::getline(iss, denumire, ',');
			std::getline(iss, destinatie, ',');
			std::getline(iss, tip, ',');
			//std::getline(iss, pret, ',');

			std::getline(iss, parsed, '\n');
			pret = std::stof(parsed);

			Oferta_turistica of{ denumire, destinatie, tip, pret };
			Repo::adauga(of);

			if (in.eof()) break;
		}
		in.close();
		
		/*
		std::ifstream in(fName);

		if (!in.is_open()) {
			throw Repo_Exception("Error opening file");
		}

		while (!in.eof()) {
			string denumire;
			in >> denumire;
			if (in.eof()) break;
			string destinatie;
			in >> destinatie;
			string tip;
			in >> tip;
			float pret;
			in >> pret;

			Oferta_turistica of{ denumire.c_str(),destinatie.c_str(),tip.c_str(),pret };
			Repo::adauga(of);
		}
		in.close();
		*/
	}

	void writeToFile()
	{
		std::ofstream out(fName);

		for (auto& p : Repo::get_all())
		{
			out << p.get_denumire() <<","<< p.get_destinatie() << "," << p.get_tip() << "," << p.get_pret();
	
			out << std::endl;



		}
		out.close();
	}

public:
	RepoFile(string fName) : Repo(), fName{ fName }{
		loadFromFile();
	}

	void adauga(const Oferta_turistica& o) override {
		Repo::adauga(o);
		writeToFile();
	}
	void sterge(const string& denumire) override {
		Repo::sterge(denumire);
		writeToFile();
	}
	void modifica(const string& denumire, const string& destinatie, const string& tip, double pret) override {
		Repo::modifica(denumire, destinatie, tip, pret);
		writeToFile();
	}
};



void test_repo_file();

class RepositoryPure
{
public:
	RepositoryPure() = default;
	virtual void adauga(const Oferta_turistica& o) = 0;
	virtual void sterge(const string& denumire) = 0;
	virtual void modifica(const string& denumire, const string& destinatie, const string& tip, double pret) = 0;
	virtual int size_repo() = 0;
	virtual const Oferta_turistica& cauta(const string& denumire) = 0;
	virtual const vector<Oferta_turistica>& get_all() = 0;
	virtual ~RepositoryPure() = default;
	virtual void adauga_in_cos(const string& denumire) = 0;
	virtual void golire_cos() = 0;
	virtual const vector<Oferta_turistica>& get_all_cos() = 0;
	virtual void exportCSV(string fName) = 0;
	virtual void genereaza_cos(int nr) = 0;
};

class RepositoryMap : public RepositoryPure
{
private:
	float probability;
	map<string, Oferta_turistica> m;
	vector<Oferta_turistica>oferte;
	vector<Oferta_turistica>cos;

public:
	RepositoryMap() = default;
	void jocurile_de_noroc()
	{
		std::mt19937 mt{ std::random_device{}() };
		const std::uniform_int_distribution<> dist(0, 100);
		const int rndNr = dist(mt);
		const float rndflt = static_cast<float>(rndNr) / 100;
		if (rndflt < this->probability)
			throw Repo_Exception("Improbabil sa se intample\n");
	}
	RepositoryMap(float prob) : probability{ prob } {}
	//Repo_dict r{ (float)0.5 };
	virtual void adauga(const Oferta_turistica& o) override {
		jocurile_de_noroc();
		string denumire = o.get_denumire();
		auto it = m.find(denumire);
		if (it != m.end())
			throw Repo_Exception("element existent!\n");
		m.insert(make_pair(denumire, o));
	}
	virtual void sterge(const string& denumire) override {
		jocurile_de_noroc();
		auto it = m.find(denumire);
		if (it == m.end())
			throw Repo_Exception("element inexistent!\n");
		m.erase(denumire);
	}
	virtual void modifica(const string& denumire, const string& destinatie, const string& tip, double pret) override
	{
		//string denumire = disci.get_denumire();
		jocurile_de_noroc();
		auto it = m.find(denumire);
		if (it == m.end())
			throw Repo_Exception("element inexistent!\n");
		it->second.set_destinatie(destinatie);
		it->second.set_tip(tip);
		it->second.set_pret(pret);
	}
	virtual int size_repo()override
	{
		return (int)m.size();
	}
	virtual const Oferta_turistica& cauta(const string& denumire) override {
		jocurile_de_noroc();
		auto it = m.find(denumire);
		if (it == m.end())
			throw Repo_Exception("element inexistent!\n");
		return it->second;
	}
	virtual const vector<Oferta_turistica>& get_all() override {
		oferte.clear();
		for (auto it = m.begin(); it != m.end(); ++it)
			oferte.push_back(it->second);
		return oferte;
	}
	virtual ~RepositoryMap() = default;
	virtual void adauga_in_cos(const string& denumire) override
	{
		for (const auto& of : cos) {
			if (of.get_denumire() == denumire) {
				throw Repo_Exception("element existent!\n");
			}
		}

		for (const auto& of : oferte)
			if (of.get_denumire() == denumire) {
				cos.push_back(of);
				return;
			}

		throw Repo_Exception("element inexistent!\n");
	}
	virtual void golire_cos() override
	{
		cos.clear();
	}
	virtual const vector<Oferta_turistica>& get_all_cos() override
	{
		return cos;
	}
	virtual void exportCSV(string fName) override {
		{
			fName += ".csv";
			ofstream out(fName);
			if (!out.is_open())
				throw Repo_Exception("Export imposibil!\n");
			for (const auto& it : cos) {
				/*
				out << "Denumire :" << it.get_denumire() << "\n";
				out << "Destinatie :" << it.get_destinatie() << "\n";
				out << "Tip :" << it.get_tip() << "\n";
				out << "Pret :" << it.get_pret() << "\n";
				out << "\n";
				*/
				out << it.get_denumire() << "," << it.get_destinatie() << "," << it.get_tip() << "," << it.get_pret() << "\n";
			}
			out.close();
		}
	}
	virtual void genereaza_cos(int nr)  override {
		if (nr > int(size(get_all())))
			throw Repo_Exception("oferte insuficiente!\n");
		vector<Oferta_turistica> generat;
		vector<Oferta_turistica> aux = oferte;
		/*
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();




			std::shuffle(aux.begin(), aux.end(), std::default_random_engine(seed)); //amesteca vectorul v
			generat.push_back(aux.at(0));
			aux.erase(oferte.begin() );
		}*/
		for (int i = 0; i < nr; i++) {
			/*
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> dist(0, aux.size() - 1);
			int rndNr = dist(mt);// numar aleator intre [0,size-1]
			*/
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> const dist(1, 6);
			const int position = dist(rng) % size(aux);

			generat.push_back(aux.at(position));
			aux.erase(aux.begin() + position);
		}
		cos.clear();
		cos = generat;
	}
};
