#include "BasketHistogram.h"
BasketHistogram::BasketHistogram(Service& s) :serv{ s } {
	this->setFixedWidth(1000);
	this->setStyleSheet("background-color:rgb(242, 169, 10)");
	s.addObserver(this);
}

void BasketHistogram::update() {

	repaint();
}