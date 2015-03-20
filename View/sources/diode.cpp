#include "../headers/diode.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

Diode::Diode(QWidget *parent, QColor color, bool status, double scale) :
    QWidget(parent)
{
    m_color = color;
    m_status = status;
    m_scale = scale;
    setFixedSize(11*m_scale,11*m_scale);
}

void Diode::paintEvent(QPaintEvent *event)
{
    QPainter diodePainter(this);
    QPen     diodePen(m_color);
    diodePen.setWidth(2);


    diodePainter.setPen(diodePen);

    if(m_status)
    {
        QBrush   diodeBrush(Qt::SolidPattern);
        diodeBrush.setColor(m_color);
        diodePainter.setBrush(diodeBrush);
    }

    diodePainter.drawEllipse(0,0,10*m_scale,10*m_scale);
}
