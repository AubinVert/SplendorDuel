#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tirages.h"
#include "plateau.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>


class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H
