#include "../headers/buttonsmanager.h"
#include <QMetaType>
#include <QHBoxLayout>

namespace View{

ButtonsManager::ButtonsManager(QWidget *parent)
    : QWidget(parent)
{
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<uint8_t>("uint8_t");
    QHBoxLayout* mainLayout = new QHBoxLayout;

    m_buttons.reserve(m_buttonsNr);
    m_buttons.fill(nullptr,m_buttonsNr);

    for(int iter=m_buttonsNr-1; iter>=0; iter--) {

        QToolButton* newButton = new QToolButton;
        newButton->setText("X" + QString::number(iter));
        newButton->setCheckable(true);
        newButton->setMinimumHeight(40);
        newButton->setMinimumWidth(40);
        m_buttons.replace(iter,newButton);

        connect(newButton, SIGNAL(toggled(bool)),this,SLOT(buttonUpdated()));

        mainLayout->addWidget(newButton);
    }

    setLayout(mainLayout);
}


void ButtonsManager::buttonUpdated() {

    uint8_t newVals = pressedBoolButtons();
    emit buttonsStatusChanged(newVals);
}

uint8_t ButtonsManager::pressedBoolButtons() const {

    uint8_t lowLevelValues =0;

    for(int iter=0; iter<m_buttons.size(); iter++)
        if(m_buttons.at(iter)->isChecked())
            lowLevelValues |= 1<<iter;

    return lowLevelValues;
}

QList<int> ButtonsManager::pressedButtons() const {

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

ButtonsManager::~ButtonsManager() {

}

}
