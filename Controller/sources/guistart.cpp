#include "../headers/guistart.h"
#include <QApplication>

namespace Controller {

GuiStart::GuiStart() : m_started(false)
{
}

void GuiStart::operator ()() {

    int one=1; // argc must be at least one
    char* string[] = {"something", "" }; // simply cheating QApp

    QApplication app(one,string);
    qApp->setStyleSheet("QGroupBox {"
                        "border: 1px solid gray;"
                        "border-radius: 3px;"
                        "margin-top: 0.5em;"
                        "}"

                        "QGroupBox::title {"
                        "subcontrol-origin: margin;"
                        "left: 10px;"
                        "padding: 0 3px 0 3px;"
                        "}"
                        );

    m_view = new View::MainView;
    m_view->show();
    m_started=true;

    app.exec();
}

View::MainView* GuiStart::gui() {
    if(m_started)
        return m_view;
    else
        return nullptr;
}

}
