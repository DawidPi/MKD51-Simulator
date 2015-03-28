#ifndef DIODEMANAGER_H
#define DIODEMANAGER_H

#include <QWidget>
#include <inttypes.h>
#include <exception>
#include "diode.h"

namespace View{

class DiodeManager : public QWidget
{
    Q_OBJECT

public:
    DiodeManager(QWidget *parent = 0);
    ~DiodeManager();

public slots:
    void changeDiodesState(int diodeOffset, bool newStatus);
    void changeDiodesState(u_int8_t newDiodesStatus);

private:
    QVector<Diode*> m_diodes;
    static const int m_yellowDiodes=4;
    static const int m_redDiodes=4;

private: //methods
};

}

#endif // DIODEMANAGER_H
