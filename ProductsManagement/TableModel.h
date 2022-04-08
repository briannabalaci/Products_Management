#pragma once
#include <qabstractitemmodel.h>
#include <vector>
#include "Oferta_turistica.h"
class MyTableModel:public QAbstractTableModel {
private:
	std::vector<Oferta_turistica> v;
public slots:
	void resetInternalData()
	{
		v.resize(0);
	}
public:
	MyTableModel(std::vector<Oferta_turistica> vec) : v{ vec } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return v.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Oferta_turistica p = v[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.get_denumire());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.get_tip());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.get_destinatie());
			}
			else if (index.column() == 3) {
				return QString::number(p.get_pret());
			}

		}
		return QVariant{};
	}

	void set_Oferte(const std::vector<Oferta_turistica> produse)
	{
		this->v = produse;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
	}

};