#ifndef GUILISTENER
#define GUILISTENER
#include "AGSI_Defs.h"
#include <cstdint>

namespace Model {

    class GuiListener {
    public:
        static bool init(AGSIFUNCS Agsi);
        static uint16_t keyboardVal();
        static void keyboard(uint16_t values);
        static void potentiometers(int which, double newVoltage);
        static void buttons(uint8_t buttons);
    private:
        static const int m_buttonsExtAddr=0x8009;
        static const int m_pot1ExtAddr=0x8005;
        static const int m_pot2ExtAddr=0x8006;
        static const int m_pot3ExtAddr=0x8007;
        static const int m_port1Addr=0x90;
    };
}

#endif
