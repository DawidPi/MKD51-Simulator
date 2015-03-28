#ifndef PROCVIEW_H
#define PROCVIEW_H

#include <QWidget>

namespace View{

class ProcView : public QWidget
{
    Q_OBJECT
public:
    explicit ProcView(QWidget *parent = 0);
    //ProcView(QWidget *parent = 0, )

protected:
    void paintEvent(QPaintEvent* event);

signals:

public slots:

private: //fields
    // not const static in case you want to scale it
    int m_startPointW;
    int m_startPointH;
    int m_width = 475;
    int m_height = 100;
    int m_numberOfPins=20;
    double m_elementaryLength;
    double m_pinRatio=3;
    double m_noPinRatio=1.5;
    int m_borderWidth=3;
    double m_fontScale=2;

private: // methods
    void drawPins(const QPointF &startPoint, QPainter& painter);
    void addPinToPath(QPainterPath& pinPath, QPointF& currentPoint,
                       bool upper);

};
}

#endif // PROCVIEW_H
