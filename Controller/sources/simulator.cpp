#include "../headers/simulator.h"
#include <QApplication>
#include <thread>
#include <QMutex>
#include <functional>

namespace Controller {

Simulator::Simulator(QObject *parent) :
    QObject(parent), m_guiStarted(false)
{
}

Simulator::~Simulator() {
    delete m_guiStartFunctor;
}

Simulator& Simulator::simulator() {
    static Simulator mainSimulator;
    return mainSimulator;
}

void Simulator::startGui() {
    m_guiStartFunctor = new GuiStart;
    std::reference_wrapper<GuiStart> guiFunctor(*m_guiStartFunctor);
    m_thread = new std::thread(guiFunctor);

    mutex.lock();
    while(m_guiStartFunctor->gui() == nullptr);
    View::MainView* gui = m_guiStartFunctor->gui();
    mutex.unlock();

    mutex.lock();
    //inputs
    connect(gui, SIGNAL(buttonsChanged(uint8_t)),
            this,SLOT(buttonsUpdated(uint8_t)),Qt::DirectConnection);
    connect(gui,SIGNAL(keyboardChanged(uint16_t)),
            this, SLOT(keyboardUpdated(uint16_t)),Qt::DirectConnection);
    connect(gui,SIGNAL(potentiometersChanged(int,double)),
            this,SLOT(potentiometerUpdated(int,double)),Qt::DirectConnection);
    connect(gui, SIGNAL(closed()), this, SLOT(guiClosed()), Qt::DirectConnection);

    //outputs
    connect(this,SIGNAL(diodesChange(int,bool)),
            gui,SLOT(diodesUpdate(int,bool)));
    connect(this,SIGNAL(diodesChange(uint8_t)),
            gui,SLOT(diodesUpdate(uint8_t)));
    connect(this,SIGNAL(diodeL8Change(bool)),
            gui,SLOT(diodeL8Update(bool)));
    connect(this,SIGNAL(buzzerChange(bool)),
            gui,SLOT(buzzerUpdate(bool)));
    connect(this,SIGNAL(segmentChange(int,
                                      View::SingleDigit::Segment,bool)),
            gui,SLOT(segmentUpdate(int,View::SingleDigit::Segment,bool)));
    connect(this, SIGNAL(ledDisplayReset()), gui, SLOT(ledDisplayReset()));
    connect(this,SIGNAL(closeGui()), gui, SLOT(close()));
    mutex.unlock();

    m_guiStarted = true;
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
    for(uint8_t mask=0x80, diode=0; mask != 0; mask >>= 1, diode++) {
        if(numberInBinary & mask)
            emit diodesChange(diode, true);
        else
            emit diodesChange(diode,false);
    }
}

void Simulator::stopGui() {
    emit closeGui();
}

bool Simulator::guiStarted() {
    return m_guiStarted;
}

void Simulator::buzzer(bool newState) {
    emit buzzerChange(newState);
}

void Simulator::diodeL8(bool newState) {
    emit diodeL8Change(newState);
}

void Simulator::ledDisplayClean() {
    emit ledDisplayReset();
}

void Simulator::buttons(std::function<void (uint8_t)> callback) {
    m_buttonsCallback = callback;
}

void Simulator::keyboard(std::function<void (uint16_t)> callback) {
    m_keyboardCallback = callback;
}

void Simulator::potentiometers(std::function<void (int, double)> callback) {
    m_potentiometersCallback = callback;
}

void Simulator::buttonsUpdated(uint8_t newValue) {
    if(m_buttonsCallback)
    m_buttonsCallback(newValue);
}

void Simulator::keyboardUpdated(uint16_t newValue) {
    if(m_keyboardCallback)
    m_keyboardCallback(newValue);
}

void Simulator::potentiometerUpdated(int which, double newVoltage) {
    if(m_potentiometersCallback)
    m_potentiometersCallback(which,newVoltage);
}

void Simulator::guiClosed() {
    m_guiStarted=false;
}

}
