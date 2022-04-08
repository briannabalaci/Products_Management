#pragma once
#include <string>
#include <iostream>
using std::string;
class Oferta_turistica
{
private:
	string denumire;
	string destinatie;
	string tip;
	double pret;

public:
	double get_pret() const;

	string get_destinatie() const;

	string get_denumire() const;

	string get_tip() const;
	Oferta_turistica() : denumire{ "dfg" }, destinatie{ "dfg" }, tip{ "dfg" }, pret{ 30 }{
	}
	Oferta_turistica(string denumire, string destinatie, string tip, double pret) : denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret }{
	}

	/*
	Oferta_turistica(const Oferta_turistica& ot) : denumire{ ot.denumire }, tip{ ot.tip }, destinatie{ ot.destinatie }, pret{ ot.pret }{
		std::cout << "Face copie\n ";
		std::cout << ot;
		//std::cout << "A";
	}*/
	/*
	friend std::ostream& operator<<(std::ostream& os, const Oferta_turistica& of) {
		os << "Denumire :" << of.denumire << "\n";
		os << "Destinatie :" << of.destinatie << "\n";
		os << "Tip :" << of.tip << "\n";
		os << "Pret :" << of.pret << "\n";
		os << "\n";
		return os;
	}*/
	void set_tip(string tipul) {
		this->tip = tipul;
	}
	void set_pret(double pretul) {
		this->pret = pretul;
	}
	void set_destinatie(string destinatia) {
		this->destinatie = destinatia;
	}
	~Oferta_turistica() = default;

	Oferta_turistica& operator=(const Oferta_turistica& a) {
		this->denumire = a.denumire;
		this->destinatie = a.destinatie;
		this->tip = a.tip;
		this->pret = a.pret;
		return *this;
	}

};

