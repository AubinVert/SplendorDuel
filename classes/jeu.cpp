#include "jeu.h"
#include <string>
#include "joueur.h"
#include <time.h>



Strategy_player& fromJsonStrategyPLayer(json data){
    if (data["is_ia"] == 1){
        IA *player = new IA;

        player->setNbCouronnes(data["nb_courones"]);
        player->setPoints(data["nb_points"]);
        player->setNbPrivileges(data["nb_privileges"]);
        player->setIa(data["is_ia"]);
        player->setNbJetons(data["nb_jetons"]);
        player->setNbRCards(data["nb_cartes_r"]);
        player->setNbJCards(data["nb_cartes_j"]);
        player->setNbJCardsReserved(data["nb_cartes_j_reservees"]);

        player->setJetons(fromJsonJetons(data["jetons"]));
        player->setJewellryCard(fromJsonJewelryCard(data["cartes_joaillerie_achetees"]));
        player->setJewellryCardReserved(fromJsonJewelryCard(data["cartes_joaiellerie_reservees"]));
        player->setRoyalCard(fromJsonRoyalCard(data["cartes_royale"]));
        player->setPrivileges(fromJsonPrivileges(data["privileges"],data["nb_privileges"]));
        return *player;

    }else{
        Joueur *player = new Joueur(data["nom"]);

        player->setNbCouronnes(data["nb_courones"]);
        player->setPoints(data["nb_points"]);
        player->setNbPrivileges(data["nb_privileges"]);
        player->setIa(data["is_ia"]);
        player->setNbJetons(data["nb_jetons"]);
        player->setNbRCards(data["nb_cartes_r"]);
        player->setNbJCards(data["nb_cartes_j"]);
        player->setNbJCardsReserved(data["nb_cartes_j_reservees"]);

        player->setJetons(fromJsonJetons(data["jetons"]));
        player->setJewellryCard(fromJsonJewelryCard(data["cartes_joaillerie_achetees"]));
        player->setJewellryCardReserved(fromJsonJewelryCard(data["cartes_joaiellerie_reservees"]));
        player->setRoyalCard(fromJsonRoyalCard(data["cartes_royale"]));
        player->setPrivileges(fromJsonPrivileges(data["privileges"],data["nb_privileges"]));

        return *player;
    }


}

// condition pour savoir si le jeu est terminé à chaque tour on check ?


void Jeu::tour_suivant(bool replay) {
    if(qui_joue->victoryConditions()){
        est_termine = true;
    }else{
        Strategy_player* temp = qui_joue;
        qui_joue = adversaire;
        adversaire = temp;
        if (!replay)
            manche++;
    }
    
}

// condition d'arrêt

const bool Jeu::isFinished() {
    return est_termine;
}


Strategy_player& Jeu::get_tour()  {
    return *qui_joue;
}

Jeu::Jeu() {

    // Création sac
    Sac::get_sac();

    // Création jetons. Ils sont mis dans le sac aussi
    int j = 1;


    for (int i = 0; i<4; i++) {
        auto* temp = new Jeton(j++, Color::bleu, "../src/Reste_detoure/Jeton_bleu.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::rouge, "../src/Reste_detoure/Jeton_rouge.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::vert, "../src/Reste_detoure/Jeton_vert.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::blanc, "../src/Reste_detoure/Jeton_blanc.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::noir, "../src/Reste_detoure/Jeton_noir.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<2; i++){
        auto* temp = new Jeton(j++, Color::perle, "../src/Reste_detoure/Jeton_perle.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<3; i++){
        auto* temp = new Jeton(j++, Color::gold, "../src/Reste_detoure/Jeton_or.png");
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }


    // Construction plateau
    Plateau::get_plateau();
    Plateau::get_plateau().remplir_plateau(Sac::get_sac());


    // construceur cartes
    cartes_joiallerie = initCartesJoaillerie();
    cartes_royales = initCartesRoyales();

    // constructeur privileges
    privileges = initPrivileges();

    // pioches :
    p1 = new Pioche(1);
    p2 = new Pioche(2);
    p3 = new Pioche(3);
    p1->InitPioches(p1, p2, p3, cartes_joiallerie);

    //std::cout<<p1->getPioche().size()<<endl;

    // tirages ?

    tirage_1 = new Tirage(1, 5, *p1);
    tirage_2 = new Tirage(2, 4, *p2);
    tirage_3 = new Tirage(3, 3, *p3);
    tirage_1->remplirTirage();
    tirage_2->remplirTirage();
    tirage_3->remplirTirage();

}

Jeu::Jeu(json data){
    //on veut init le jeu avec tout ce dont on a besoin
    est_termine = data["est_termine"];
    cout<<"init j1\n"<<endl;
    qui_joue = &fromJsonStrategyPLayer(data["qui_joue"]);
    manche = data["manche"];
    cout<<"init j2\n"<<endl;
    adversaire = &fromJsonStrategyPLayer(data["adversaire"]);

    // volontaire de pas init
    //cartes_joiallerie = fromJsonJewelryCard(data["cartes_joiallerie"]);
    //jetons = fromJsonJetons(data["jetons"]);
    cartes_royales = fromJsonRoyalCard(data["cartes_royales"]);
    privileges = fromJsonPrivileges(data["privileges"], data["nb_privileges"]);

    cout<<"init pioche1\n"<<endl;
    p1 = &fromJsonPioche(data["pioche1"]);
    cout<<"init pioche2\n"<<endl;
    p2 = &fromJsonPioche(data["pioche2"]);
    cout<<"init pioche3\n"<<endl;
    p3 = &fromJsonPioche(data["pioche3"]);


    tirage_1 = &fromJsonTirage(data["tirage1"], *p1);

    tirage_2 = &fromJsonTirage(data["tirage2"], *p2);

    tirage_3 = &fromJsonTirage(data["tirage3"], *p3);


    fromJsonSac(data["sac"]);

    fromJsonPlateau(data["plateau"]);


}

json Jeu::toJson() const{
    json j;


    j["est_termine"] = est_termine;
    j["manche"] = manche;


    j["pioche1"] = p1->toJson();

    j["pioche2"] = p2->toJson();

    j["pioche3"] = p3->toJson();

    j["tirage1"] = tirage_1->toJson();

    j["tirage2"] = tirage_2->toJson();

    j["tirage3"] = tirage_3->toJson();


    j["qui_joue"] = Jeu::getJeu().getCurrentPlayer().toJson();

    j["adversaire"] = Jeu::getJeu().getOpponent().toJson();


    j["privileges"] = {};
    for (int i = 0; i < privileges.size(); ++i) {
        j["privileges"].push_back(privileges[i]->toJson());
    }
    j["nb_privileges"] = privileges.size();


    j["cartes_royales"] = {};
    for (int i = 0; i < cartes_royales.size(); ++i) {
        j["cartes_royales"].push_back(cartes_royales[i]->toJson());
    }

    j["sac"] = Sac::get_sac().toJson();
    j["plateau"] = Plateau::get_plateau().toJson();



    return j;
}

Jeu::Handler Jeu::handler;

Jeu::~Jeu(){

    // Déstruction jetons
    for (auto  jeton : jetons){
        delete jeton;
    }
    jetons.clear();

    // Déstruction cartes royales
    for (auto cartes_royale : cartes_royales){
        delete cartes_royale;
    }
    cartes_royales.clear();

    // Déstruction cartes joaillerie
    for (auto it : cartes_joiallerie){
        delete it;
    }
    cartes_joiallerie.clear();

    // Déstruction privilèges
    for (auto privilege : privileges){
        delete privilege;
    }
    privileges.clear();

    // Libération pioches
    delete p1;
    delete p2;
    delete p3;

    // Libère les tirages :
    delete tirage_1;
    delete tirage_2;
    delete tirage_3;

    // Déstruction sac
    Sac::libere_sac();

    // Déstruction plateau
    Plateau::libere_plateau();

    // Détruire joueur et ses privilèges et cartes royales
    delete qui_joue;
    delete adversaire;
};

Jeu& Jeu::getJeu(){
    if (handler.instance == nullptr)  handler.instance = new Jeu;
    return *handler.instance;
}
Jeu& Jeu::getJeu(json data){
    if (handler.instance == nullptr)  handler.instance = new Jeu(data);
    return *handler.instance;
}


void Jeu::libereJeu(){
    delete handler.instance;
    handler.instance = nullptr;
}

void Jeu::test() {
    if (handler.instance == nullptr) std::cout << "Test";
}


void Jeu::setPlayers(){
    string choix1;
    cout<<"Le premier joueur est un joueur ou une IA [J/I]? \nChoix: "<<endl;
    cin>>choix1;

    string name1;
    cout << "Veuillez entrer son nom : ";
    cin >> name1;


    string choix2;
    cout<<"Le second joueur est un joueur ou une IA [J/I]? \nChoix: "<<endl;
    cin>>choix2;

    string name2;
    cout << "Veuillez entrer son nom : ";
    cin >> name2;



    srand(static_cast<unsigned>(std::time(nullptr)));
    if(rand()%2==0) { // joueur qui débute la partie est tiré aléatoirement
        if (choix1 == "J") {
            qui_joue = new Joueur(name1);
            qui_joue->setIa(0);
        } else {
            qui_joue = new IA(name1);
            qui_joue->setIa(1);
        }

        if (choix2 == "J") {
            adversaire = new Joueur(name2);
            adversaire->setIa(0);

        } else {
            adversaire = new IA(name2);
            adversaire->setIa(1);

        }
    }else{
        if (choix1 == "J") {
            adversaire = new Joueur(name1);
            adversaire->setIa(0);

        } else {
            adversaire = new IA(name1);
            adversaire->setIa(1);

        }

        if (choix2 == "J") {
            qui_joue = new Joueur(name2);
            qui_joue->setIa(0);

        } else {
            qui_joue = new IA(name2);
            qui_joue->setIa(1);

        }
    }
    adversaire->obtainPrivilege(); // Le joueur qui ne commence pas démarre avec un privilège
}


void Jeu::printCarteRoyale(){
    int i = 0;
    for(auto c: cartes_royales){
        cout<<"Indice : "<<i++<<", "<<*c<<endl;
    }
}
