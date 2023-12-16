#include "qt_tirages.h"
#include "qt_vue_carte.h"
#include <QVBoxLayout>

Qt_Tirages::Qt_Tirages(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create a horizontal layout to hold the tier layouts and the spacer
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    // Setting up the images with resizing to fit the label
    const QSize imageSize(100, 140); // Set your desired size here

    // Setting up the deck images with Qt_carte
    deckImage1 = new Qt_carte(this);
    deckImage1->setImage("../src/Reste_detoure/Pioche_niveau_1.png");
    deckImage2 = new Qt_carte(this);
    deckImage2->setImage("../src/Reste_detoure/Pioche_niveau_2.png");
    deckImage3 = new Qt_carte(this);
    deckImage3->setImage("../src/Reste_detoure/Pioche_niveau_3.png");
    royalCardsImage = nullptr; // Keep as nullptr if you don't want an image for royal cards

    // Setup each tier with the decks on the right
    setupTierLayout(tier1Layout, tier1Cards, 5, deckImage1);
    setupTierLayout(tier2Layout, tier2Cards, 4, deckImage2);
    setupTierLayout(tier3Layout, tier3Cards, 3, deckImage3);
    setupTierLayout(royalLayout, royalCards, 4, royalCardsImage); // Modified line

    // Add the tier layouts to the left side of the horizontal layout
    verticalLayout->addLayout(royalLayout);
    verticalLayout->addLayout(tier1Layout);
    verticalLayout->addLayout(tier2Layout);
    verticalLayout->addLayout(tier3Layout);

    // Add a spacer item to justify the cards to the right
    verticalLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Add the horizontal layout to the main layout
    mainLayout->addLayout(verticalLayout);
}

void Qt_Tirages::setupTierLayout(QHBoxLayout *&layout, QVector<Qt_carte*> &cards, int cardCount, Qt_carte *deckImage) {
    layout = new QHBoxLayout();

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < cardCount; ++i) {
        Qt_carte *card = new Qt_carte();
        card->setFixedSize(100, 140);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        cards.push_back(card);
        layout->addWidget(card);
    }

    if (deckImage != nullptr) {
        deckImage->setFixedSize(100, 140);  // Same size as cards
        layout->addWidget(deckImage);
    }
}


