#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

namespace View {

class KeyboardButton : public QToolButton
{
    Q_OBJECT
public:

    static constexpr int BUTTONS_IN_ROW=4;
    static constexpr int BUTTONS_IN_COL=4;

    enum class Value {BUTT_0 =0, BUTT_1, BUTT_2,BUTT_3,BUTT_4,BUTT_5, BUTT_6,
                BUTT_7, BUTT_8, BUTT_9, BUTT_F1, BUTT_F2, BUTT_F3, BUTT_F4,
                BUTT_ENT, BUTT_MIN};

    explicit KeyboardButton(QWidget *parent, Value buttonValue );
    Value value(){return m_value;}

private: //Methods

private: //Fields
    Value m_value;
};

}

#endif // BUTTON_H
