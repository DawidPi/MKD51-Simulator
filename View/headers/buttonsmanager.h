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

signals:
    void buttonsStatusChanged() const;

protected slots:
    void buttonClicked() const;

private: //fields
    static const int m_buttonsNr=8;
    QList<QToolButton*> m_buttons;

};
}

#endif // BUTTONSMANAGER_H
