#include "qt_tirages.h"
#include <QVBoxLayout>

Qt_Tirages::Qt_Tirages(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create a horizontal layout to hold the tier layouts and the spacer
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    // Setup each tier with the decks on the right
    setupTierLayout(tier1Layout, tier1Cards, 5, deckImage1);
    setupTierLayout(tier2Layout, tier2Cards, 4, deckImage2);
    setupTierLayout(tier3Layout, tier3Cards, 3, deckImage3);
    setupTierLayout(royalLayout, royalCards, 4, royalCardsImage);

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

void Qt_Tirages::setupTierLayout(QHBoxLayout *&layout, QVector<QLabel*> &cards, int cardCount, QLabel *&deckImage) {
    layout = new QHBoxLayout();

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0); // Set spacing between widgets to 0

    for (int i = 0; i < cardCount; ++i) {
        QLabel *card = new QLabel(QString("Card %1").arg(i + 1));
        card->setFixedSize(100, 140);  // Width: 100px, Height: 140px based on 1:1.4 aspect ratio
        card->setStyleSheet("border: 1px solid black;");
        cards.push_back(card);
        layout->addWidget(card);
    }

    deckImage = new QLabel("Deck Image");
    deckImage->setFixedSize(100, 140);  // Same size as cards
    layout->addWidget(deckImage);
}
