#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <fstream>

void test_repo() {
	Repo r;
	Oferta_turistica of{ "A","B","C",6.5 };
	r.adauga(of);
	const auto& oferte = r.get_all();
	assert(oferte.size() == 1);
	try {
		r.adauga(of);
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element existent!\n");
	}

	r.modifica("A", "B", "D", 7);
	const auto& oferte2 = r.get_all();

	//assert(oferte2.get(0).get_pret() == 7);
	//assert(oferte2.get(0).get_tip() == "D");
	assert(oferte2.at(0).get_pret() == 7);
	assert(oferte2.at(0).get_tip() == "D");
	try {
		r.modifica("f", "h", "r", 7);
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}

	Oferta_turistica of3{ "X","Y","Z",15 };
	r.adauga(of3);

	assert(oferte.size() == 2);

	r.sterge("X");
	assert(oferte.size() == 1);

	try {
		r.sterge("f");
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}/**/
	assert(r.cauta("A").get_pret() == 7);
	try {
		r.cauta("x");
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}/**/
	Oferta_turistica of1{ "A1","B1","C1",6.5 };
	r.adauga(of1);
	Oferta_turistica of2{ "A2","B2","C2",6.5 };
	r.adauga(of2);
	Oferta_turistica of5{ "A3","B3","C3",6.5 };
	r.adauga(of5);
	r.adauga_in_cos("A1");
	const auto& cos = r.get_all_cos();
	assert(cos.size() == 1);
	try {
		r.adauga_in_cos("A1");
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element existent!\n");
	}
	try {
		r.adauga_in_cos("A4");
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}

	try {
		r.genereaza_cos(100);
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "oferte insuficiente!\n");
	}
	r.golire_cos();
	/*
	r.genereaza_cos(3);
	const auto& cos1 = r.get_all_cos();

	std::cout << cos1.size();
	assert(cos1.size() == 3);
	*/

	ofstream ofs;
	//ofs.open("test1.csv", ofstream::out | ofstream::trunc);
	r.exportCSV("test1");
	//std::ifstream in("test1.csv");
	//assert(in.peek() != std::ifstream::traits_type::eof());

	try { r.exportCSV("nuexista//fisi"); }
	catch (const Repo_Exception& re) { assert(re.getMessage() == "Export imposibil!\n"); }


}

void test_repo_file() {
	RepoFile r{ "test1.csv" };
	Oferta_turistica of{ "A","B","C",6.5 };
	r.adauga(of);
	const auto& oferte = r.get_all();
	assert(oferte.size() == 1);
	try {
		r.adauga(of);
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element existent!\n");
	}

	r.modifica("A", "B", "D", 7);
	const auto& oferte2 = r.get_all();

	//assert(oferte2.get(0).get_pret() == 7);
	//assert(oferte2.get(0).get_tip() == "D");
	assert(oferte2.at(0).get_pret() == 7);
	assert(oferte2.at(0).get_tip() == "D");
	try {
		r.modifica("f", "h", "r", 7);
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}

	Oferta_turistica of3{ "X","Y","Z",15 };
	r.adauga(of3);

	assert(oferte.size() == 2);

	r.sterge("X");
	assert(oferte.size() == 1);

	try {
		r.sterge("f");
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}/**/
	try {
		RepoFile r2{ "aaa//testulet.csv" };
	}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "Error opening file");
	}

}
