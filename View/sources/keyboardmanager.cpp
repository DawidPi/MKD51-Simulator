#include "../headers/keyboardmanager.h"
#include <QGridLayout>
#include <QMetaType>
#include "../headers/keyboardbutton.h"

namespace View {

KeyboardManager::KeyboardManager(QWidget *parent) :
    QWidget(parent)
{
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<uint8_t>("uint8_t");
    createButtons();
}

void KeyboardManager::createButtons()
{
    QGridLayout* buttonsLayout = new QGridLayout();

    for(int currentRow=0; currentRow<KeyboardButton::BUTTONS_IN_COL; currentRow++)
    {
        for(int currentCol=0; currentCol<KeyboardButton::BUTTONS_IN_ROW; currentCol++)
        {
            KeyboardButton* newButton =
                    new KeyboardButton(this,
                               static_cast<KeyboardButton::Value>(
                                   currentRow*KeyboardButton::BUTTONS_IN_ROW+currentCol));
            m_buttons.append(newButton);
            connect(newButton,SIGNAL(pressed()),this,SLOT(buttonUpdated()));
            connect(newButton,SIGNAL(released()),this,SLOT(buttonUpdated()));
            buttonsLayout->addWidget(newButton,currentRow,currentCol);
        }
    }

    setLayout(buttonsLayout);
}

void KeyboardManager::buttonUpdated()
{
    KeyboardButton* button = qobject_cast<KeyboardButton*>(sender());

    if(button->isDown())
        emit buttonPressed(button->value());
    else
        emit buttonReleased(button->value());

    uint16_t lowLevelValues = getLowLevelKeyboardStatus();
    emit keyboardLowLevelChanged(lowLevelValues);
}

uint16_t KeyboardManager::getLowLevelKeyboardStatus() {
    uint16_t lowLevelValue=0;
    const int bitsInTwoBytes=16;

    for(int iter=0; iter<bitsInTwoBytes; iter++) {
        if(m_buttons.at(iter)->isDown())
            lowLevelValue |= 1<<iter;
    }

    return lowLevelValue;
}

KeyboardManager::~KeyboardManager()
{
}

}
