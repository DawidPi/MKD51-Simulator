#include "../headers/potmanager.h"
#include <QFormLayout>
#include <QSlider>
#include <QString>

PotManager::PotManager(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout* mainLayout = new QFormLayout;

    for(int iter=0; iter<m_pots; iter++)
    {
        QSlider* newSlider = new QSlider(Qt::Horizontal);
        newSlider->setMaximum(100);
        newSlider->setMinimum(0);
        m_sliders.append(newSlider);
        mainLayout->addRow("Pot: " + QString::number(iter+1),
                           newSlider);
    }

    setLayout(mainLayout);
}

void PotManager::sliderChanged(int newValue)
{
    double lostResistance = m_potMaxVoltage/newValue;

    QSlider* potentiometer = qobject_cast<QSlider*>(sender());
    int offset;

    for(int currSlider=0; currSlider<m_sliders.size(); currSlider++)
    {
        if(m_sliders.at(currSlider) == potentiometer)
        {
            offset=currSlider;
            break;
        }
    }

    emit potResistanceChanged(offset, m_potMaxVoltage-lostResistance);
}

PotManager::~PotManager()
{

}
