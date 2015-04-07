#ifndef GUISTART
#define GUISTART

#include "../../View/headers/mainview.h"
#include "QMutex"

namespace Controller {

    class GuiStart {

    public:
        GuiStart();
        View::MainView* gui();
        void operator()();

    private:
        View::MainView* m_view;
        bool m_started;
    };

}

#endif
