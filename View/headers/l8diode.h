#ifndef L8DIODE
#define L8DIODE

#include <QWidget>
#include "diode.h"

class L8Diode : public QWidget
{
    Q_OBJECT

public slots:
    void changeDiode(bool newState);

public:
    explicit L8Diode(QWidget* parent=0);
private:
    Diode* m_diode;
};

#endif
