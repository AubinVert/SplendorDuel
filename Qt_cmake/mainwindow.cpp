#include "mainwindow.h"
#include "qt_popup_couleur.h"

MainWindow::Handler MainWindow::handler;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), buyingCard(false) {

    jeu = &Jeu::getJeu();

    // Initialize player name labels
    topPlayerNameLabel = new QLabel("Player 1");
    bottomPlayerNameLabel = new QLabel("Player 2");
    topPlayerNameLabel->setStyleSheet("QLabel { color: white; background-color: white; border: 1px solid white; }");
    bottomPlayerNameLabel->setStyleSheet("QLabel { color: white; background-color: white; border: 1px solid white; }");

    QWidget *centralWidget = new QWidget(this);

    // Background pour toute la fenêtre
    centralWidget->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(16);

    quijoue = new QLabel("Qui joue");
    quijoue->setStyleSheet("QLabel { color: white; background-color: white; border: 1px solid white; }");
    mainLayout->addWidget(quijoue, 0, Qt::AlignLeft);

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
    viewCardsButtonTop = new QPushButton("Voir cartes achetées");
    viewJetonsButtonTop = new QPushButton("Voir jetons");
    viewReservedCardsButtonTop = new QPushButton("Voir cartes réservées");

    // Faire le texte blanc
    viewCardsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewJetonsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewReservedCardsButtonTop->setStyleSheet("color: rgba(255, 255, 255, 255);");

    // Connecter aux fonctionnalités
    connect(viewCardsButtonTop, &QPushButton::clicked, this, &MainWindow::showBoughtCardsTop);
    connect(viewJetonsButtonTop, &QPushButton::clicked, this, &MainWindow::showJetonsTop);
    connect(viewReservedCardsButtonTop, &QPushButton::clicked, this, &MainWindow::showReservedCardsTop);


    // Ajouter un layout et les mettre dedans
    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    topButtonLayout->addWidget(viewCardsButtonTop);
    topButtonLayout->addWidget(viewJetonsButtonTop);
    topButtonLayout->addWidget(viewReservedCardsButtonTop);
    mainLayout->addLayout(topButtonLayout);

    // ######## PLATEAU ET TIRAGES ########


    // Plateau et tirages
    QWidget *middleContainer = new QWidget;
    QHBoxLayout *middleLayout = new QHBoxLayout(middleContainer);

    // Créer le plateau et les tirages
    plateau = &Qt_Plateau::getPlateau();
    tirages = new Qt_Tirages;

    QVBoxLayout *plateauLayout = new QVBoxLayout();
    plateauLayout->addWidget(plateau);

    middleLayout->addLayout(plateauLayout); // Rajouter le plateau et le bouton au middle layout
    middleLayout->addStretch(); // Stretch pour mettre les tirages à droite
    tirages->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    middleLayout->addWidget(tirages);
    mainLayout->addWidget(middleContainer);

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
    viewCardsButtonBottom = new QPushButton("Voir cartes achetées");
    viewJetonsButtonBottom = new QPushButton("Voir jetons");
    viewReservedCardsButtonBottom = new QPushButton("Voir cartes réservées");

    viewCardsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewJetonsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
    viewReservedCardsButtonBottom->setStyleSheet("color: rgba(255, 255, 255, 255);");
    connect(viewCardsButtonBottom, &QPushButton::clicked, this, &MainWindow::showBoughtCardsBottom);
    connect(viewJetonsButtonBottom, &QPushButton::clicked, this, &MainWindow::showJetonsBottom);
    connect(viewReservedCardsButtonBottom, &QPushButton::clicked, this, &MainWindow::showReservedCardsBottom);

    QHBoxLayout *bottomButtonLayout = new QHBoxLayout;
    bottomButtonLayout->addWidget(viewCardsButtonBottom);
    bottomButtonLayout->addWidget(viewJetonsButtonBottom);
    bottomButtonLayout->addWidget(viewReservedCardsButtonBottom);
    mainLayout->addLayout(bottomButtonLayout);

    // Set le widget central
    setCentralWidget(centralWidget);

    // Connexions
    connect(this, &MainWindow::triggerNextAction, this, &MainWindow::nextAction);
    connect(this, &MainWindow::triggerYesNo, this, &MainWindow::YesNo);
    connect(this, &MainWindow::triggerInfo, this, &MainWindow::showInfo);
    connect(this, &MainWindow::triggercolorChoice, this, &MainWindow::colorChoice);
    connect(this, &MainWindow::jetonActionDone, &wait_for_action_jeton, &QEventLoop::quit);
    connect(this, &MainWindow::carteActionDone, &wait_for_action_carte, &QEventLoop::quit);

}

MainWindow::~MainWindow() {
    // Rien
}



void MainWindow::showJetonsBottom() {
    QDialog *jetonsDialog = new QDialog();
    jetonsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");


    QVBoxLayout* verticallayout = new QVBoxLayout();

    QLabel* name = new QLabel();
    name->setText("Jetons de " + QString::fromStdString(Jeu::getJeu().getCurrentPlayer().getName()));
    name->setStyleSheet("QLabel { color: white; }");


    verticallayout->addWidget(name, Qt::AlignCenter);

    QGridLayout* layout = new QGridLayout();
    QWidget *gridWidget = new QWidget();

    gridWidget->setLayout(layout);

    int nb = Jeu::getJeu().getCurrentPlayer().getNbJetons();

    for (int i = 0; i < 16; i++){
        Qt_jeton* j = new Qt_jeton();
        if (i < nb) j->setJeton(Jeu::getJeu().getCurrentPlayer().getJeton()[i]);
        j->setFixedSize(60, 60);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        j->setStyleSheet("border: 1px solid black;");
        layout->addWidget(j, i / 4, i % 4);
        j->updateAppearance();
    }

    // Disable stretching and set fixed size for the layout
    for (int i = 0; i < 4; ++i) {
        layout->setRowStretch(i, 0);
        layout->setColumnStretch(i, 0);
    }

    verticallayout->addWidget(gridWidget);
    jetonsDialog->setLayout(verticallayout);

    jetonsDialog->exec();
}

void MainWindow::showReservedCardsBottom() {
    QDialog *cardsDialog = new QDialog();
    cardsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    QGridLayout* layout = new QGridLayout();

    int nb = Jeu::getJeu().getCurrentPlayer().getNbCartesReservees();
    for (int i = 0; i < nb; i++){
        qDebug() << "CARTES RESERVEES";
        Qt_carte* c = new Qt_carte();
        c->setCard(Jeu::getJeu().getCurrentPlayer().getCartesReserved()[i]);
        c->setFixedSize(75, 105);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        if (getBuyingCard() == true) c->setDisabled(false);
        else c->setDisabled(true);
        c->setIndice(i);
        connect(c, &Qt_carte::carteClicked, &MainWindow::getMainWindow(), &MainWindow::carteClicked);
        // label->setStyleSheet("border: 1px solid black;");
        layout->addWidget(c, i / 4, i % 4);
        c->updateAppearance();
        qDebug() << c->getCard()->getVisuel();

    }

    cardsDialog->setLayout(layout);
    cardsDialog->exec(); // L'afficher
}

void MainWindow::showBoughtCardsBottom() {
    QDialog *cardsDialog = new QDialog();
    cardsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    QGridLayout* layout = new QGridLayout();

    int nb = Jeu::getJeu().getCurrentPlayer().getNbCartesJoaillerie();
    for (int i = 0; i < nb; i++){
        qDebug() << "CARTES ACHETEES";
        Qt_carte* c = new Qt_carte();
        c->setCard(Jeu::getJeu().getCurrentPlayer().getCartesBought()[i]);
        c->setFixedSize(75, 105);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        c->setDisabled(true);
        // label->setStyleSheet("border: 1px solid black;");
        layout->addWidget(c, i / 4, i % 4);
        c->updateAppearance();
        qDebug() << c->getCard()->getVisuel();

    }

    cardsDialog->setLayout(layout);
    cardsDialog->exec(); // L'afficher
}

void MainWindow::showBoughtCardsTop() {
    QDialog *cardsDialog = new QDialog();
    cardsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    QGridLayout* layout = new QGridLayout();

    int nb = Jeu::getJeu().getOpponent().getNbCartesJoaillerie();
    for (int i = 0; i < nb; i++){
        qDebug() << "CARTES ACHETEES";
        Qt_carte* c = new Qt_carte();
        c->setCard(Jeu::getJeu().getOpponent().getCartesBought()[i]);
        c->setFixedSize(75, 105);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        c->setDisabled(true);
        // label->setStyleSheet("border: 1px solid black;");
        layout->addWidget(c, i / 4, i % 4);
        c->updateAppearance();
        qDebug() << c->getCard()->getVisuel();

    }

    cardsDialog->setLayout(layout);
    cardsDialog->exec(); // L'afficher
}

void MainWindow::showJetonsTop() {
    QDialog *jetonsDialog = new QDialog();
    jetonsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");


    QVBoxLayout* verticallayout = new QVBoxLayout();

    QLabel* name = new QLabel();
    name->setText("Jetons de " + QString::fromStdString(Jeu::getJeu().getOpponent().getName()));
    name->setStyleSheet("QLabel { color: white; }");


    verticallayout->addWidget(name, Qt::AlignCenter);

    QGridLayout* layout = new QGridLayout();
    QWidget *gridWidget = new QWidget();

    gridWidget->setLayout(layout);

    int nb = Jeu::getJeu().getOpponent().getNbJetons();

    for (int i = 0; i < 16; i++){
        Qt_jeton* j = new Qt_jeton();
        if (i < nb) j->setJeton(Jeu::getJeu().getOpponent().getJeton()[i]);
        j->setFixedSize(60, 60);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        j->setStyleSheet("border: 1px solid black;");
        layout->addWidget(j, i / 4, i % 4);
        j->updateAppearance();
    }

    // Disable stretching and set fixed size for the layout
    for (int i = 0; i < 4; ++i) {
        layout->setRowStretch(i, 0);
        layout->setColumnStretch(i, 0);
    }

    verticallayout->addWidget(gridWidget);
    jetonsDialog->setLayout(verticallayout);

    jetonsDialog->exec();
}

void MainWindow::showReservedCardsTop() {
    QDialog *cardsDialog = new QDialog();
    cardsDialog->setStyleSheet("background-image: url('../src/background.jpg'); background-position: center;");
    QGridLayout* layout = new QGridLayout();

    int nb = Jeu::getJeu().getOpponent().getNbCartesReservees();
    for (int i = 0; i < nb; i++){
        qDebug() << "CARTES RESERVEES";
        Qt_carte* c = new Qt_carte();
        c->setCard(Jeu::getJeu().getOpponent().getCartesReserved()[i]);
        c->setFixedSize(75, 105);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        c->setDisabled(true);
        c->setIndice(i);
        // label->setStyleSheet("border: 1px solid black;");
        layout->addWidget(c, i / 4, i % 4);
        c->updateAppearance();
        qDebug() << c->getCard()->getVisuel();

    }

    cardsDialog->setLayout(layout);
    cardsDialog->exec(); // L'afficher
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

    if (tirages->getDeck1() != nullptr) tirages->getDeck1()->updateAppearance("../src/Reste_detoure/Pioche_niveau_1.png");
    if (tirages->getDeck2() != nullptr) tirages->getDeck2()->updateAppearance("../src/Reste_detoure/Pioche_niveau_2.png");
    if (tirages->getDeck3() != nullptr) tirages->getDeck3()->updateAppearance("../src/Reste_detoure/Pioche_niveau_3.png");



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

    if (j != nullptr && j->getJeton() != nullptr ) {
        qDebug() << "Jeton cliqué : " << j->getJeton()->getVisuel();
        setIndiceJetonClick(j->getIndice());
    }else{
        setIndiceJetonClick(-1);
    }

    MainWindow::getMainWindow().jetonActionDone();
}


void MainWindow::carteClicked(Qt_carte* c){
    if (c != nullptr) qDebug() << "Carte cliquée : " << c->getIndice() << c->getReservee();
    else qDebug() << "nullptr carte";
    setDerniereCarteClick(c);

    MainWindow::getMainWindow().carteActionDone();
}


void MainWindow::deactivateButtons(){
    // Jetons
    int nbmax = Jeton::getNbMaxJetons();
    for(int i = 0; i < nbmax; i++){
        plateau->getPlateau().getJetons()[i]->setEnabled(false);
    }

    // Tirage 1
    for (int i = 0; i < 5; i++){
        getTirages()->getTier1()[i]->setEnabled(false);
    }

    // Tirage 2
    for (int i = 0; i < 4; i++){
        getTirages()->getTier2()[i]->setEnabled(false);
    }

    // Tirage 3
    for (int i = 0; i < 3; i++){
        getTirages()->getTier3()[i]->setEnabled(false);
    }

    // Tirage cartes royales
    for (int i = 0; i < 4; i++){
        getTirages()->getRoyalCards()[i]->setEnabled(false);
    }

    // Les 3 pioches

    getTirages()->getDeck1()->setEnabled(false);
    getTirages()->getDeck2()->setEnabled(false);
    getTirages()->getDeck3()->setEnabled(false);

    // Déactiver les cartes reservées des 2 joueurs

}

void MainWindow::activateJetons(){
    // Jetons
    int nbmax = Jeton::getNbMaxJetons();
    for(int i = 0; i < nbmax; i++){
        plateau->getPlateau().getJetons()[i]->setEnabled(true);
    }
}

void MainWindow::activateForReserve(){
    // Tirage 1
    for (int i = 0; i < 5; i++){
        getTirages()->getTier1()[i]->setEnabled(true);
    }

    // Tirage 2
    for (int i = 0; i < 4; i++){
        getTirages()->getTier2()[i]->setEnabled(true);
    }

    // Tirage 3
    for (int i = 0; i < 3; i++){
        getTirages()->getTier3()[i]->setEnabled(true);
    }

    // Les 3 pioches

    getTirages()->getDeck1()->setEnabled(true);
    getTirages()->getDeck2()->setEnabled(true);
    getTirages()->getDeck3()->setEnabled(true);
}

void MainWindow::activateForBuy(){
    qDebug() << "ACtiate for buy";
    // Tirage 1
    for (int i = 0; i < 5; i++){
        getTirages()->getTier1()[i]->setEnabled(true);
    }

    // Tirage 2
    for (int i = 0; i < 4; i++){
        getTirages()->getTier2()[i]->setEnabled(true);
    }

    // Tirage 3
    for (int i = 0; i < 3; i++){
        getTirages()->getTier3()[i]->setEnabled(true);
    }

    // Cartes reservées par le joueur en question
}

void MainWindow::updateQuiJoue(){
    quijoue->setText(QString::fromStdString("C'est à " + Jeu::getJeu().getCurrentPlayer().getName()) + " de jouer");
}

void MainWindow::colorChoice(Color *c, int* nb){
    // Créer la fenêtre color choice et recup c et nb
    popupCouleur dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        *c = dialog.getColor();
        *nb = dialog.getNb();
    }
}
