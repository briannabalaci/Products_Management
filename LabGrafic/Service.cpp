#include "Service.h"
#include "Comparare.h"
#include <map>
#include <exception>

/*
VectDinNewDeleteT<Oferta_turistica> Service::filtre_name(std::string filtre)
{
	VectDinNewDeleteT<Oferta_turistica> lista;
	VectDinNewDeleteT<Oferta_turistica> oferte = repo.get_all();
	for (const auto& prod : oferte)
	{
		if (prod.get_denumire().find(filtre) != std::string::npos)
			lista.add(prod);
	}
	if (lista.size() == 0)
		throw std::exception("Nu exista produse care satisfac criteriul!\n");
	return lista;
}*/



//VectDinNewDeleteT<Oferta_turistica> Service::sortare_generala(bool (*comparare) (const Oferta_turistica&, const Oferta_turistica&))
vector<Oferta_turistica> Service::sortare_generala(bool (*comparare) (const Oferta_turistica&, const Oferta_turistica&))
{
	auto oferte = get_all();
	if (comparare != nullptr)
		for (auto it1 = oferte.begin(); it1 != oferte.end(); ++it1)
			for (auto it2 = it1; it2 != oferte.end(); ++it2)
			{
				if (comparare(*it1, *it2))
				{
					auto aux = *it1;
					*it1 = *it2;
					*it2 = aux;
				}
			}
	return oferte;
}

vector<Oferta_turistica> Service::sortare_denumire()
//VectDinNewDeleteT<Oferta_turistica> Service::sortare_denumire()
{
	return sortare_generala(comparare_denumire);
}

//VectDinNewDeleteT<Oferta_turistica> Service::sortare_destinatie()
vector<Oferta_turistica> Service::sortare_destinatie()
{
	return sortare_generala(comparare_destinatie);
}

vector<Oferta_turistica> Service::sortare_prof_tip()
//VectDinNewDeleteT<Oferta_turistica> Service::sortare_prof_tip()
{
	return sortare_generala(comparare_pret_tip);
}

void test_service() {
	Repo repo;
	Service serv { repo };
	serv.add("a", "b", "c", 5);
	//const auto& oferte = serv.get_all();
	assert(serv.sizer() == 1);
	//assert(size(oferte) == 1);
	try {
		serv.add("a", "b", "c", 5);}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element existent!\n");}
	try {
		serv.add("", "b", "c", 5);}
	catch (Valid_Exception& e) {
		assert(e.getMessage() == "denumire invalida!\n");}
	try {
		serv.add("a", "", "c", 5);}
	catch (Valid_Exception& e) {
		assert(e.getMessage() == "destinatie invalida!\n");}
	try {
		serv.add("a", "b", "", 5);}
	catch (Valid_Exception& e) {
		assert(e.getMessage() == "tip invalid!\n");}
	try {
		serv.add("a", "b", "c", -80);}
	catch (Valid_Exception& e) {
		assert(e.getMessage() == "pret invalid!\n");}

	serv.modify("a", "b", "d", 7);
	const auto& oferte = serv.get_all();

	//assert(oferte.get(0).get_pret() == 7);
	assert(oferte.at(0).get_pret() == 7);
	try {
		serv.modify("f", "h", "r", 7);}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");}

	serv.add("X", "Y", "Z", 15);
	assert(serv.sizer() == 2);
	serv.remove("X");
	//oferte = serv.get_all();
	assert(serv.sizer() == 1);
	try {
		serv.remove("f");}
	catch (Repo_Exception& e) {
		assert(e.getMessage() == "element inexistent!\n");
	}/**/

	/*
		assert(serv.search("a").get_pret() == 7);
		try {
			serv.search("x");}
		catch (Repo_Exception& e) {
			assert(e.getMessage() == "element inexistent!\n");
		}/**/

		/*
			serv.add("ab", "x", "c", 100);
			serv.add("abc", "y", "c", 120);
			*/
			/*
			VectDinNewDeleteT<Oferta_turistica> v;
			v = serv.filtreazaDestinatie ("x");
			auto filtrat=serv.filtreazaPret(99, 130);
			assert(filtrat.get(0).get_destinatie() == "x");

			Oferta_turistica ofertuta1("a", "x", "c", 34);
			Oferta_turistica ofertuta2("r", "b", "c", 33);
			Oferta_turistica ofertuta3("r", "b", "b", 33);
			assert(comparare_denumire(ofertuta2, ofertuta1));
			assert(comparare_destinatie(ofertuta1, ofertuta2));
			assert(comparare_pret_tip(ofertuta1, ofertuta2));
			assert(comparare_pret_tip(ofertuta2, ofertuta3));

			assert(comparare_denumire(ofertuta1, ofertuta2)==false);
			assert(comparare_destinatie(ofertuta2, ofertuta1) == false);
			assert(comparare_pret_tip(ofertuta2, ofertuta1) == false);
			assert(comparare_pret_tip(ofertuta3, ofertuta2) == false);

			serv.add("ab", "g", "gf", 10);
			serv.add("gf", "yf", "f", 160);
			serv.add("gc", "o", "v", 160);
			serv.add("ahgc", "x", "v", 45);
			serv.add("yfc", "t", "j", 190);

			//const auto& papa = serv.get_all();
			*/
	
				serv.add("A1", "B1", "C1", 6.5);
				serv.add("A2", "B2", "C2", 6.5);
				serv.add("A3", "B3", "C3", 6.5);
				serv.add_in_wishlist("A1");
				const auto& cos = serv.get_all_wishlist();
				assert(cos.size() == 1);
				try {
					serv.add_in_wishlist("A1");}
				catch (Repo_Exception& e) {
					assert(e.getMessage() == "element existent!\n");
				}
				try {
					serv.add_in_wishlist("A4");}
				catch (Repo_Exception& e) {
					assert(e.getMessage() == "element inexistent!\n");
				}
				serv.generate_wishlist(3);
				const auto& cos1 = serv.get_all_wishlist();
				assert(cos1.size() == 3);

				try {
					serv.generate_wishlist(100);}
				catch (Repo_Exception& e) {
					assert(e.getMessage() == "oferte insuficiente!\n");
				}
				serv.empty_wishlist();

				const auto& filtru1=serv.filtreaza("destinatie", "B1", 0, 0);
				assert(filtru1.at(0).get_destinatie() == "B1");
				const auto& filtru2=serv.filtreaza("pret", "adad", 6, 100);
				assert(filtru2.at(0).get_pret() == 7);

				try {
					serv.filtreaza("aaa", "adad", 6, 100);}
				catch (Repo_Exception& e) {
					assert(e.getMessage() == "criteriu inexistent!\n");
				}
					const auto& sort1 = serv.generalSortSTL("denumire");
					//cout << sort1.at(0).get_destinatie();
					assert(sort1.at(0).get_destinatie() == "B1");
					const auto & sort2 = serv.generalSortSTL("destinatie");
					assert(sort2.at(0).get_destinatie() == "B1");
					const auto & sort3 = serv.generalSortSTL("tip+pret");
					//cout << sort3.at(0).get_pret();
					assert(sort3.at(0).get_pret() == 6.5);

					try {
						serv.generalSortSTL("aaaa");}
					catch (Repo_Exception& e) {
						assert(e.getMessage() == "criteriu invalid!\n");
					}
					serv.add("Ha", "Tenerife", "c", 5);
					serv.add("Pa", "Tenerife", "d", 7);
					serv.add("Ma", "Zanzibar", "d", 7);
					auto rap = serv.raport();
					map <string, int> ::iterator it;
					it = rap.find("Tenerife");
					assert(it->first == "Tenerife");
					assert(it->second == 2);
					it = rap.find("Zanzibar");
					assert(it->first == "Zanzibar");
					assert(it->second == 1);

					ofstream ofs;

					serv.exportFile("test1");


					try { serv.exportFile("nuexista//fisi"); }
					catch (const Repo_Exception& re) { assert(re.getMessage() =="Export imposibil!\n"); }


			}
			void test_undo() {
				Repo repo;
				Service serv{ repo };
				try {
					serv.undo();}
				catch (const Repo_Exception& re) { assert(re.getMessage() == "Nu mai exista operatii\n"); }
				serv.add("lala", "lili", "cici", 8);
				serv.undo();
				serv.add("L", "Light", "Yagami", 8);
				serv.modify("L", "Misa", "Amane", 9);
				serv.undo();
				serv.remove("L");
				serv.undo();
			}

			

