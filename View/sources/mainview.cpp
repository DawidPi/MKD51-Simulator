#include "../headers/mainview.h"

#include <QVBoxLayout>
#include <QGroupBox>

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
    QVBoxLayout* elementsLayout = new QVBoxLayout;
    QGroupBox* box = new QGroupBox(tr("out: Diode P1.6 out: Buzz P1.7"));

    L8Diode* diode = new L8Diode;
    elementsLayout->addWidget(diode);

    box->setLayout(elementsLayout);
    layout->addWidget(box);
}

void MainView::createButtons(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("buttons (addr:0x8008)"));

    ButtonsManager* buttons = new ButtonsManager;
    tmpLayout->addWidget(buttons);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createDiodes(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("diodes (addr:0x8008)"));

    DiodeManager* diodes = new DiodeManager;
    tmpLayout->addWidget(diodes);

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

    WLed* segmDisplay = new WLed;
    tmpLayout->addWidget(segmDisplay);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createKeyboard(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("keyboard (out:P0,1 in:P2,5)"));

    KeyboardManager* keyboard = new KeyboardManager;
    tmpLayout->addWidget(keyboard);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createPotentiometers(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("Potentiometers (addr: 8005-7)"));

    PotManager* potentiometers = new PotManager;
    tmpLayout->addWidget(potentiometers);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}

void MainView::createL8Diode(QLayout* layout)
{
    QHBoxLayout* tmpLayout = new QHBoxLayout;
    QGroupBox* box = new QGroupBox(tr("L8 Diode (out: P1.6)"));

    L8Diode* diode = new L8Diode;
    tmpLayout->addWidget(diode);

    box->setLayout(tmpLayout);
    layout->addWidget(box);
}
