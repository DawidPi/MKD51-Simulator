#include <QHBoxLayout>
#include "../headers/l8diode.h"
#include "../headers/diode.h"

L8Diode::L8Diode(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    m_diode = new Diode(0,Qt::blue,false,2);

    mainLayout->addWidget(m_diode);
    setLayout(mainLayout);
}

void L8Diode::changeDiode(bool newState)
{
    m_diode->setStatus(newState);
}
