#ifndef KEILLISTENER
#define KEILLISTENER

#include <vector>
#include "../../View/headers/singledigit.h"
#include "AGSI_Defs.h"



namespace Model {

    class KeilListener {
    public:
        static bool init(AGSIFUNCS Agsi);
        static void monitorMKD();
        static void port1Listener();
        static void buzzer(DWORD port1);
        static void diodeL8(DWORD port1);
        static void diodes();
        static void keyboard(DWORD port1);
        static void ledDisplay();
        static void peripheralsStart();

    private:
        static const int m_port1Addr=0x90;
        static const int m_buzzerPin=7;
        static const int m_diodeL8Pin=6;

        static const int m_keyboardOutputLSPin=1; //not sure about it
        static const int m_keyboardOutputMSPin=0;

        static const int m_diodesExtAddr=0x8008;
        static const int m_buttonsExtAddr=0x8009;

        static const int m_ledDisplayExtAddr=0x8018;
        static const int m_ledDisplaySelectLS=1;
        static const int m_ledDisplaySelectMS=0;

    private:
        static std::vector<View::SingleDigit::Segment> numberToSegments(BYTE number);
        static void numberToBinDisp(BYTE number);

    };
}

#endif
