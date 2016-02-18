#ifdef _MSC_VER
#pragma once
#endif

#ifndef _OPENGL_WIDGET_H_
#define _OPENGL_WIDGET_H_

#include <vector>

#include <QtWidgets/qopenglwidget.h>

class OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget* parent = nullptr);
    virtual ~OpenGLWidget();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void mousePressEvent(QMouseEvent* ev) override;
    virtual void mouseMoveEvent(QMouseEvent* ev) override;
    virtual void mouseReleaseEvent(QMouseEvent* ev) override;

private:
    void drawObjects() const;

    using uint = unsigned int;
    static const int selectBufferSize = 100;
    std::vector<uint> selectBuffer = std::vector<uint>(selectBufferSize);


};  // class OpenGLWidget

#endif  // _OPENGL_WIDGET_H_