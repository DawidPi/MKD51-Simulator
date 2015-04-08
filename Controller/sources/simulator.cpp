#include "../headers/simulator.h"
#include <QDebug>
#include <QApplication>
#include <thread>
#include <QMutex>


namespace Controller {

Simulator::Simulator(QObject *parent) :
    QObject(parent)
{
}

Simulator& Simulator::simulator() {
    static Simulator mainSimulator;
    return mainSimulator;
}

void Simulator::startGui() {

    qDebug() << "in startGui";
    m_thread = new std::thread(m_guiStartFunctor);
    qDebug() << "after creating thread";

    /*
    QObject::connect();
    */
}

void Simulator::segment(int letterOffset,
                        View::SingleDigit::Segment segment,
                        bool newState)
{
    emit segmentChange(letterOffset, segment, newState);
}

void Simulator::diodes(int diode, bool newState) {
    emit diodesChange(diode, newState);
}

void Simulator::diodes(uint8_t numberInBinary) {
    for(uint8_t mask=0x01, diode=1; mask != 0; mask <<= 1, diode++) {
        if(numberInBinary & mask)
            emit diodesChange(diode, true);
        else
            emit diodesChange(diode,false);
    }
}

void Simulator::buzzer(bool newState) {
    emit buzzerChange(newState);
}

void Simulator::diodeL8(bool newState) {
    emit diodeL8Change(newState);
}

void Simulator::buttons(std::function<void (uint8_t)> &callback) {
    m_buttonsCallback = callback;
}

void Simulator::keyboard(std::function<void (uint16_t)> callback) {
    m_keyboardCallback = callback;
}

void Simulator::potentiometers(std::function<void (int, double)> callback) {
    m_potentiometersCallback = callback;
}

void Simulator::buttonsUpdate(uint8_t newValue) {
    m_buttonsCallback(newValue);
}

void Simulator::keyboardUpdate(uint16_t newValue) {
    m_keyboardCallback(newValue);
}

void Simulator::potentiometerUpdate(int which, double fillPercent) {
    m_potentiometersCallback(which,fillPercent);
}

}
