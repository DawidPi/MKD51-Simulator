#ifndef WLED_H
#define WLED_H

#include <QWidget>
#include "singledigit.h"

namespace View{

    class LedManager : public QWidget
    {
        Q_OBJECT

    public:
        LedManager(QWidget *parent = 0);
        ~LedManager();

        void changeSegment(int letterOffset,
                           QVector<SingleDigit::Segment> segments,
                           bool newState);

    private: //fields
        QVector<SingleDigit*> m_digits;
    };

}

#endif // WLED_H
