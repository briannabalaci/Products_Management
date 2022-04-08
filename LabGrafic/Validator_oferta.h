#pragma once
#include <string>
#include <iostream>
#include "Oferta_turistica.h"
#include "POSError.h"
using std::string;
/*
class Valid_Exception {
	string msg;
public:
	Valid_Exception(string m) :msg(m) {

	}
	string getMessage() {
		return msg;
	}
};*/
class Valid_Exception :public POSError {
public:
	Valid_Exception(string msg) :
		POSError(msg) {}

};
/*
* of - element de tip Oferta_turistica
* valideza o oferta
* arunca eroare daca tipul,destinatie sau denumirea este vida si daca pretul este mai mic ca 0
*/
void valideaza_oferta(const Oferta_turistica& of);
