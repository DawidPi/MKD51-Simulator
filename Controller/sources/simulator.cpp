#include "../headers/simulator.h"
#include <QApplication>
#include <QMutex>


namespace Controller {

void Simulator::startGui() {
    int zero=0;
    QApplication App(zero, nullptr);
    qApp->setStyleSheet("QGroupBox {"
                        "border: 1px solid gray;"
                        "border-radius: 3px;"
                        "margin-top: 0.5em;"
                        "}"

                        "QGroupBox::title {"
                        "subcontrol-origin: margin;"
                        "left: 10px;"
                        "padding: 0 3px 0 3px;"
                        "}"
                        );


    m_mutex.lock();
    m_view = new View::MainView;
    m_view->show();
    m_mutex.unlock();

    App.exec();
}

Simulator* Simulator::startSimulator() {
    static Simulator singleSimulator;
    m_thread = new std::thread(Simulator::startGui);

    m_mutex.lock(); // connect things later
    m_mutex.unlock();

    return &singleSimulator;
}

std::thread* Simulator::inThread() {
    return m_thread;
}

Simulator::Simulator() {

}

}
