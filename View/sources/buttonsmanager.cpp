#include "../headers/buttonsmanager.h"
#include <QHBoxLayout>

namespace View{

ButtonsManager::ButtonsManager(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;

    for(int iter=0; iter<m_buttonsNr; iter++)
    {
        QToolButton* newButton = new QToolButton;
        newButton->setText("X" + QString::number(iter));
        newButton->setCheckable(true);
        newButton->setMinimumHeight(40);
        newButton->setMinimumWidth(40);
        m_buttons.append(newButton);

        connect(newButton, SIGNAL(clicked()),this,SLOT(buttonClicked()));

        mainLayout->addWidget(newButton);
    }

    setLayout(mainLayout);
}

QList<int> ButtonsManager::pressedButtons() const
{
    QList<int> buttonsPressed;
    for(int iter=0; iter<m_buttons.size(); iter++)
    {
        if(m_buttons.at(iter)->isChecked())
        {
            buttonsPressed.append(iter);
        }
    }

    return buttonsPressed;
}

void ButtonsManager::buttonClicked() const
{
    emit buttonsStatusChanged();
}

ButtonsManager::~ButtonsManager()
{

}

}
