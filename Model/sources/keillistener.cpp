#include "../headers/keillistener.h"
#include "../headers/guilistener.h"
#include "../../Controller/headers/simulator.h"
#include "../../AGSI_Defs.h"

static AGSIFUNCS m_agsi;

namespace Model {

bool KeilListener::init(AGSIFUNCS Agsi) {

    m_agsi = Agsi;
    bool successfull = true;

    successfull &= m_agsi.DefineSFR("P1", m_port1Addr,
                                  AGSIBYTE, 0);

    successfull &= m_agsi.SetWatchOnSFR(m_port1Addr, port1Listener, AGSIWRITE);
    successfull &= m_agsi.SetWatchOnMemory(m_diodesExtAddr, m_diodesExtAddr+1,
                                         diodes, AGSIWRITE);
    successfull &= m_agsi.SetWatchOnMemory(m_ledDisplayExtAddr, m_ledDisplayExtAddr+1,
                                           ledDisplay, AGSIWRITE);

    return successfull;
}

void KeilListener::port1Listener() {

    DWORD Port1Val, prevVal;
    DWORD mask=0xFF;
    static bool initialized=false;

    if(m_agsi.ReadSFR(m_port1Addr,&Port1Val, &prevVal, mask)) {
        if(!initialized) {
            monitorMKD();
            initialized = true;
        }
        else {
            buzzer(Port1Val);
            diodeL8(Port1Val);
            ledDisplay();
            keyboard(Port1Val);
        }
    }
}

void KeilListener::peripheralsStart() {

}

void KeilListener::monitorMKD() {
    uint8_t buttonsInitVal=0xFF;
    m_agsi.WriteSFR(m_port1Addr,0x3C, 0xFF);
    m_agsi.WriteMemory(m_buttonsExtAddr,1,&buttonsInitVal);
}

void KeilListener::keyboard(DWORD port1) {
    uint16_t values=Model::GuiListener::keyboardVal();

    uint8_t firstRow = 0 | ((values & 0x8000) | ((values & 0x800)<<3) |
                               ((values & 0x80)<<6) | ((values&8)<<9));
    uint8_t secondRow =  0 | (((values & 0x4000)<<1) | ((values & 0x400)<<4) |
                              ((values & 0x40)<<7) | ((values&4)<<10));
    uint8_t thirdRow =  0 | (((values & 0x2000)<<2) | ((values & 0x200)<<5) |
                              ((values & 0x20)<<8) | ((values&2)<<11));
    uint8_t fourthRow =  0 | (((values & 0x1000)<<3) | ((values & 0x100)<<6) |
                              ((values & 0x10)<<9) | ((values&1)<<12));
    BYTE result=0;
    DWORD maskedPort = port1 & 0x03;

    // change it for an array
    switch(maskedPort){
    case 0:
        result = firstRow;
        break;
    case 1:
        result = secondRow;
        break;
    case 2:
        result = thirdRow;
        break;
    case 3:
        result=fourthRow;
        break;
    default:
        m_agsi.Message("Ooops executed default in keyboard model\n");
        break;
    }

    result >>=2;

    m_agsi.WriteSFR(m_port1Addr,result,0x3C);
    m_agsi.UpdateWindows();

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

    if(m_agsi.ReadSFR(m_port1Addr, &segmentOffsetVal, &prevVal, mask)) {
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
