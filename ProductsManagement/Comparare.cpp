#include "Comparare.h"

bool comparare_denumire(const Oferta_turistica& of1, const Oferta_turistica& of2)
{
	if (of1.get_denumire() > of2.get_denumire())
		return true;
	else return false;
}

bool comparare_destinatie(const Oferta_turistica& of1, const Oferta_turistica& of2)
{
	if (of1.get_destinatie() > of2.get_destinatie())
		return true;
	else return false;
}

bool comparare_pret_tip(const Oferta_turistica& disci1, const Oferta_turistica& disci2)
{
	if (disci1.get_tip() == disci2.get_tip())
	{
		if (disci1.get_pret() > disci2.get_pret())
			return true;
		else return false;
	}
	else if (disci1.get_tip() > disci2.get_tip())
		return true;
	else return false;
}
