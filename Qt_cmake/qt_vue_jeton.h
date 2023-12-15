#ifndef QT_VUE_JETON_H
#define QT_VUE_JETON_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QString>
#include <QStaticText>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../classes/jetons.h"


class Qt_jeton : public QPushButton {
    Q_OBJECT

private:
    // Jeton m_jeton; // Assuming Jeton is a class representing the jeton data

public:
    // explicit Qt_jeton(const Jeton& j, QWidget *parent = nullptr);
    explicit Qt_jeton(QWidget *parent = nullptr);

    //void updateAppearance(); // Function to update the appearance based on the jeton's state

protected:
    //void paintEvent(QPaintEvent *event) override;

signals:
    //void jetonClicked(const Jeton& j); // Signal to emit when the jeton is clicked

public slots:
    //void onJetonClicked(); // Slot to handle jeton clicks
};


#endif // QT_VUE_JETON_H
