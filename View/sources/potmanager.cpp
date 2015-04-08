#include "../headers/potmanager.h"
#include <QFormLayout>
#include <QSlider>
#include <QString>

namespace View {

PotManager::PotManager(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout* mainLayout = new QFormLayout;

    for(int iter=0; iter<m_pots; iter++)
    {
        QSlider* newSlider = new QSlider(Qt::Horizontal);
        newSlider->setMaximum(m_slidersMaxValue);
        newSlider->setMinimum(0);
        m_sliders.append(newSlider);
        mainLayout->addRow("Pot: " + QString::number(iter+1),
                           newSlider);
        connect(newSlider,SIGNAL(sliderMoved(int)), this,SLOT(sliderUpdated(int)));
    }

    setLayout(mainLayout);
}

void PotManager::sliderUpdated(int newValue)
{
    double lostVolategeOnResistance = m_potMaxVoltage*newValue/m_slidersMaxValue;

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

    emit potResistanceChanged(offset, m_potMaxVoltage-lostVolategeOnResistance);
}

PotManager::~PotManager()
{

}

}
