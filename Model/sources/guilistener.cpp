#include "../headers/guilistener.h"
#include "../../Controller/headers/simulator.h"
#include "../../AGSI_Defs.h"

static AGSIFUNCS m_agsi;

namespace Model {

    bool GuiListener::init(AGSIFUNCS Agsi) {
        m_agsi = Agsi;

        Controller::Simulator::simulator().buttons(buttons);
        Controller::Simulator::simulator().keyboard(keyboard);
        Controller::Simulator::simulator().potentiometers(potentiometers);

        return true;
    }

    void GuiListener::keyboard(uint16_t values) {

    }

    void GuiListener::potentiometers(int which, double newVoltage) {

    }

    void GuiListener::buttons(uint8_t buttons) {
        //m_agsi.WriteMemory()
    }

}
