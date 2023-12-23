#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QString>
#include "Qt_cmake/mainwindow.h"
#include "classes/jeu.h"
#include "classes/joueur.h"
#include "Qt_cmake/qt_popup_info.h"
#include "Qt_cmake/qt_popup_yesno.h"
#include "main.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    InfoDialog info_dialog("Bienvenu dans le jeu Splendor Duel !");
    info_dialog.exec();

    popupYesNo yesno(nullptr, "Voulez vous commencer une nouvelle partie ou finir la dernière partie en cours (Oui/Non) ?");
    yesno.exec();
    char tmp = yesno.getUserChoice();


    if(tmp == 'Y'){
        gameFromScratch(argc, argv);
    }
    else {
        gameFromJson(argc, argv);
    }

    char tmp2 = 'Y';
    while(tmp2 == 'Y'){
        popupYesNo relaunch(nullptr, "Voulez vous recommencer (Oui/Non) ?");
        relaunch.show();
        tmp2 = relaunch.getUserChoice();
        if(tmp2 == 'Y'){
            gameFromScratch(argc, argv);
        }
    }

    return app.exec();
}
