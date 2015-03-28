#include "../headers/mainview.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QDebug>

namespace View {

MainView::MainView(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    createPinView(mainLayout);
    createSegmView(mainLayout);
    createDiodes(mainLayout);
    createButtons(mainLayout);
        QHBoxLayout* subLayout = new QHBoxLayout;
        createKeyboard(subLayout);
            QVBoxLayout* potsDiodeBuzz = new QVBoxLayout;
            createPotentiometers(potsDiodeBuzz);
            createBuzzAndL8Diode(potsDiodeBuzz);
            subLayout->addLayout(potsDiodeBuzz);
    mainLayout->addLayout(subLayout);

    setWindowTitle("MKD51 Simulator - iDSP");
    setLayout(mainLayout);
}

void MainView::createBuzzAndL8Diode(QLayout* layout)
{
    QHBoxLayout* elementsLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("out: Buzz P1.7, out: Diode P1.6"));

    m_diodeL8 = new Diode(0,Qt::blue,false,2);
    m_buzzer = new Buzzer;

    elementsLayout->addWidget(m_buzzer);
    elementsLayout->addWidget(m_diodeL8);

    box->setLayout(elementsLayout);
    layout->addWidget(box);
}

void MainView::createButtons(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("buttons (addr:0x8008)"));

    m_buttons = new ButtonsManager;
    tmpLayout->addWidget(m_buttons);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createDiodes(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("diodes (addr:0x8008)"));

    m_diodes = new DiodeManager;
    tmpLayout->addWidget(m_diodes);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createPinView(QLayout* layout)
{
    ProcView* procPins = new ProcView;
    layout->addWidget(procPins);
}

void MainView::createSegmView(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("7 segm display (addr:0x8018)"));

    m_ledDisplay = new LedManager;
    tmpLayout->addWidget(m_ledDisplay);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createKeyboard(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("keyboard (out:P0,1 in:P2,5)"));

    m_keyboard = new KeyboardManager;
    tmpLayout->addWidget(m_keyboard);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createPotentiometers(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("Potentiometers (addr: 8005-7)"));

    m_potentiometers = new PotManager;
    tmpLayout->addWidget(m_potentiometers);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

}
