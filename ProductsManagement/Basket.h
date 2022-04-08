#pragma once
#include <QtWidgets/Qwidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qLineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include <QtWidgets/qmainwindow.h>

#include <sstream>
#include <iomanip>
#include <string>
#include<qdebug.h>
#include<vector>
#include "MyGUI.h"
#include "Service.h"
#include "TableModel.h"
#include <qlistview.h>
using std::vector;
using std::string;
class Basket :public QMainWindow, public Observer {
public:
    Basket(Service& serv) :serv{ serv } {
        model = new MyTableModel{ serv.get_all() };
        lst->setModel(model);
        initGUI();
        loadData();
        initConnect();
        

    }
private:
    Service& serv;
    //QListWidget* lst = new QListWidget;
    QListWidget* wsh = new QListWidget;
    QPushButton* btnAddG = new QPushButton{ "Add in wishlist" };
    QPushButton* btnGenG = new QPushButton{ "Generate wishlist" };
    QPushButton* btnClearG = new QPushButton{ "Clear in wishlist" };
    QPushButton* btnExportG = new QPushButton{ "Export wishlist" };
    QLineEdit* txtDenumireG = new QLineEdit;
    QLineEdit* txtGenG = new QLineEdit;
    QTableWidget* tableWidget = new QTableWidget{ 0, 4 };
    MyTableModel* model;
    QListView* lst = new QListView;
    void initGUI() {
        QWidget* cw = new QWidget;
        setCentralWidget(cw);
        QHBoxLayout* lyMain = new QHBoxLayout{};
        cw->setLayout(lyMain);
        lyMain->addWidget(lst);

        QVBoxLayout* lyCentre = new QVBoxLayout{};
        auto formLyG = new QFormLayout;

        formLyG->addRow("Denumire", txtDenumireG);
        formLyG->addRow("Number", txtGenG);
        lyCentre->addLayout(formLyG);
        lyCentre->addWidget(btnAddG);
        lyCentre->addWidget(btnGenG);
        lyCentre->addWidget(btnClearG);
       // lyCentre->addWidget(btnExport);

        lyMain->addLayout(lyCentre);

        lyMain->addWidget(wsh);
    }

    void  update() override {
        loadWish();
        //loadTable();
    }

    void initConnect() {
        serv.addObserver(this);
         QObject::connect(btnAddG, &QPushButton::clicked, [&]() {
           
           
             auto denumire = txtDenumireG->text();
             try {
                 serv.add_in_wishlist(denumire.toStdString());
             }
             catch (Repo_Exception& re)
             {
                 auto err = QString::fromStdString(re.getMessage());
                 QMessageBox::warning(nullptr, "Error", err);
             }
             loadWish();
            });

         QObject::connect(btnGenG, &QPushButton::clicked, [&]() {
             auto denumire = txtGenG->text();
             try {
                 serv.generate_wishlist(denumire.toDouble());
             }
             catch (Repo_Exception& re)
             {
                 auto err = QString::fromStdString(re.getMessage());
                 QMessageBox::warning(nullptr, "Error", err);
             }
             loadWish();
             });

         QObject::connect(btnClearG, &QPushButton::clicked, [&]() {
             
             try {
                 serv.empty_wishlist();
             }
             catch (Repo_Exception& re)
             {
                 auto err = QString::fromStdString(re.getMessage());
                 QMessageBox::warning(nullptr, "Error", err);
             }
             loadWish();
             });
         
         QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
             if (lst->selectionModel()->selectedIndexes().isEmpty())
             {
                 txtDenumireG->setText("");
                 txtGenG->setText("");
                 
                 return;
             }
             txtDenumireG->clear();
             txtGenG->clear();
             auto curr = lst->selectionModel()->selectedIndexes().at(0);
             string name = curr.data(Qt::DisplayRole).toString().toStdString();
             Oferta_turistica o = serv.search(name);
             txtDenumireG->setText(QString::fromStdString(name));
             //txt_type->setText(QString::fromStdString(p.get_type()));
             //txt_prod->setText(QString::fromStdString(p.get_producer()));
             ///->setText(QString::number(p.get_price()));
             });
    }
    void loadWish() {
        wsh->clear();

        //vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };
        vector<Oferta_turistica> v = serv.get_all_wishlist();

        for (const auto& oferta : v) {

            wsh->addItem(QString::fromStdString(oferta.get_denumire()));

        }
    }

    void loadData() {
        
        vector<Oferta_turistica> v = serv.get_all();
        model->set_Oferte(v);
        /*
        //lst->clear();

        //vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };
       
     
        for (const auto& oferta : v) {

           // lst->addItem(QString::fromStdString(oferta.get_denumire()));

        }*/
    }
    /*
    void loadTable(vector<Oferta_turistica> v) {
        tableWidget->clear();
        tableWidget->setRowCount(0);
        tableWidget->setHorizontalHeaderLabels(QString("Denumire;Destinatie;Tip;Pret").split(";"));
        string denumire, destinatie, tip;
        double pret;
        int row = 0;
        for (const auto& oferta : v) {
            denumire = oferta.get_denumire();
            destinatie = oferta.get_destinatie();
            tip = oferta.get_tip();
            pret = oferta.get_pret();
            std::stringstream s;
            s << std::fixed << std::setprecision(3) << pret;
            auto q_den = QString::fromStdString(denumire);
            auto q_dest = QString::fromStdString(destinatie);
            auto q_tip = QString::fromStdString(tip);
            auto q_pret = QString::fromStdString(s.str());

            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(q_den));
            tableWidget->setItem(row, 1, new QTableWidgetItem(q_dest));
            tableWidget->setItem(row, 2, new QTableWidgetItem(q_tip));
            tableWidget->setItem(row, 3, new QTableWidgetItem(q_pret));
            row++;
        }
        tableWidget->setSizeAdjustPolicy(tableWidget->AdjustToContents);
    }
    */
};