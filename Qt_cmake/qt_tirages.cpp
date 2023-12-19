#include "qt_tirages.h"
#include "qt_vue_carte.h"
#include <QVBoxLayout>
#include <QPixmap>

Qt_Tirages::Qt_Tirages(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create a horizontal layout to hold the tier layouts and the spacer
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    // Setting up the images with resizing to fit the label
    const QSize imageSize(75, 105); // Set your desired size here

    deck1 = new Qt_carte();
    deck2 = new Qt_carte();
    deck3 = new Qt_carte();

    royalCardsImage = nullptr; // Keep as nullptr if you don't want an image for royal cards

    // Setup each tier with the decks on the right
    setupTierLayout(tier1Layout, tier1Cards, 5, deck1);
    setupTierLayout(tier2Layout, tier2Cards, 4, deck2);
    setupTierLayout(tier3Layout, tier3Cards, 3, deck3);
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

void Qt_Tirages::setupTierLayout(QHBoxLayout *&layout, std::vector<Qt_carte*> &cards, int cardCount, Qt_carte *deck) {
    layout = new QHBoxLayout();

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < cardCount; ++i) {
        Qt_carte *card = new Qt_carte();
        card->setIndice(i);
        card->setStyleSheet("background: transparent;");
        card->setFixedSize(75, 105);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        cards.push_back(card);
        layout->addWidget(card);
    }

   if (deck != nullptr) {
        deck->setFixedSize(75, 105);  // Same size as cards
        deck->setStyleSheet("background: transparent;");
        layout->addWidget(deck);
    }
}


