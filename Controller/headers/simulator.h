#ifndef SIMULATOR
#define SIMULATOR

#include <thread>
#include <QObject>
#include "../../View/headers/mainview.h"
#include "guistart.h"
#include <functional>
#include <stdint.h>
#include <QMutex>

namespace Controller {

    class Simulator : public QObject {
        Q_OBJECT
    public:
        static Simulator& simulator();

        void startGui();
        void segment(int letterOffset, View::SingleDigit::Segment segment,
                     bool newState);
        void diodes(uint8_t numberInBinary);
        void diodes(int diode, bool newState);
        void buttons(std::function<void(uint8_t states)> callback);
        void keyboard(std::function<void(uint16_t states)> callback);
        void buzzer(bool newState);
        void diodeL8(bool newState);
        void potentiometers(std::function<void(int which, double fillPercent)>
                           callback);

        std::thread* m_thread; //to be deleted in final state

    public slots:
        void buttonsUpdated(uint8_t newValue);
        void keyboardUpdated(uint16_t newValue);
        void potentiometerUpdated(int which, double fillPercent);

    signals:
        void segmentChange(int letterOffset, View::SingleDigit::Segment segment,
                           bool newState);
        void diodesChange(int diode, bool newState);
        void diodesChange(uint8_t newValues);
        void buzzerChange(bool newState);
        void diodeL8Change(bool newState);

    private: //methods
        explicit Simulator(QObject* parent=0);

    private: //fields
        QMutex mutex;
        std::function<void(uint8_t)> m_buttonsCallback;
        std::function<void(uint16_t)> m_keyboardCallback;
        std::function<void(int which, double fillPercent)> m_potentiometersCallback;

        GuiStart* m_guiStartFunctor;
    };

}

#endif
