#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ######## SCORE LABELS ########

    // ######## SCORE DISPLAYS ########

    // Create score displays using QLCDNumber
    QLCDNumber *topScoreDisplay = new QLCDNumber(2); // Display with 2 digits
    QLCDNumber *bottomScoreDisplay = new QLCDNumber(2); // Display with 2 digits
    topScoreDisplay->display(0);
    bottomScoreDisplay->display(0);

    // Add score displays to the main layout
    mainLayout->addWidget(topScoreDisplay, 0, Qt::AlignCenter); // Align center at the top

    // Add top buttons
    viewCardsButtonTop = new QPushButton("View Cards");
    viewJetonsButtonTop = new QPushButton("View Jetons");
    connect(viewCardsButtonTop, &QPushButton::clicked, this, &MainWindow::showCards);
    connect(viewJetonsButtonTop, &QPushButton::clicked, this, &MainWindow::showJetons);

    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    topButtonLayout->addWidget(viewCardsButtonTop);
    topButtonLayout->addWidget(viewJetonsButtonTop);
    mainLayout->addLayout(topButtonLayout);

    // ######## PLATEAU ET TIRAGES ########

    // Plateau and tirages
    QWidget *middleContainer = new QWidget;
    QHBoxLayout *middleLayout = new QHBoxLayout(middleContainer);

    // Create the 'remplir plateau' button and connect it to a slot
    remplirPlateauButton = new QPushButton("Remplir Plateau", this);
    connect(remplirPlateauButton, &QPushButton::clicked, this, &MainWindow::remplirPlateau);

    Qt_Plateau *plateau = new Qt_Plateau;
    Qt_Tirages *tirages = new Qt_Tirages;

    QVBoxLayout *plateauLayout = new QVBoxLayout();
    plateauLayout->addWidget(plateau);
    plateauLayout->addWidget(remplirPlateauButton); // Add the 'remplir plateau' button below the plateau

    middleLayout->addLayout(plateauLayout); // Add the plateau and button layout to the middle layout
    middleLayout->addStretch(); // Add a stretch to push tirages to the right
    middleLayout->addWidget(tirages);

    mainLayout->addWidget(middleContainer);

    mainLayout->addWidget(remplirPlateauButton);


    // Add bottom score label to the main layout
    mainLayout->addWidget(bottomScoreDisplay, 0, Qt::AlignCenter); // Align center at the bottom

    // Add bottom buttons
    viewCardsButtonBottom = new QPushButton("View Cards");
    viewJetonsButtonBottom = new QPushButton("View Jetons");
    connect(viewCardsButtonBottom, &QPushButton::clicked, this, &MainWindow::showCards);
    connect(viewJetonsButtonBottom, &QPushButton::clicked, this, &MainWindow::showJetons);

    QHBoxLayout *bottomButtonLayout = new QHBoxLayout;
    bottomButtonLayout->addWidget(viewCardsButtonBottom);
    bottomButtonLayout->addWidget(viewJetonsButtonBottom);
    mainLayout->addLayout(bottomButtonLayout);

    // Set the central widget and margins
    setCentralWidget(centralWidget);
}

void MainWindow::showCards() {
    QDialog *cardsDialog = new QDialog(this);

    cardsDialog->exec(); // Show the dialog
}

void MainWindow::showJetons() {
    QDialog *jetonsDialog = new QDialog(this);
    QVBoxLayout *dialogLayout = new QVBoxLayout(jetonsDialog);

    Qt_Jetons_Main *jet_bas = new Qt_Jetons_Main(jetonsDialog);
    dialogLayout->addWidget(jet_bas);

    jetonsDialog->exec();
}


/*void MainWindow::updateTopScore(int score) {
    topScoreDisplay->display(score);
}

void MainWindow::updateBottomScore(int score) {
    bottomScoreDisplay->display(score);
}*/

void MainWindow::remplirPlateau() {
    // Placeholder for action when 'remplir plateau' is clicked
}

