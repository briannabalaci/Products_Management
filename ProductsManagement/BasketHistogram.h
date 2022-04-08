#pragma once
#include "QtWidgets/qwidget.h"
#include "Observer.h"
#include "Service.h"
#include <time.h>
#include "qpainter.h"
class BasketHistogram: public QWidget,Observer
{
public:
	Service& serv;
	BasketHistogram(Service& s);
private:
	void paintEvent(QPaintEvent* ev) override {
		srand(time(NULL));
		QPainter p{ this };
		QImage img;
		img.load("D:/Cinna/cat.jpg");
		img = img.scaled(50, 50, Qt::KeepAspectRatio);
		int x = 1,y = 10;
		for (const auto& u : serv.get_all_wishlist())
		{
			x = rand() % 900;
			y = rand() % 460;
			QPoint pct{ x,y };
			p.drawImage(pct, img);
		}
	}

	void update() override;
};

