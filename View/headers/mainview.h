#ifndef MAINVIEW
#define MAINVIEW

#include <QWidget>
#include "buttonsmanager.h"
#include "diodemanager.h"
#include "keyboardmanager.h"
#include "procview.h"
#include "potmanager.h"
#include "ledmanager.h"
#include "diode.h"
#include "buzzer.h"

namespace View{

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent =0);

private:
    void createPinView(QLayout* layout);
    void createSegmView(QLayout* layout);
    void createDiodes(QLayout* layout);
    void createKeyboard(QLayout* layout);
    void createButtons(QLayout* layout);
    void createPotentiometers(QLayout* layout);
    void createBuzzAndL8Diode(QLayout* layout);
};

}

#endif
