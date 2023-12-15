#include "qt_cards_main.h"
#include "qt_vue_carte.h"

Qt_cards_main::Qt_cards_main(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    // Additional setup for the layout, if needed
}

void Qt_cards_main::addCard() {
    Qt_carte *newCard = new Qt_carte(this);  // Create a new card
    int cardCount = layout->count();         // Get the current number of cards
    int row = cardCount / 5;                 // Calculate the row for the new card
    int col = cardCount % 5;                 // Calculate the column for the new card
    layout->addWidget(newCard, row, col);    // Add the new card to the layout
}
