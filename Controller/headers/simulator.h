#ifndef SIMULATOR
#define SIMULATOR

#include <thread>
#include "../../View/headers/mainview.h"
#include <QMutex>

namespace Controller {

    class Simulator {
    public:
        static Simulator *startSimulator();


        static std::thread* inThread();
    private:
        static void startGui();

        Simulator();

    private:
        static std::thread* m_thread;
        static View::MainView* m_view;
        static QMutex m_mutex;
    };

}

#endif
