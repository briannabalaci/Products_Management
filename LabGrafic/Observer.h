#pragma once
#include <vector>
using std::vector;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
	vector<Observer*> interesati;
protected:
	void notify() {
		for (auto obs : interesati) {
			obs->update();
		}
	}
public:
	void addObserver(Observer* o) {
		interesati.push_back(o);
	}
	void removeObserver(Observer* o) {
		interesati.erase(std::remove(begin(interesati), end(interesati), o),interesati.end());
	}
};


