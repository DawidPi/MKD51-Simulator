#include "../headers/ledmanager.h"
#include "QGridLayout"
#include <qdebug.h>

namespace View {

LedManager::LedManager(QWidget *parent)
    : QWidget(parent)
{

    QGridLayout * gridLayout = new QGridLayout;

    for(int i=0; i<4; i++){
        SingleDigit *newDigit = new SingleDigit;
        m_digits.append(newDigit);

        gridLayout->addWidget(newDigit,0,i);
    }

    setLayout(gridLayout);
}

void LedManager::changeSegment(int letterOffset,
                         QVector<SingleDigit::Segment> segments,
                         bool newState)
{
    for(const auto& segment : segments)
    {
        m_digits.at(letterOffset)->changeState(segment, newState);
    }
}

LedManager::~LedManager()
{
}

}
