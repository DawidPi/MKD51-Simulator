#ifndef BUTTONSMANAGER_H
#define BUTTONSMANAGER_H

#include <QWidget>
#include <QToolButton>

namespace View {

    class ButtonsManager : public QWidget
    {
        Q_OBJECT

    public:
        ButtonsManager(QWidget *parent = 0);
        ~ButtonsManager();
        QList<int> pressedButtons() const;
        uint8_t pressedBoolButtons() const;

    signals:
        void buttonsStatusChanged(uint8_t newValue);

    protected slots:
        void buttonUpdated();

    private: //fields
        static const int m_buttonsNr=6;
        QVector<QToolButton*> m_buttons;

    };
}

#endif // BUTTONSMANAGER_H
