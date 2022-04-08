#include "Oferta_turistica.h"
#include "Repo.h"
#include "Service.h"
//#include "UI.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Repo.h"
#include "Service.h"
#include "LabGrafic.h"
//#include "testSortare.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qLineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget>
#include <string>
#include<vector>
#include "MyGUI.h"
using std::vector;
using std::string;
/*

#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>
*/
int main(int argc, char* argv[])
{
    
    test_repo();
    test_repo_file();
    test_service();
    test_undo();
    QApplication a(argc, argv);
    RepoFile repo{"fisi.csv"};
    Service serv{ repo };
 
    MyGUI gui{ serv };
    gui.show();
    /*
    QWidget w{};
    QHBoxLayout* lyMain = new QHBoxLayout{};
    w.setLayout(lyMain);
    auto lst = new QListWidget;
    vector<string> allProduct = { "prod1","prod2","prod3",  "prod12","prod15","prod17" , "prod22","prod34","prod56" };
    for (const auto& numeProdus : allProduct) {

        lst->addItem(QString::fromStdString(numeProdus));
    }
    lyMain->addWidget(lst);


    auto stgLy = new QVBoxLayout{};

    auto formLy = new QFormLayout;
    formLy->addRow("Denumire", new QLineEdit);
    formLy->addRow("Destinatie", new QLineEdit);
    formLy->addRow("Tip", new QLineEdit);
    formLy->addRow("Pret", new QLineEdit);
    
    stgLy->addLayout(formLy);
 
   auto  lyBtn = new QHBoxLayout{};
   lyBtn->addWidget(new QPushButton{ "Adauga" });
   lyBtn->addWidget(new QPushButton{ "Sterge" });
   lyBtn->addWidget(new QPushButton{ "Modifica" });
   lyBtn->addWidget(new QPushButton{ "Exit" });
   stgLy->addLayout(lyBtn);
   lyMain->addLayout(stgLy);
    w.show();
 */
    return a.exec();
}
