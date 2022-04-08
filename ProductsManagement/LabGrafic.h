#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LabGrafic.h"

class LabGrafic : public QMainWindow
{
    Q_OBJECT

public:
    LabGrafic(QWidget *parent = Q_NULLPTR);

private:
    Ui::LabGraficClass ui;
};
