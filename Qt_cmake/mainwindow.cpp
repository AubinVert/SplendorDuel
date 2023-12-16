#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);

    centralWidget->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");

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
    viewCardsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewJetonsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");
    connect(viewCardsButtonTop, &QPushButton::clicked, this, &MainWindow::showCards);
    connect(viewJetonsButtonTop, &QPushButton::clicked, this, &MainWindow::showJetons);

    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    topButtonLayout->addWidget(viewCardsButtonTop);
    topButtonLayout->addWidget(viewJetonsButtonTop);
    mainLayout->addLayout(topButtonLayout);

    // ######## CONDITION DE VICTOIRE ET REGLES ########

    QGridLayout *regles = new QGridLayout;

    // Add top buttons
    QPushButton *viewRegles = new QPushButton("View Regles");
    viewRegles->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewRegles->setFixedWidth(100);
    connect(viewRegles, &QPushButton::clicked, this, &MainWindow::openWebLink);

    QLabel *conditionsVictoire = new QLabel(this);

    // Load the image
    QPixmap originalPixmap("../src/Reste_detoure/Conditions_victoire.png");

    // Scale the image while maintaining aspect ratio
    QPixmap scaledPixmap = originalPixmap.scaled(397 / 2, 330 / 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Set the pixmap to the label
    conditionsVictoire->setPixmap(scaledPixmap);

    // Set the label size to the size of the scaled pixmap
    conditionsVictoire->setFixedSize(scaledPixmap.size());

    regles->addWidget(viewRegles, 0, 0, Qt::AlignCenter);
    regles->addWidget(conditionsVictoire, 0 ,1, Qt::AlignCenter);

    mainLayout->addLayout(regles);

    // ######## PLATEAU ET TIRAGES ########

    // Plateau and tirages
    QWidget *middleContainer = new QWidget;
    QHBoxLayout *middleLayout = new QHBoxLayout(middleContainer);

    // Create the 'remplir plateau' button and connect it to a slot
    remplirPlateauButton = new QPushButton("Remplir Plateau", this);
    remplirPlateauButton->setStyleSheet("color: rgba(255, 255, 255, 255);");
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
    viewCardsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewJetonsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
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

void MainWindow::openWebLink() {
    QDesktopServices::openUrl(QUrl("https://cdn.1j1ju.com/medias/da/39/6a-splendor-duel-regle.pdf"));
}
