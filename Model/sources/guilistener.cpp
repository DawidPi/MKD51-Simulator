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
        m_agsi.Message("Keyboard callback launched\n");
        m_agsi.UpdateWindows();
    }

    void GuiListener::potentiometers(int which, double newVoltage) {
        m_agsi.Message("potentiometer callback launched\n");
        m_agsi.UpdateWindows();
    }

    void GuiListener::buttons(uint8_t buttons) {
        buttons |= 0xF0;
        m_agsi.WriteMemory(m_buttonsExtAddr, 1, &buttons);
        m_agsi.UpdateWindows();
    }

}
