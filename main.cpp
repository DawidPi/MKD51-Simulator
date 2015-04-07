#include "Controller/headers/simulator.h"


int main(int argc, char *argv[])
{
    Controller::Simulator::simulator().startGui();
    Controller::Simulator::simulator().m_thread->join();

    return 0;
}
