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

#include "BasketHistogram.h"
#include <sstream>
#include <iomanip>
#include <string>
#include<qdebug.h>
#include<vector>
#include "MyGUI.h"
#include "Service.h"
#include "Basket.h"
#include "Observer.h"
using std::vector;
using std::string;
class MyGUI:public QMainWindow {
public:
    MyGUI(Service& serv) :serv{ serv } {
        model = new MyTableModel{ serv.get_all() };
        lst->setModel(model);
	initGUI();
    loadData();
    initConnect();

   
    }
private:
    Service& serv;
    Basket bask{ serv };
    //QListWidget* lst = new QListWidget;
    MyTableModel* model;
    QListView* lst = new QListView;
    QPushButton* btnExit = new QPushButton{ "Exit" };
    QPushButton* btnAdd = new QPushButton{ "Adauga" };
    QPushButton* btnDel = new QPushButton{ "Sterge" };
    QPushButton* btnModif = new QPushButton{ "Modifica" };
    QPushButton* btnSearch = new QPushButton{ "Cauta" };


    QPushButton* btnAddG = new QPushButton{ "Add in wishlist" };
    QPushButton* btnGenG = new QPushButton{ "Generate wishlist" };
    QPushButton* btnClearG = new QPushButton{ "Clear in wishlist" };
    QPushButton* btnExportG = new QPushButton{ "Export wishlist" };
    QLineEdit* txtDenumireG = new QLineEdit;
    QLineEdit* txtGenG = new QLineEdit;

    QPushButton* crdBask = new QPushButton{ "CRUD Basket" };
    QPushButton* histBask = new QPushButton{ "Histogram Basket" };

    QPushButton* btnSortDenum = new QPushButton{ "SortByName" };
    QPushButton* btnSortDest = new QPushButton{ "SortByDestination" };
    QPushButton* btnSortType = new QPushButton{ "SortByType+Price" };
    QPushButton* btnFilterDest = new QPushButton{ "FilterByDestination" };
    QPushButton* btnFilterPrice = new QPushButton{ "FilterByPrice" };

    QPushButton* btnAddWishlist = new QPushButton{ "AddWishlist" };
    QPushButton* btnGenerateWishlist = new QPushButton{ "GenerateWishlist" };
    QPushButton* btnClearWishlist = new QPushButton{ "ClearWishlist" };
    
    QPushButton* btnExport = new QPushButton{ "Export" };
    QPushButton* btnUndo = new QPushButton{ "Undo" };

    QLineEdit* txtDenumire = new QLineEdit;
    QLineEdit* txtDestinatie = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;
    QTableWidget* tableWidget = new QTableWidget{ 0, 4 };

    QLineEdit* txtPretMin = new QLineEdit;
    QLineEdit* txtPretMax = new QLineEdit;
    QLineEdit* txtDestinatiefiltru = new QLineEdit;

    QMenuBar* menu_bar = new QMenuBar();
    QAction* basket_menu = new QAction("Basket");
 

    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            qDebug() << "exit button apasat";
            QMessageBox::information(nullptr, "Info", "Exit button apasat!");
            close();
            });

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            auto destinatie = txtDestinatie->text();
            auto tip = txtTip->text();
            auto pret = txtPret->text();
            try{
            serv.add(denumire.toStdString(), destinatie.toStdString(), tip.toStdString(), pret.toDouble());
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            reloadData(serv.get_all());
            });
        QObject::connect(btnDel, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            try{
            serv.remove(denumire.toStdString());
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            reloadData(serv.get_all());
            });
        QObject::connect(btnModif, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            auto destinatie = txtDestinatie->text();
            auto tip = txtTip->text();
            auto pret = txtPret->text();
            try {
                serv.modify(denumire.toStdString(), destinatie.toStdString(), tip.toStdString(), pret.toDouble());
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            reloadData(serv.get_all());
            });

        QObject::connect(btnSearch, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            try {
                auto oferta=serv.search(denumire.toStdString());
                auto strg = oferta.get_denumire() + " " + oferta.get_destinatie() + " " + oferta.get_tip() + " " + to_string(oferta.get_pret());
                QMessageBox::information(nullptr, "Result", QString::fromStdString(strg));
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            
            });


        QObject::connect(btnSortDenum, &QPushButton::clicked, [&]() {
            vector<Oferta_turistica> v = serv.generalSortSTL("denumire");
            model->set_Oferte(v);
            /*
            model->set_Oferte(v);
            try {
                vector<Oferta_turistica> v = serv.generalSortSTL("denumire");

                txtDenumire->clear();
                txtDestinatie->clear();
                txtTip->clear();
                txtPret->clear();
                lst->clear();

                //vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };
                
                loadTable(v);
                for (const auto& oferta : v) {

                    lst->addItem(QString::fromStdString(oferta.get_denumire()));

                }
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }

            });

        QObject::connect(btnSortDest, &QPushButton::clicked, [&]() {

            try {
                vector<Oferta_turistica> v = serv.generalSortSTL("destinatie");

                txtDenumire->clear();
                txtDestinatie->clear();
                txtTip->clear();
                txtPret->clear();
                lst->clear();

                //vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };

                loadTable(v);
                for (const auto& oferta : v) {

                    lst->addItem(QString::fromStdString(oferta.get_denumire()));

                }
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            */
            });

        QObject::connect(btnSortType, &QPushButton::clicked, [&]() {
            vector<Oferta_turistica> v = serv.generalSortSTL("tip+pret");
            model->set_Oferte(v);
            /*
            try {
                vector<Oferta_turistica> v = serv.generalSortSTL("tip+pret");

                txtDenumire->clear();
                txtDestinatie->clear();
                txtTip->clear();
                txtPret->clear();
                lst->clear();

                //vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };

                loadTable(v);
                for (const auto& oferta : v) {

                    lst->addItem(QString::fromStdString(oferta.get_denumire()));

                }
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }

            });

        QObject::connect(btnFilterDest, &QPushButton::clicked, [&]() {

            auto destinatie = txtDestinatiefiltru->text();
            try {

                vector<Oferta_turistica> oferte = serv.filtreaza("destinatie", destinatie.toStdString(), 0, 0);

                txtDestinatiefiltru->clear();
                lst->clear();

                loadTable(oferte);
                for (const auto& oferta : oferte) {

                    lst->addItem(QString::fromStdString(oferta.get_denumire()));

                }
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            */
            });
        
        QObject::connect(btnFilterPrice, &QPushButton::clicked, [&]() {

            auto pretMax = txtPretMax->text();
            auto pretMin = txtPretMin->text();
            vector<Oferta_turistica> v = serv.filtreaza("pret", "", pretMin.toDouble(), pretMax.toDouble());
            model->set_Oferte(v);
            /*
            try {

                vector<Oferta_turistica> oferte = serv.filtreaza("pret", "", pretMin.toDouble(), pretMax.toDouble());

                txtPretMax->clear();
                txtPretMin->clear();
                lst->clear();

                loadTable(oferte);
                for (const auto& oferta : oferte) {

                    lst->addItem(QString::fromStdString(oferta.get_denumire()));

                }
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }*/

            });

        QObject::connect(btnExport, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            try {
                serv.exportFile(denumire.toStdString());
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            
            });
        QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            try {
                serv.undo();
            }
            catch (Repo_Exception& re)
            {
                auto err = QString::fromStdString(re.getMessage());
                QMessageBox::warning(nullptr, "Error", err);
            }
            reloadData(serv.get_all());
            });
        
        QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {

            if (lst->selectionModel()->selectedIndexes().isEmpty())
            {
                txtDenumire->setText("");
                txtTip->setText("");
                txtDestinatie->setText("");
                txtPret->setText("");
                return;
            }
            txtDenumire->clear();
            txtTip->clear();
            txtDestinatie->clear();
            txtPret->clear();
            auto curr = lst->selectionModel()->selectedIndexes().at(0);
            string name = curr.data(Qt::DisplayRole).toString().toStdString();
            Oferta_turistica p = serv.search(name);
            txtDenumire->setText(QString::fromStdString(name));
            txtTip->setText(QString::fromStdString(p.get_tip()));
            txtDestinatie->setText(QString::fromStdString(p.get_destinatie()));
            txtPret->setText(QString::number(p.get_pret()));
            });
            
                /*
        QObject::connect(lst, &QListWidget::itemClicked, [&]() {
            auto sel = lst->currentItem();
          
                auto q_denumire = sel->text();
                auto denumire = q_denumire.toStdString();
                txtDenumire->setText(q_denumire);
                auto o = serv.search(denumire);
                
                txtDestinatie->setText(QString::fromStdString(o.get_destinatie()));
                txtTip->setText(QString::fromStdString(o.get_tip()));
                txtPret->setText(QString::number(o.get_pret()));
            
            });*/
            
        QObject::connect(basket_menu, &QAction::triggered, this, [&]() {
            bask.show();
            });

        QObject::connect(crdBask, &QPushButton::clicked, [&]() {
            auto nc = new Basket{ serv };
            nc->show();
            });
        QObject::connect(histBask, &QPushButton::clicked, [&]() {
            auto nc = new BasketHistogram{ serv };
            nc->show();
            });

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
            
            });
    }
   
    

    void loadData() {

        txtDenumire->clear();
        txtDestinatie->clear();
        txtTip->clear();
        txtPret->clear();
        
        vector<Oferta_turistica> v = serv.get_all();
        model->set_Oferte(v);
        //loadTable(v);
        /*
        lst->clear();
        
        //vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };
        vector<Oferta_turistica> v = serv.get_all();
        
        for (const auto& oferta : v) {

            lst->addItem(QString::fromStdString(oferta.get_denumire()));
           
        }*/
    }

    void reloadData(vector<Oferta_turistica> v) {

        txtDenumire->clear();
        txtDestinatie->clear();
        txtTip->clear();
        txtPret->clear();
        model->set_Oferte(v);
        //lst->clear();
        //loadTable(v);
        /*
        for (const auto& oferta : v) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(oferta.get_denumire()));
            item->setData(Qt::UserRole, QString::fromStdString(oferta.get_denumire()));
            lst->addItem(item);

        }
        */
    }
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
	void initGUI() {

        QWidget* cw = new QWidget;
        setCentralWidget(cw);
        cw->setStyleSheet("background-color:#97B3D0FF");
        btnExit->setStyleSheet("background-color:#9F6B99FF");
        btnAdd->setStyleSheet("background-color:#9F6B99FF");
        btnDel->setStyleSheet("background-color:#9F6B99FF");
        btnModif->setStyleSheet("background-color:#9F6B99FF");
        btnSearch->setStyleSheet("background-color:#9F6B99FF");
        btnSortDenum-> setStyleSheet("background-color:#9F6B99FF");
        btnSortDest->setStyleSheet("background-color:#9F6B99FF");
        btnSortType->setStyleSheet("background-color:#9F6B99FF");
        btnFilterDest->setStyleSheet("background-color:#9F6B99FF");
        btnFilterPrice->setStyleSheet("background-color:#9F6B99FF");

        btnAddWishlist->setStyleSheet("background-color:#9F6B99FF");
        btnGenerateWishlist->setStyleSheet("background-color:#9F6B99FF");
        btnClearWishlist->setStyleSheet("background-color:#9F6B99FF");
        
        btnExport = new QPushButton{ "Export" };
        btnUndo = new QPushButton{ "Undo" };
        btnExport->setStyleSheet("background-color:#9F6B99FF");
        btnUndo->setStyleSheet("background-color: #9F6B99FF");

        QHBoxLayout* lyMain = new QHBoxLayout{};
        cw->setLayout(lyMain);
        menu_bar->addAction(basket_menu);
        setMenuBar(menu_bar);
        lyMain->addWidget(lst);
        lst->setStyleSheet("background-color:rgb(255, 229, 204)");
        menu_bar->setStyleSheet("background-color:rgb(255, 153, 51)");

        auto stgLy = new QVBoxLayout{};

        auto formLy = new QFormLayout;
        
        formLy->addRow("Denumire", txtDenumire);
        formLy->addRow("Destinatie", txtDestinatie);
        formLy->addRow("Tip", txtTip);
        formLy->addRow("Pret", txtPret);

        stgLy->addLayout(formLy);

        auto  lyBtn1 = new QHBoxLayout{};
     
      
        lyBtn1->addWidget(btnAdd);
        lyBtn1->addWidget(btnDel);
        lyBtn1->addWidget(btnModif);
        lyBtn1->addWidget(btnSearch);
        lyBtn1->addWidget(btnExit);

        auto  lyBtn2 = new QHBoxLayout{};

        lyBtn2->addWidget(btnSortDenum);
        lyBtn2->addWidget(btnSortDest);
        lyBtn2->addWidget(btnSortType);

        auto  lyBtn3 = new QHBoxLayout{};

        lyBtn3->addWidget(btnFilterDest);
        lyBtn3->addWidget(btnFilterPrice);

        stgLy->addLayout(lyBtn1);
        stgLy->addLayout(lyBtn2);
        stgLy->addLayout(lyBtn3);

        auto formLy2 = new QFormLayout;
        
        formLy2->addRow("Destinatie filtru", txtDestinatiefiltru);
        formLy2->addRow("Pret minim", txtPretMin);
        formLy2->addRow("Pret maxim", txtPretMax);
        
        stgLy->addLayout(formLy2);

        lyMain->addLayout(stgLy);

        QVBoxLayout* lyCentre = new QVBoxLayout{};
        auto formLyG = new QFormLayout;

        formLyG->addRow("Denumire", txtDenumireG);
        formLyG->addRow("Number", txtGenG);
        lyCentre->addLayout(formLyG);
        lyCentre->addWidget(btnAddG);
        lyCentre->addWidget(btnGenG);
        lyCentre->addWidget(btnClearG);
        lyCentre->addWidget(crdBask);
        lyCentre->addWidget(histBask);

        // lyCentre->addWidget(btnExport);

        lyMain->addLayout(lyCentre);
        btnAddG->setStyleSheet("background-color: #9F6B99FF");
        btnGenG->setStyleSheet("background-color: #9F6B99FF");
        btnClearG->setStyleSheet("background-color: #9F6B99FF");
        crdBask->setStyleSheet("background-color: #9F6B99FF");
        histBask->setStyleSheet("background-color: #9F6B99FF");

        //lyMain->addWidget(tableWidget);

        //tableWidget->setStyleSheet("background-color:rgb(255, 229, 204)");

        auto  lyBtn4 = new QHBoxLayout{};

        lyBtn4->addWidget(btnExport);
        lyBtn4->addWidget(btnUndo);

        stgLy->addLayout(lyBtn4);

        
	}
  
};