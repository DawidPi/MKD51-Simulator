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

        Diode&              singleDiode(){return *m_diodeL8;}
        Buzzer&             buzzer(){return *m_buzzer;}
        DiodeManager&       diodes(){return *m_diodes;}
        LedManager&         ledDisplay(){return *m_ledDisplay;}
        ButtonsManager&     buttons(){return *m_buttons;}
        KeyboardManager&    keyboard(){return *m_keyboard;}
        PotManager&         potentiometers(){return *m_potentiometers;}


    private: //methods
        void createPinView(QLayout* layout);
        void createSegmView(QLayout* layout);
        void createDiodes(QLayout* layout);
        void createKeyboard(QLayout* layout);
        void createButtons(QLayout* layout);
        void createPotentiometers(QLayout* layout);
        void createBuzzAndL8Diode(QLayout* layout);

    private: //fields
        //outputs
        Diode * m_diodeL8;
        Buzzer * m_buzzer;
        DiodeManager * m_diodes;
        LedManager *   m_ledDisplay;

        //inputs
        ButtonsManager*  m_buttons;
        KeyboardManager* m_keyboard;
        PotManager*     m_potentiometers;

    };

}

#endif
