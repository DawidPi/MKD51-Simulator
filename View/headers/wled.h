#ifndef WLED_H
#define WLED_H

#include <QWidget>
#include "singledigit.h"

class WLed : public QWidget
{
    Q_OBJECT

public:
    WLed(QWidget *parent = 0);
    ~WLed();

public slots:
    void changeSegment(int letterOffset,
                       QVector<SingleDigit::Segment> segments,
                       bool newState);

private: //fields
    QVector<SingleDigit*> m_digits;
};

#endif // WLED_H
