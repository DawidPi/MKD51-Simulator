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
        ~Simulator();

        void startGui();
        void stopGui();
        bool guiStarted();
        void ledDisplayClean();
        void segment(int letterOffset, View::SingleDigit::Segment segment,
                     bool newState);
        void diodes(uint8_t numberInBinary);
        void diodes(int diode, bool newState);
        void buttons(std::function<void(uint8_t states)> callback);
        void keyboard(std::function<void(uint16_t states)> callback);
        void buzzer(bool newState);
        void diodeL8(bool newState);
        void potentiometers(std::function<void(int which, double newVoltage)>
                           callback);
        std::thread& thread();



    public slots:
        void buttonsUpdated(uint8_t newValue);
        void keyboardUpdated(uint16_t newValue);
        void potentiometerUpdated(int which, double newVoltage);

    signals:
        void finish();
        void closeGui();
        void ledDisplayReset();
        void segmentChange(int letterOffset, View::SingleDigit::Segment segment,
                           bool newState);
        void diodesChange(int diode, bool newState);
        void diodesChange(uint8_t newValues);
        void buzzerChange(bool newState);
        void diodeL8Change(bool newState);

    private slots:
        void guiClosed();

    private: //methods
        explicit Simulator(QObject* parent=0);

    private: //fields
        std::thread* m_thread;
        QMutex mutex;
        bool m_guiStarted;
        std::function<void(uint8_t)> m_buttonsCallback;
        std::function<void(uint16_t)> m_keyboardCallback;
        std::function<void(int which, double newVoltage)> m_potentiometersCallback;

        GuiStart* m_guiStartFunctor;
    };

}

#endif
