#include "../headers/keillistener.h"
#include "../../Controller/headers/simulator.h"
#include "../../AGSI_Defs.h"

AGSIFUNCS m_agsi;

namespace Model {

bool KeilListener::init(AGSIFUNCS Agsi) {

    m_agsi = Agsi;
    bool successfull = true;

    successfull &= Agsi.DefineSFR("P1", m_Port1Addr,
                                  AGSIBYTE, 0);

    successfull &= Agsi.SetWatchOnSFR(m_Port1Addr, port1Listener, AGSIWRITE);
    successfull &= Agsi.SetWatchOnMemory(m_diodesExtAddr, m_diodesExtAddr+1,
                                         diodes, AGSIWRITE);

    return successfull;
}

void KeilListener::port1Listener() {

    DWORD currVal, prevVal;
    DWORD mask=0xFF;

    if(m_agsi.ReadSFR(m_Port1Addr,&currVal, &prevVal, mask)) {

        numberToBinDisp(static_cast<uint8_t>(currVal));
        buzzer(currVal);
        diodeL8(currVal);
    }

}

void KeilListener::buzzer(DWORD port1) {

    int mask = 1<<m_buzzerPin;
    if((port1&mask)==0){
        Controller::Simulator::simulator().buzzer(true);
    }
    else
        Controller::Simulator::simulator().buzzer(false);
}

void KeilListener::diodeL8(DWORD port1) {

    int mask = 1<<m_diodeL8Pin;

    if((port1&mask)==0) {
        Controller::Simulator::simulator().diodeL8(true);
    }
    else
        Controller::Simulator::simulator().diodeL8(false);

}

void KeilListener::diodes() {

    BYTE diodesValue;

    if(m_agsi.ReadMemory(m_diodesExtAddr, 1, &diodesValue)) {
        numberToBinDisp(diodesValue);
        Controller::Simulator::simulator().diodes(diodesValue);
    }
}

void KeilListener::ledDisplay() {

    DWORD segmentOffsetVal;
    DWORD prevVal;
    DWORD mask= (1<<m_ledDisplaySelectLS) || (1<<m_ledDisplaySelectMS);
    int digitToTurnOn=0;

    if(m_agsi.ReadSFR(m_Port1Addr, &segmentOffsetVal, &prevVal, mask)) {
        if(segmentOffsetVal & (1<<m_ledDisplaySelectMS))
            digitToTurnOn |= 2;
        if(segmentOffsetVal & (1<<m_ledDisplaySelectLS))
            digitToTurnOn++;

        BYTE segmentsValue;
        if(m_agsi.ReadMemory(m_ledDisplayExtAddr, 8, &segmentsValue)) {
            Controller::Simulator::simulator().ledDisplayClean();

            auto segments = KeilListener::numberToSegments(segmentsValue);

            for(const auto& segment: segments) {
                Controller::Simulator::simulator().segment(
                            digitToTurnOn,segment,true);
            }
        }
    }
}

std::vector<View::SingleDigit::Segment> KeilListener::numberToSegments(BYTE number) {

    const int bitsaInBYTE=8;
    std::vector<View::SingleDigit::Segment> segments;

    for(int mask=0x01, iteration=0; mask<bitsaInBYTE; mask<<=1, iteration++) {
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
