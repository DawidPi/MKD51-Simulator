#include <QString>
#include "../headers/keyboardbutton.h"

namespace View{

KeyboardButton::KeyboardButton(QWidget *parent, Value buttonValue) :
    QToolButton(parent)
{
    //0 and 9 are lowest and max digits
    if(static_cast<int>(buttonValue) >= 0 and static_cast<int>(buttonValue) <=9)
        setText(QString::number(static_cast<int>(buttonValue)));
    else if(buttonValue == Value::BUTT_MIN)
        setText("-");
    else if (buttonValue == Value::BUTT_ENT)
        setText("Ent");
    else    // here to get text like F1 F2 and so on, that's why I subtract 9
        setText(QString("F") +
                QString::number(static_cast<int>(buttonValue)-9));

    // just to look nice
    setMinimumWidth(40);
    setMinimumHeight(40);
}

}
