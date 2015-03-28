#ifndef BUZZER
#define BUZZER

#include <QWidget>

namespace View{

class Buzzer : public QWidget
{
    Q_OBJECT

public:
    explicit Buzzer(QWidget* parent=0,bool defaultOn=true,
                    double scale=1);

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void changeStatus(bool turnedOn);

private:
    bool m_turnedOn;
    int m_startOffset = 5;
    double m_width=80;
    double m_height=80;

    void drawSpeaker(QPainter& speakerPainter);
    void drawMusic(QPainter& speakerPainter);

};

}

#endif
