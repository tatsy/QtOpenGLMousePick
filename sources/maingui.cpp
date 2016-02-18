#include "maingui.h"

MainGui::MainGui(QWidget* parent)
    : QMainWindow(parent)
    , openglWidget(new OpenGLWidget) {
    this->setCentralWidget(openglWidget);
    this->resize(800, 600);
}

MainGui::~MainGui() {
}

