#include "../headers/keyboardmanager.h"
#include <QGridLayout>
#include "../headers/keyboardbutton.h"

namespace View {

KeyboardManager::KeyboardManager(QWidget *parent) :
    QWidget(parent)
{
    createButtons();
    setMinimumWidth(225);//just to see all the title
    setWindowTitle(tr("MKD51 Keyboard"));
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
            connect(newButton,SIGNAL(clicked(bool)),this,SLOT(buttonChanged(bool)));
            buttonsLayout->addWidget(newButton,currentRow,currentCol);
        }
    }

    setLayout(buttonsLayout);
}

void KeyboardManager::buttonChanged(bool newValue)
{
    KeyboardButton* button = qobject_cast<KeyboardButton*>(sender());

    if(newValue)
        emit buttonPressed(button->value());
    else
        emit buttonPressed(button->value());
}

KeyboardManager::~KeyboardManager()
{
}

}
