#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QWidget>
#include "keyboardbutton.h"

namespace View {

    class KeyboardManager : public QWidget
    {
        Q_OBJECT

    public:
        explicit KeyboardManager(QWidget *parent = 0);
        ~KeyboardManager();

    signals:
        void buttonPressed(KeyboardButton::Value Button);
        void buttonReleased(KeyboardButton::Value Button);

    private slots:
        void buttonChanged(bool newValue);

    private: //fields
    QVector<KeyboardButton*> m_buttons;

    private: //Methods
        void createButtons();
    };
}
#endif // KEYBOARDWINDOW_H
