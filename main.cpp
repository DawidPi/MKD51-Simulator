#include <QApplication>
#include "View/headers/mainview.h"
#include <thread>


void main1(int m_argc, char** m_argv) {
    View::MainView* m_view;
    QApplication App(m_argc, m_argv);
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

    m_view = new View::MainView;
    m_view->show();

    App.exec();
}

int main(int argc, char *argv[])
{
    Controller::Simulator::simulator().startGui();
    Controller::Simulator::simulator().m_thread->join();

    return 0;
}
