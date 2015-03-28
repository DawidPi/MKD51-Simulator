#ifndef POTMANAGER_H
#define POTMANAGER_H

#include <QWidget>
#include <QSlider>

namespace View{

    class PotManager : public QWidget
    {
        Q_OBJECT

    public:
        PotManager(QWidget *parent = 0);
        ~PotManager();

    signals:
        void potResistanceChanged(int potOffset, double newResistance);

    private slots:
        void sliderChanged(int newValue);

    private:
        double m_potMaxVoltage=5;
        QVector<QSlider*> m_sliders;
        static const int m_pots=3;
    };
}

#endif // POTMANAGER_H
