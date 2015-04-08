#ifndef DIODE_H
#define DIODE_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>

namespace View{

    class Diode : public QWidget
    {
        Q_OBJECT
    public:
        explicit Diode(QWidget *parent, QColor color, bool status=false, double scale=1);

        void changeStatus(bool newStatus){m_status = newStatus; update();}

    protected:
        void paintEvent(QPaintEvent *event);

    private: //fields
        bool m_status;
        QColor m_color;
        double m_scale;
    };
}

#endif // DIODE_H
