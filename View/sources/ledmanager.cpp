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
    for(const auto& segment : segments) {

        m_digits.at(letterOffset)->changeState(segment, newState);
    }
}

void LedManager::reset() {
    QVector<SingleDigit::Segment> allSegments;
    allSegments << SingleDigit::Segment::SEG_A
                << SingleDigit::Segment::SEG_B
                << SingleDigit::Segment::SEG_C
                << SingleDigit::Segment::SEG_D
                << SingleDigit::Segment::SEG_E
                << SingleDigit::Segment::SEG_F
                << SingleDigit::Segment::SEG_G
                << SingleDigit::Segment::SEG_P;

    for(int currentOffset; currentOffset<m_digits.size(); currentOffset++) {
        changeSegment(currentOffset,allSegments,false);
    }
}

LedManager::~LedManager() {

}

}
