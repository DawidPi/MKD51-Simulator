#ifndef SINGLEDIGIT_H
#define SINGLEDIGIT_H

#include <QWidget>
#include <array>
#include <tuple>
#include <QPoint>
#include <QPointF>
#include <QMetaType>

namespace View{

    class SingleDigit : public QWidget
    {
        Q_OBJECT

    public:
        explicit SingleDigit(QWidget *parent = 0,int borderWidth=2,QColor borderColor=Qt::black, QColor segmentColor= Qt::blue ,double scale=1.5);
        enum class Segment {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E,
                     SEG_F, SEG_G, SEG_P, SEG_MAX};

        //getters
        QColor& segmentColor(){return m_segmentColor;}
        QColor& borderColor(){return m_borderColor;}

        //setters
        void setSegmentColor(QColor & segmentColor){m_segmentColor = segmentColor; update();}
        void setBorderColor(QColor & borderColor){m_borderColor = borderColor; update();}

        // U cannot use SEG_MAX as a argument or it throws out of range
        // exception
        void changeState(Segment segment, bool turnedOn);

    protected:
        void paintEvent(QPaintEvent * event);

    private: //DECLARATIONS

        //implementation specific declaration of types for private methods
        //contains additional info about startPoint of segment and its orientation
        typedef std::tuple<QPointF, bool, Segment> ExtSegment;
        enum {POSITION=0, ORIENTATION, SEGMENT};

        enum {isVertical=1, isHorizontal=0};
        static const int ELEMENTS=static_cast<int>(Segment::SEG_MAX);


    private: // Methods
    void drawDigit(QPainter& painter, const QPointF& startPoint, QBrush& brush);
    void drawBorder(QPainter&  painter, const QPointF& startPoint);

    void drawVerticalSegment(QPainter& painter, const QPointF& startPoint, bool filled,
                               QBrush& brush);

    void drawHorizontalSegment(QPainter& painter, const QPointF& startPoint, bool filled,
                              QBrush& brush);

    std::array<ExtSegment, ELEMENTS-1> getElementsToDraw(const QPointF &startPoint);

    private: //fields
        int    m_borderWidth;
        double m_scale;
        QColor m_segmentColor;
        QColor m_borderColor;
        std::array<bool, ELEMENTS> m_states;
    };

}

#endif // SINGLEDIGIT_H
