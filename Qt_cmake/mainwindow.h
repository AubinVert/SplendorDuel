#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qt_tirages.h"
#include "qt_plateau.h"
#include "qt_jetons_bas.h"
#include "qt_jetons_main.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>


class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H
