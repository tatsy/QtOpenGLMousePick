#ifdef _MSC_VER
#pragma once
#endif

#ifndef _MAIN_GUI_H_
#define _MAIN_GUI_H_

#include <QtWidgets/qmainwindow.h>

#include "opengl_widget.h"

class MainGui : public QMainWindow {
    Q_OBJECT

public:
    explicit MainGui(QWidget* parent = nullptr);
    virtual ~MainGui();

private:
    OpenGLWidget* openglWidget;
};

#endif  // _MAIN_GUI_H_
