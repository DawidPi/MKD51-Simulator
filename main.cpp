#include "Controller/headers/simulator.h"


int main(int argc, char *argv[])
{
    Controller::Simulator::startSimulator();
    std::thread* simuThread = Controller::Simulator::inThread();

    simuThread->join();

    return 0;
}
