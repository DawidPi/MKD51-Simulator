#include "../headers/singledigit.h"
#include <stdexcept>
#include <tuple>

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QDebug>

namespace View {

SingleDigit::SingleDigit(QWidget *parent,int borderWidth, QColor borderColor, QColor segmentColor,double scale) :
    QWidget(parent)
{
    //base size of this widget
    QSize fixedSize(50,67); //to private section?
    m_scale = scale;
    m_borderWidth = borderWidth;
    m_segmentColor = segmentColor;
    m_borderColor = borderColor;

    fixedSize *= m_scale;
    setFixedSize(fixedSize);

    for(auto & status : m_states){
        status = false;
    }
}

void SingleDigit::changeState(Segment segment, bool turnedOn){
    try{
        m_states.at(static_cast<int>(segment)) = turnedOn;
    }
    catch(const std::out_of_range& exception){
        qDebug() << "out of range in SingleDigit::changeState()";
        throw exception;
    }

    update();
}

void SingleDigit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //border
    QPen borderPen(m_borderColor);
    borderPen.setWidth(m_borderWidth);
    painter.setPen(borderPen);
    drawBorder(painter, QPoint(0,0));

    //segment
    QPen segmentPen(m_segmentColor);
    segmentPen.setWidth(1);

    QBrush brush(Qt::SolidPattern);
    brush.setColor(m_segmentColor);

    // looks nice in this point
    QPoint startPoint(8*m_scale,7*m_scale);
    painter.setPen(segmentPen);

    drawDigit(painter,startPoint, brush);

    // drawing dot

    if(m_states[static_cast<int>(Segment::SEG_P)]==true)
    {
        painter.setBrush(m_segmentColor);
        painter.drawEllipse(38*m_scale,55*m_scale,7*m_scale,7*m_scale);
    }

    QPen dotBorderPen(Qt::black);
    painter.setPen(dotBorderPen);
    painter.drawEllipse(38*m_scale,55*m_scale,7*m_scale,7*m_scale);
    painter.setPen(segmentPen);


}

std::array<SingleDigit::ExtSegment, SingleDigit::ELEMENTS-1> SingleDigit::getElementsToDraw(const QPointF &startPoint)
{
    using namespace std;
    const int segmentLength = 26;

    std::array<SingleDigit::ExtSegment, SingleDigit::ELEMENTS-1> elementsToDraw;
    QPointF segmentPoint(startPoint);

    elementsToDraw[0] = make_tuple(segmentPoint,isHorizontal,Segment::SEG_A);

    segmentPoint += QPointF(segmentLength*m_scale, 0);
    elementsToDraw[1] = make_tuple(segmentPoint, isVertical, Segment::SEG_B);

    segmentPoint += QPointF(0,segmentLength*m_scale);
    elementsToDraw[2] = make_tuple(segmentPoint, isVertical, Segment::SEG_C);

    segmentPoint += QPointF(-segmentLength*m_scale,segmentLength*m_scale);
    elementsToDraw[3] = make_tuple(segmentPoint, isHorizontal, Segment::SEG_D);

    segmentPoint -= QPointF(0,segmentLength*m_scale);
    elementsToDraw[4] = make_tuple(segmentPoint, isVertical, Segment::SEG_E);

    segmentPoint -= QPointF(0,segmentLength*m_scale);
    elementsToDraw[5] = make_tuple(segmentPoint, isVertical, Segment::SEG_F);

    segmentPoint += QPointF(0,segmentLength*m_scale);
    elementsToDraw[6] = make_tuple(segmentPoint, isHorizontal, Segment::SEG_G);


    return elementsToDraw;
}

void SingleDigit::drawDigit(QPainter &painter, const QPointF &startPoint, QBrush &brush)
{
    using namespace std;

auto elementsToDraw = getElementsToDraw(startPoint);

    for(auto & element : elementsToDraw)
    {
        Segment elementSegm = get<SEGMENT>(element);
        bool elementState = m_states.at(static_cast<int>(elementSegm));
        QPointF startPoint = get<POSITION>(element);

        if(get<ORIENTATION>(element) == isVertical)
        {
            drawVerticalSegment(painter, startPoint, elementState, brush);

            if(elementState)
            {
                QPen tmpPen(m_borderColor);
                painter.setPen(tmpPen);
                drawVerticalSegment(painter,startPoint,!elementState,brush);
                tmpPen.setColor(m_segmentColor);
                painter.setPen(tmpPen);
            }
        }
        else
        {
            drawHorizontalSegment(painter, startPoint, elementState, brush);

            if(elementState)
            {
                QPen tmpPen(m_borderColor);
                painter.setPen(tmpPen);
                drawHorizontalSegment(painter,startPoint,!elementState,brush);
                tmpPen.setColor(m_segmentColor);
                painter.setPen(tmpPen);
            }
        }
    }
}

void SingleDigit::drawBorder(QPainter &painter, const QPointF& startPoint)
{
    QPointF m_border[4]{
        QPointF(1,1),
        QPointF(48,1),
        QPointF(48,65),
        QPointF(1,65)
    };

    for(auto & point : m_border)
    {
        point =point*m_scale + startPoint;
    }

    painter.drawPolygon(m_border,sizeof(m_border)/sizeof(QPointF));
}

void SingleDigit::drawVerticalSegment(QPainter &painter, const QPointF& startPoint, bool filled,
                           QBrush &brush)
{
    const std::array<QPointF, 7>baseSegment{
        QPointF(0,0),
        QPointF(3,3),
        QPointF(3,23),
        QPointF(0,26),
        QPointF(-3,23),
        QPointF(-3,3),
        QPointF(0,0)
    };

    QPainterPath segmentPath;

    segmentPath.moveTo(baseSegment.at(0)+startPoint);

    for(auto & point : baseSegment)
        segmentPath.lineTo(point*m_scale + startPoint);

    if(filled)
        painter.fillPath(segmentPath, brush);
    else
        painter.drawPath(segmentPath);
}

void SingleDigit::drawHorizontalSegment(QPainter &painter, const QPointF& startPoint, bool filled,
                          QBrush &brush)
{
    const std::array<QPointF, 7>baseSegment{
        QPointF(0,0),
        QPointF(3,-3),
        QPointF(23,-3),
        QPointF(26,0),
        QPointF(23,3),
        QPointF(3,3),
        QPointF(0,0)
    };

    QPainterPath segmentPath;

    segmentPath.moveTo(baseSegment.at(0)+startPoint);

    for(auto & point : baseSegment)
        segmentPath.lineTo(point*m_scale + startPoint);

    if(filled)
        painter.fillPath(segmentPath,brush);
    else
        painter.drawPath(segmentPath);
}

}
