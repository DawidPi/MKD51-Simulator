#include <QApplication>
#include "View/headers/mainview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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
    View::MainView view;
    view.show();

    return app.exec();
}
