QT = core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

SOURCES += \
    ../classes/carte.cpp \
    ../classes/jetons.cpp \
    ../classes/jeu.cpp \
    ../classes/joueur.cpp \
    ../classes/pioche.cpp \
    ../classes/plateau.cpp \
    ../classes/privilege.cpp \
    ../classes/sac.cpp \
    ../classes/tirage.cpp \
    ../main.cpp \
    main_old.cpp \
    mainwindow.cpp \
    plateau.cpp \
    tirages.cpp

HEADERS += \
    ../classes/Exception.h \
    ../classes/carte.h \
    ../classes/jetons.h \
    ../classes/jeu.h \
    ../classes/joueur.h \
    ../classes/pioche.h \
    ../classes/plateau.h \
    ../classes/privilege.h \
    ../classes/sac.h \
    ../classes/tirage.h \
    ../main.h \
    plateau.h \
    tirages.h \
