#pragma once
#include "Oferta_turistica.h"
#include "Repo.h"
class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Oferta_turistica ofAdaugata;
	Repo& repoOferte;
public:
	UndoAdauga(Repo& repoOferte, Oferta_turistica& ofAdaugata) : repoOferte{ repoOferte }, ofAdaugata{ ofAdaugata }{


	}
	void doUndo() override {
		repoOferte.sterge(ofAdaugata.get_denumire());
	}
};

class UndoSterge : public ActiuneUndo {
	const Oferta_turistica ofStearsa;
	Repo& repoOferte;
public:
	UndoSterge(Repo& repoOferte, const Oferta_turistica& ofS) : repoOferte{ repoOferte }, ofStearsa{ ofS }{

	}
	void doUndo() override {
		repoOferte.adauga(ofStearsa);
	}

};
class UndoModifica : public ActiuneUndo {
	Oferta_turistica ofModificata;
	Repo& repoOferte;
public:
	UndoModifica(Repo& repoOferte, const Oferta_turistica& ofModificata) : repoOferte{ repoOferte }, ofModificata{ ofModificata }{

	}
	void doUndo() override {
		repoOferte.modifica(ofModificata.get_denumire(), ofModificata.get_destinatie(), ofModificata.get_tip(), ofModificata.get_pret());
	}
};

