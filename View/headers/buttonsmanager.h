#ifndef BUTTONSMANAGER_H
#define BUTTONSMANAGER_H

#include <QWidget>
#include <QToolButton>

class ButtonsManager : public QWidget
{
    Q_OBJECT

public:
    ButtonsManager(QWidget *parent = 0);
    ~ButtonsManager();

    QList<int> pressedButtons() const;

protected slots:
    void buttonClicked();

private: //fields
    static const int m_buttonsNr=4;
    QList<QToolButton*> m_buttons;

};

#endif // BUTTONSMANAGER_H
