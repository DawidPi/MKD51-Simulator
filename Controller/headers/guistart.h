#ifndef GUISTART
#define GUISTART

#include <QObject>
#include "../../View/headers/mainview.h"
#include "QMutex"

namespace Controller {

    class GuiStart {
    public:
        GuiStart();
        View::MainView* gui();
        void operator()();

    private:
        QMutex mutex;
        View::MainView* m_view;
        bool m_started;
    };

}

#endif
