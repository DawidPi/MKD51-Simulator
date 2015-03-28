#include "../headers/diodemanager.h"
#include "../headers/diode.h"
#include <QHBoxLayout>

namespace View{

DiodeManager::DiodeManager(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* diodesLayout= new QHBoxLayout;

    for(int iter=0; iter<m_redDiodes; iter++)
    {
        Diode* newDiode= new Diode(0,Qt::red, true,2);
        diodesLayout->addWidget(newDiode);
        m_diodes.append(newDiode);
    }

    for(int iter=0; iter<m_yellowDiodes; iter++)
    {
        Diode* newDiode = new Diode(0,Qt::yellow, true, 2);
        diodesLayout->addWidget(newDiode);
        m_diodes.append(newDiode);
    }

    setLayout(diodesLayout);
}

void DiodeManager::changeDiodesState(int diodeOffset, bool newStatus)
{
    if(diodeOffset >= m_diodes.size())
        throw std::out_of_range("wrong offset in changeDiodesState");

    m_diodes.at(diodeOffset)->setStatus(newStatus);
}

void DiodeManager::changeDiodesState(u_int8_t newDiodesStatus)
{
    const int bitsInByte=8;
    for(int currentOffset=0; currentOffset<bitsInByte; currentOffset++)
    {
        if(newDiodesStatus & 1>>currentOffset)
            changeDiodesState(currentOffset, true);
        else
            changeDiodesState(currentOffset, false);
    }

}

DiodeManager::~DiodeManager()
{

}

}
