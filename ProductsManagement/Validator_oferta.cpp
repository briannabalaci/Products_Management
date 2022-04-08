#include "Validator_oferta.h"

void valideaza_oferta(const Oferta_turistica& of) {
	if (of.get_denumire() == "")
		throw Valid_Exception("denumire invalida!\n");
	if (of.get_destinatie() == "")
		throw Valid_Exception("destinatie invalida!\n");
	if (of.get_tip() == "")
		throw Valid_Exception("tip invalid!\n");
	if (of.get_pret() < 0)
		throw Valid_Exception("pret invalid!\n");
}
