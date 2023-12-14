#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ######## SCORE LABELS ########

    // Create score labels
    QLabel *topScoreLabel = new QLabel("X score: 0"); // Initially set to 0
    QLabel *bottomScoreLabel = new QLabel("Y score: 0"); // Initially set to 0

    // Set a name to the labels for future reference
    topScoreLabel->setObjectName("topScoreLabel");
    bottomScoreLabel->setObjectName("bottomScoreLabel");

    // Configure labels (font size, color, etc.)
    topScoreLabel->setStyleSheet("font-size: 24px; color: black;");
    bottomScoreLabel->setStyleSheet("font-size: 24px; color: black;");

    // Add top score label to the main layout
    mainLayout->addWidget(topScoreLabel, 0, Qt::AlignCenter); // Align center at the top

    // Wrap each component in a separate QWidget if needed

    // ######## JETONS HAUT ########

    // Top jetons
    QWidget *topJetonsContainer = new QWidget;
    QVBoxLayout *topJetonsLayout = new QVBoxLayout(topJetonsContainer);
    Qt_Jetons_Main *jet_haut = new Qt_Jetons_Main;
    topJetonsLayout->addWidget(jet_haut);
    mainLayout->addWidget(topJetonsContainer);

    // ######## PLATEAU ET TIRAGES ########

    // Plateau and tirages
    QWidget *middleContainer = new QWidget;
    QHBoxLayout *middleLayout = new QHBoxLayout(middleContainer);
    Qt_Plateau *plateau = new Qt_Plateau;
    Qt_Tirages *tirages = new Qt_Tirages;

    // Align tirages to the right
    middleLayout->addWidget(plateau);
    middleLayout->addStretch(); // Add a stretch to push tirages to the right
    middleLayout->addWidget(tirages);

    mainLayout->addWidget(middleContainer);

    // ######## JETONS BAS ########

    // Bottom jetons
    QWidget *bottomJetonsContainer = new QWidget;
    QVBoxLayout *bottomJetonsLayout = new QVBoxLayout(bottomJetonsContainer);
    Qt_Jetons_Main *jet_bas = new Qt_Jetons_Main;
    bottomJetonsLayout->addWidget(jet_bas);
    mainLayout->addWidget(bottomJetonsContainer);

    // Add bottom score label to the main layout
    mainLayout->addWidget(bottomScoreLabel, 0, Qt::AlignCenter); // Align center at the bottom

    // Set the central widget and margins
    setCentralWidget(centralWidget);
}
