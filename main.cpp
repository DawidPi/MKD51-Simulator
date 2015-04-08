#include <QApplication>
#include "View/headers/mainview.h"
#include <thread>
#include "Controller/headers/simulator.h"
#include <QDebug>

void callback1(int intnum, double dblnum) {
    qDebug() << "callback1: " << intnum << dblnum;
}

void callback2(uint8_t number) {
    qDebug() << "callback2: " << number;
}

void callback3(uint16_t number) {
    qDebug() << "callback3: " << number;
}

int main(int argc, char *argv[])
{
    Controller::Simulator::simulator().startGui();

    Controller::Simulator::simulator().diodes(0x0F);
    Controller::Simulator::simulator().diodeL8(true);
    Controller::Simulator::simulator().segment(0,
                                      View::SingleDigit::Segment::SEG_P,
                                               true);
    Controller::Simulator::simulator().buttons(callback2);
    Controller::Simulator::simulator().keyboard(callback3);
    Controller::Simulator::simulator().potentiometers(callback1);

    Controller::Simulator::simulator().m_thread->join();
    return 0;
}
