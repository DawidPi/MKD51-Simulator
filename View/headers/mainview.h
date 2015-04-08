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

    public slots:
        void reset();
        void segmentUpdate(int letterOffset, View::SingleDigit::Segment segment,
                           bool newState);
        void diodesUpdate(int diode, bool newState);
        void diodesUpdate(uint8_t newValues);
        void buzzerUpdate(bool newState);
        void diodeL8Update(bool newState);

    signals:
        void keyboardChanged(uint16_t newValues);
        void buttonsChanged(uint8_t newValues);
        void potentiometersChanged(int which, double fillPercent);

    private slots:
        void buttonsUpdated(uint8_t newValues);
        void keyboardUpdated(uint16_t);
        void potentiometersUpdated(int which, double fillPercent);

    private: //methods
        void makeConnections();
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
