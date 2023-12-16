#ifndef QT_LABELCLICK_H
#define QT_LABELCLICK_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class Qt_LabelClick : public QLabel {
    Q_OBJECT

public:
    explicit Qt_LabelClick(const QString &text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        : QLabel(text, parent, f) {
        // Ajouter une initialisation si besoin
    }

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
    }
};

#endif // QT_LABELCLICK_H
