#include "mainwindow.h"

MainWindow::Handler MainWindow::handler;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    jeu = &Jeu::getJeu();

    // Initialize player name labels
    topPlayerNameLabel = new QLabel("Player 1");
    bottomPlayerNameLabel = new QLabel("Player 2");
    topPlayerNameLabel->setStyleSheet("color: white;");
    bottomPlayerNameLabel->setStyleSheet("color: white;");

    QWidget *centralWidget = new QWidget(this);

    // Background pour toute la fenêtre
    centralWidget->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(16);

    // ######## SCORE EN HAUT ET BOUTONS ########


    // Scores sur QLCD Display
    topScoreDisplay = new QLCDNumber(); // Display avec 2 digits
    bottomScoreDisplay = new QLCDNumber(); // Display avec 2 digits

    // Afficher 0 pour l'instant
    topScoreDisplay->display(0);
    bottomScoreDisplay->display(0);

    // Les rajouter sur le layout principal
    mainLayout->addWidget(topPlayerNameLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(topScoreDisplay, 0, Qt::AlignCenter); // Alligner au centre

    // Boutons du haut (cartes et jetons)
    viewCardsButtonTop = new QPushButton("Voir cartes");
    viewJetonsButtonTop = new QPushButton("Voir jetons");

    // Faire le texte blanc
    viewCardsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewJetonsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");

    // Connecter aux fonctionnalités
    connect(viewCardsButtonTop, &QPushButton::clicked, this, &MainWindow::showCards);
    connect(viewJetonsButtonTop, &QPushButton::clicked, this, &MainWindow::showJetons);


    // Ajouter un layout et les mettre dedans
    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    topButtonLayout->addWidget(viewCardsButtonTop);
    topButtonLayout->addWidget(viewJetonsButtonTop);
    mainLayout->addLayout(topButtonLayout);




    // ######## PLATEAU ET TIRAGES ########


    // Plateau et tirages
    QWidget *middleContainer = new QWidget;
    QHBoxLayout *middleLayout = new QHBoxLayout(middleContainer);

    // Créer 'remplir plateau' et le connecter à un slot
    remplirPlateauButton = new QPushButton("Remplir Plateau", this);
    remplirPlateauButton->setStyleSheet("color: rgba(255, 255, 255, 255);");
    connect(remplirPlateauButton, &QPushButton::clicked, this, &MainWindow::remplirPlateau);

    // Créer le plateau et les tirages
    plateau = &Qt_Plateau::getPlateau();
    tirages = new Qt_Tirages;

    QVBoxLayout *plateauLayout = new QVBoxLayout();
    plateauLayout->addWidget(plateau);
    plateauLayout->addWidget(remplirPlateauButton); // Ajouter 'remplir plateau' en dessous plateau

    middleLayout->addLayout(plateauLayout); // Rajouter le plateau et le bouton au middle layout
    middleLayout->addStretch(); // Stretch pour mettre les tirages à droite
    tirages->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    middleLayout->addWidget(tirages);
    mainLayout->addWidget(middleContainer);
    mainLayout->addWidget(remplirPlateauButton);


    // ######## CONDITION DE VICTOIRE ET REGLES ########


    QVBoxLayout *regles = new QVBoxLayout;

    // Ajouter le bouton de règles
    QPushButton *viewRegles = new QPushButton("Voir règles");
    viewRegles->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewRegles->setFixedWidth(397 / 3);
    connect(viewRegles, &QPushButton::clicked, this, &MainWindow::openWebLink);

    // Conditions de victoire et son image
    QLabel *conditionsVictoire = new QLabel(this);
    QPixmap originalPixmap("../src/Reste_detoure/Conditions_victoire.png");
    QPixmap scaledPixmap = originalPixmap.scaled(397 / 3, 330 / 3, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    conditionsVictoire->setPixmap(scaledPixmap);
    conditionsVictoire->setFixedSize(scaledPixmap.size());

    // Les rajouter au layout
    regles->addWidget(conditionsVictoire, Qt::AlignCenter);
    regles->addWidget(viewRegles, Qt::AlignCenter);
    regles->addStretch(1);

    middleLayout->addLayout(regles, Qt::AlignCenter);



    // ######## SCORE EN BAS ET BOUTONS ########


    // Ajouter le score en bas
    mainLayout->addWidget(bottomPlayerNameLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(bottomScoreDisplay, 0, Qt::AlignCenter); // Align center at the bottom


    // Boutons du bas
    viewCardsButtonBottom = new QPushButton("Voir cartes");
    viewJetonsButtonBottom = new QPushButton("Voir jetons");
    viewCardsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewJetonsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
    connect(viewCardsButtonBottom, &QPushButton::clicked, this, &MainWindow::showCards);
    connect(viewJetonsButtonBottom, &QPushButton::clicked, this, &MainWindow::showJetons);

    QHBoxLayout *bottomButtonLayout = new QHBoxLayout;
    bottomButtonLayout->addWidget(viewCardsButtonBottom);
    bottomButtonLayout->addWidget(viewJetonsButtonBottom);
    mainLayout->addLayout(bottomButtonLayout);

    // Set le widget central
    setCentralWidget(centralWidget);

    // Connexions
    connect(this, &MainWindow::triggerNextAction, this, &MainWindow::nextAction);
    connect(this, &MainWindow::triggerYesNo, this, &MainWindow::YesNo);
    connect(this, &MainWindow::triggerInfo, this, &MainWindow::showInfo);
    connect(this, &MainWindow::actionDone, &wait_for_action, &QEventLoop::quit);
    connect(this, &MainWindow::triggerTiragePioche, this, &MainWindow::popTiragePioche);

}

MainWindow::~MainWindow() {
    // Rien
}

void MainWindow::showCards() {
    QDialog *cardsDialog = new QDialog(this);
    cardsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    cardsDialog->exec(); // L'afficher
}

void MainWindow::showJetons() {
    QDialog *jetonsDialog = new QDialog(this);
    QVBoxLayout *dialogLayout = new QVBoxLayout(jetonsDialog);

    Qt_Jetons_Main *jet_bas = new Qt_Jetons_Main(jetonsDialog);
    jetonsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    dialogLayout->addWidget(jet_bas);

    jetonsDialog->exec();
}


void MainWindow::updateTopScore(int score) {
    topScoreDisplay->display(score);
}

void MainWindow::updateBottomScore(int score) {
    bottomScoreDisplay->display(score);
}

void MainWindow::remplirPlateau() {
    // Mettre l'action ici
}

void MainWindow::openWebLink() {
    QDesktopServices::openUrl(QUrl("https://cdn.1j1ju.com/medias/da/39/6a-splendor-duel-regle.pdf"));
}

void MainWindow::setTopPlayerName(const QString &name) {
    topPlayerNameLabel->setText(name);
    topPlayerNameLabel->update();
}

void MainWindow::setBottomPlayerName(const QString &name) {
    bottomPlayerNameLabel->setText(name);
    bottomPlayerNameLabel->update();
}

void MainWindow::updateTirages(){

    // Update des pointeurs carte

    // Tirage 1
    qDebug() << "Tirage1";
    for (int i = 0; i < Jeu::getJeu().get_tirage_1()->getNbCartes(); i++){
        tirages->getTier1()[i]->setCard(Jeu::getJeu().get_tirage_1()->getTirage()[i]);

        // Update des visuels
        tirages->getTier1()[i]->updateAppearance();
    }


    // Tirage 2
    qDebug() << "Tirage2";
    for (int i = 0; i < Jeu::getJeu().get_tirage_2()->getNbCartes(); i++){
        tirages->getTier2()[i]->setCard(Jeu::getJeu().get_tirage_2()->getTirage()[i]);

        // Update des visuels
        tirages->getTier2()[i]->updateAppearance();
    }


    // Tirage 3
    qDebug() << "Tirage3";
    for (int i = 0; i < Jeu::getJeu().get_tirage_3()->getNbCartes(); i++){
        tirages->getTier3()[i]->setCard(Jeu::getJeu().get_tirage_3()->getTirage()[i]);

        // Update des visuels
        tirages->getTier3()[i]->updateAppearance();
    }


    // Cartes royales
    qDebug() << "CartesRoyales";
    for (int i = 0; i < Jeu::getJeu().getCartesRoyales().size(); i++){
        tirages->getRoyalCards()[i]->setCard(Jeu::getJeu().getCartesRoyales()[i]);

        // Update des visuels
        tirages->getRoyalCards()[i]->updateAppearance();
    }

    if (tirages->getDeckImage1() != nullptr) tirages->getDeckImage1()->updateAppearance("../src/Reste_detoure/Pioche_niveau_1.png");
    if (tirages->getDeckImage2() != nullptr) tirages->getDeckImage2()->updateAppearance("../src/Reste_detoure/Pioche_niveau_2.png");
    if (tirages->getDeckImage3() != nullptr) tirages->getDeckImage3()->updateAppearance("../src/Reste_detoure/Pioche_niveau_3.png");



}

void MainWindow::updatePlateau(){

    Plateau::get_plateau().printTab();

    // Update des pointeurs jeton

    for (int i = 0; i < NJETONS; i++){
        plateau->getJetons()[i]->setJeton(Plateau::get_plateau().get_plateau_i(i));
    }

    // Update des visuels

    for (int i = 0; i < NJETONS; i++){
        // Mise à jour jetons

        // if (plateau->getJetons()[i]->getJeton() != nullptr) qDebug() << toString(plateau->getJetons()[i]->getJeton()->getColor());
        plateau->getJetons()[i]->updateAppearance();
    }


}

void MainWindow::updatePrivileges(){
    int nb_privileges = Jeu::getJeu().getNbPrivilege();
    QIcon icon(QPixmap(QString::fromStdString("../src/Reste_detoure/Privilege.png")));
    switch(nb_privileges){
    case 0:
        plateau->getPrivilege1()->setIcon(QIcon());
        plateau->getPrivilege1()->setIconSize(plateau->getPrivilege1()->size());
        plateau->getPrivilege2()->setIcon(QIcon());
        plateau->getPrivilege2()->setIconSize(plateau->getPrivilege2()->size());
        plateau->getPrivilege3()->setIcon(QIcon());
        plateau->getPrivilege3()->setIconSize(plateau->getPrivilege3()->size());
        break;
    case 1:
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege1()->setIcon(icon);
        plateau->getPrivilege1()->setIconSize(plateau->getPrivilege1()->size());
        plateau->getPrivilege2()->setIcon(QIcon());
        plateau->getPrivilege2()->setIconSize(plateau->getPrivilege2()->size());
        plateau->getPrivilege3()->setIcon(QIcon());
        plateau->getPrivilege3()->setIconSize(plateau->getPrivilege3()->size());
        break;
    case 2:
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege1()->setIcon(icon);
        plateau->getPrivilege1()->setIconSize(plateau->getPrivilege1()->size());
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege2()->setIcon(icon);
        plateau->getPrivilege2()->setIconSize(plateau->getPrivilege2()->size());
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege3()->setIcon(QIcon());
        plateau->getPrivilege3()->setIconSize(plateau->getPrivilege3()->size());
        break;
    case 3:
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege1()->setIcon(icon);
        plateau->getPrivilege1()->setIconSize(plateau->getPrivilege1()->size());
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege2()->setIcon(icon);
        plateau->getPrivilege2()->setIconSize(plateau->getPrivilege2()->size());
        // qDebug() << jeton->getVisuel();
        plateau->getPrivilege3()->setIcon(icon);
        plateau->getPrivilege3()->setIconSize(plateau->getPrivilege3()->size());
        break;
    }
    plateau->getPrivilege1()->update();
    plateau->getPrivilege2()->update();
    plateau->getPrivilege3()->update();
}

void MainWindow::nextAction(int* tmp, Joueur* j){

    // qDebug() << "IN NEXT ACTION";
    int nb_choice = j->getOptionalChoices();

    ChoiceDialog dialog(nb_choice, this);
    if (dialog.exec() == QDialog::Accepted) {
        *tmp = dialog.getUserChoice();

    }

}

void MainWindow::YesNo(char* choice, const std::string& string){

    popupYesNo dialog(this, string);
    if (dialog.exec() == QDialog::Accepted) {
        *choice = dialog.getUserChoice();
    }

}

void MainWindow::showInfo(const string& string){

    InfoDialog dialog(QString::fromStdString(string), this);
    dialog.exec();

}

void MainWindow::jetonClicked(Qt_jeton* j){
    if (j != nullptr) qDebug() << "Jeton cliqué : " << j->getJeton()->getVisuel();
    else qDebug() << "nullptr jeton";
    setIndiceJetonClick(j->getIndice());
    MainWindow::getMainWindow().actionDone();
}
