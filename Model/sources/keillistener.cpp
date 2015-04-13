#include "../headers/keillistener.h"
#include "../../Controller/headers/simulator.h"
#include "../../AGSI_Defs.h"

static AGSIFUNCS m_agsi;

namespace Model {

bool KeilListener::init(AGSIFUNCS Agsi) {

    m_agsi = Agsi;
    bool successfull = true;

    successfull &= m_agsi.DefineSFR("P1", m_Port1Addr,
                                  AGSIBYTE, 0);

    successfull &= m_agsi.SetWatchOnSFR(m_Port1Addr, port1Listener, AGSIWRITE);
    successfull &= m_agsi.SetWatchOnMemory(m_diodesExtAddr, m_diodesExtAddr+1,
                                         diodes, AGSIWRITE);
    successfull &= m_agsi.SetWatchOnMemory(m_ledDisplayExtAddr, m_ledDisplayExtAddr+1,
                                           ledDisplay, AGSIWRITE);

    return successfull;
}

void KeilListener::port1Listener() {

    DWORD currVal, prevVal;
    DWORD mask=0xFF;

    if(m_agsi.ReadSFR(m_Port1Addr,&currVal, &prevVal, mask)) {
        buzzer(currVal);
        diodeL8(currVal);
        ledDisplay();
    }

}

void KeilListener::buzzer(DWORD port1) {

    DWORD mask = 1<<m_buzzerPin;
    if((port1&mask)==0){
        Controller::Simulator::simulator().buzzer(false);
    }
    else
        Controller::Simulator::simulator().buzzer(true);
}

void KeilListener::diodeL8(DWORD port1) {

    DWORD mask = 1<<m_diodeL8Pin;

    if((port1&mask)==0) {
        Controller::Simulator::simulator().diodeL8(false);
    }
    else
        Controller::Simulator::simulator().diodeL8(true);

}

void KeilListener::diodes() {

    BYTE diodesValue;

    if(m_agsi.ReadMemory(m_diodesExtAddr, 1, &diodesValue)) {
        Controller::Simulator::simulator().diodes(diodesValue);
    }
}

void KeilListener::ledDisplay() {

    DWORD segmentOffsetVal;
    DWORD prevVal;
    DWORD mask = (1<<m_ledDisplaySelectLS) | (1<<m_ledDisplaySelectMS);
    DWORD digitToTurnOn=0;

    if(m_agsi.ReadSFR(m_Port1Addr, &segmentOffsetVal, &prevVal, mask)) {
        digitToTurnOn = segmentOffsetVal;

        BYTE segmentsValue;
        if(m_agsi.ReadMemory(m_ledDisplayExtAddr, 1, &segmentsValue)) {
            Controller::Simulator::simulator().ledDisplayClean();

            auto segments = KeilListener::numberToSegments(segmentsValue);

            for(auto& segment: segments) {
                Controller::Simulator::simulator().segment(
                            digitToTurnOn,segment,true);
            }
        }
    }
}

std::vector<View::SingleDigit::Segment> KeilListener::numberToSegments(BYTE number) {

    std::vector<View::SingleDigit::Segment> segments;

    for(uint8_t mask=0x01, iteration=0; mask!=0; mask<<=1, iteration++) {
        if(number & mask)
            segments.push_back(static_cast<View::SingleDigit::Segment>(iteration));
    }

    return segments;
}

void KeilListener::numberToBinDisp(BYTE number) {

    for(DWORD mask = 0x80; mask!=0; mask>>=1) {
        if(number&mask)
            m_agsi.Message("1");
        else
            m_agsi.Message("0");
    }
    m_agsi.Message("\n");
}

}
