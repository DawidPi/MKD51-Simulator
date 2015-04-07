#include "../headers/buzzer.h"

#include <QPainter>
#include <QPen>
#include <QPainterPath>

namespace View {

Buzzer::Buzzer(QWidget *parent,bool defaultOn ,double scale) :
    QWidget(parent)
{
    m_turnedOn=defaultOn;
    m_width *= scale;
    m_height *= scale;

    setFixedSize(m_width+ 0.1*m_width, m_height+0.1*m_height);
}

void Buzzer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    drawSpeaker(painter);
    drawMusic(painter);
}

void Buzzer::changeStatus(bool turnedOn)
{
    m_turnedOn = turnedOn;

    update();
}

void Buzzer::drawSpeaker(QPainter& speakerPainter)
{
    QPointF currentPoint(m_startOffset,m_startOffset);
    QPainterPath speakerPath(currentPoint);

    speakerPath.addRect(m_startOffset,0.25*m_height+m_startOffset,
                        0.25*m_width,0.5*m_height);

    currentPoint += QPointF(0.25*m_width,0.25*m_height);
    speakerPath.moveTo(currentPoint);

    currentPoint += QPointF(0.25*m_width, -0.25*m_height);
    speakerPath.lineTo(currentPoint);

    currentPoint += QPointF(0,m_height);
    speakerPath.lineTo(currentPoint);

    currentPoint += QPointF(-0.25*m_width, -0.25*m_height);
    speakerPath.lineTo(currentPoint);

    currentPoint += QPointF(0, -0.25*m_height);
    speakerPath.moveTo(currentPoint);

    speakerPainter.drawPath(speakerPath);
}

void Buzzer::drawMusic(QPainter& speakerPainter)
{
    if(m_turnedOn)
    {
        QPen arcPen(Qt::red);
        arcPen.setWidth(3);
        speakerPainter.setPen(arcPen);
        speakerPainter.drawArc(0.30*m_width, m_startOffset,
                               0.5*m_width, m_height,
                               -30*16, 60*16);

        arcPen.setColor(Qt::green);
        speakerPainter.setPen(arcPen);
        speakerPainter.drawArc(0.43*m_width, m_startOffset,
                           0.5*m_width, m_height,
                           -42*16, 84*16);

        arcPen.setColor(Qt::magenta);
        speakerPainter.setPen(arcPen);
        speakerPainter.drawArc(0.55*m_width, m_startOffset,
                               0.5*m_width, m_height,
                               -55*16, 110*16);
    }
    else
    {
        QPen crossPen(Qt::red);
        crossPen.setWidth(4);

        speakerPainter.setPen(crossPen);
        speakerPainter.drawLine(m_startOffset, m_startOffset,
                                0.75*m_width-2*m_startOffset,
                                m_height+m_startOffset);

        speakerPainter.drawLine(0.75*m_width-2*m_startOffset, m_startOffset,
                                m_startOffset,
                                m_height+m_startOffset);
    }
}
}
