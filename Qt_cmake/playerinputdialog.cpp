#include "PlayerInputDialog.h"

PlayerInputDialog::PlayerInputDialog(QWidget *parent) : QDialog(parent) {
    // Setup UI elements here
    // Connect submitButton clicked signal to onSubmitClicked slot
}

void PlayerInputDialog::onSubmitClicked() {
    emit inputValuesSubmitted(name1Edit->text(), name2Edit->text(), choix1Edit->text(), choix2Edit->text());
    close();
}
