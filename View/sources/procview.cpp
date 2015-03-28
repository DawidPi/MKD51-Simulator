#include "../headers/procview.h"
#include <QPainter>
#include <QFont>

//needs some refactoring

namespace View {

ProcView::ProcView(QWidget *parent) :
    QWidget(parent)
{
    m_elementaryLength = m_width/(m_noPinRatio*m_numberOfPins+1
                                       + m_pinRatio*m_numberOfPins);

    m_startPointW = m_borderWidth;
    m_startPointH = m_elementaryLength*m_noPinRatio+ m_borderWidth;

    setFixedSize(m_width+m_startPointW+m_borderWidth,
                 m_height+2*m_startPointH+m_borderWidth);
}

void ProcView::paintEvent(QPaintEvent *event){
    QPainter procPainter(this);
    QPen     procPen(Qt::black);

    procPen.setWidth(m_borderWidth);
    procPainter.setPen(procPen);

    QRect rect(m_startPointW,m_startPointH,m_width,m_height);
    QTextOption textOpts;
    QFont textFont = procPainter.font();

    textFont.setPointSize(procPainter.font().pointSize()*m_fontScale);
    procPainter.setFont(textFont);
    textOpts.setAlignment(Qt::AlignCenter);

    procPainter.drawRect(rect);
    procPainter.drawText(rect,"80C31",textOpts);
    drawPins(QPointF(m_startPointW, m_startPointH), procPainter);
}

void ProcView::drawPins(const QPointF& startPoint, QPainter& painter)
{
    /* I guess it needs some comment in here of what I'm doing
       so,the pin will be like:

       m_noPinRatio  :  m_pinRatio  : m_noPinRatio
                   _______________
      ____________|               |________ m_noPinRatio

      that's why I need to divide length of 8031 by m_noPinRatio*m_numberOfPins+1 +
      pinRatio*m_numberOfPins then I can draw pin in proper ratio
    */


    QPointF currentPoint = startPoint;
    QPointF nextPoint;


    //draw upper pins

    QPainterPath pinPath(currentPoint);
    nextPoint = currentPoint+QPointF(m_elementaryLength*m_noPinRatio,0);
    pinPath.moveTo(nextPoint);
    currentPoint = nextPoint;

    for(int currentElementIdx=0; currentElementIdx<m_numberOfPins;
        currentElementIdx++)
    {
          addPinToPath(pinPath, currentPoint, true);
    }

    // draw lower pins
    currentPoint = startPoint - QPoint(0,-m_height);
    pinPath.moveTo(currentPoint);

    nextPoint = currentPoint+QPointF(m_elementaryLength*m_noPinRatio,0);
    pinPath.moveTo(nextPoint);
    currentPoint = nextPoint;

    for(int currentElementIdx=0; currentElementIdx<m_numberOfPins;
        currentElementIdx++)
    {
        addPinToPath(pinPath, currentPoint, false);

    }

    painter.drawPath(pinPath);
}

void ProcView::addPinToPath(QPainterPath& pinPath, QPointF& currentPoint,
                   bool upper)
{
    QPointF nextPoint;

    int upLow=1;
    if(!upper)
        upLow=-1;

    nextPoint = currentPoint + QPointF(0, -upLow*m_elementaryLength*m_noPinRatio);
    pinPath.lineTo(nextPoint);
    currentPoint = nextPoint;

    nextPoint = currentPoint + QPointF(m_elementaryLength*m_pinRatio,0);
    pinPath.lineTo(nextPoint);
    currentPoint = nextPoint;

    nextPoint = currentPoint + QPointF(0, upLow*m_elementaryLength*m_noPinRatio);
    pinPath.lineTo(nextPoint);
    currentPoint = nextPoint;

    nextPoint = currentPoint + QPointF(m_elementaryLength*m_noPinRatio,0);
    pinPath.moveTo(nextPoint);
    currentPoint = nextPoint;
}

}
