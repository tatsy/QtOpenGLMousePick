#include <QtWidgets/qapplication.h>
#include "maingui.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainGui gui;
    gui.show();
    return app.exec();
}