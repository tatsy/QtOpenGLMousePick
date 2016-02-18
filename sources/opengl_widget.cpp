#include "opengl_widget.h"

#include <gl/GLU.h>

#include <QtGui/qevent.h>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) {
}

OpenGLWidget::~OpenGLWidget() {
}

void OpenGLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int renderMode;
    glGetIntegerv(GL_RENDER_MODE, &renderMode);

    if (renderMode != GL_SELECT) {
        // Matrix setting
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        const float aspect = static_cast<float>(width()) / height();
        gluPerspective(45.0, aspect, 1.0, 1000.0);    
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    drawObjects();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* ev) {
    // Selection buffer
    std::fill(selectBuffer.begin(), selectBuffer.end(), 0);
    glSelectBuffer(selectBufferSize, &selectBuffer[0]);

    // Draw for selection buffer
    glRenderMode(GL_SELECT);

    // Matrix setting
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluPickMatrix(ev->x(), height() - ev->y(), 5, 5, viewport);
    const float aspect = static_cast<float>(viewport[2]) / viewport[3];
    gluPerspective(45.0, aspect, 1.0, 1000.0);

    // Draw
    paintGL();

    // Reset matrix setting
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Revert render mode
    int hits = glRenderMode(GL_RENDER);

    // Show selection
    printf("%d hits\n", hits);
    if (hits > 0) {
        int id = 0;
        for (int i = 0; i < hits; i++) {
            printf("Level: %u\n", selectBuffer[id + 0]);
            printf("  Min: %f\n", (double)selectBuffer[id + 1] / UINT_MAX);
            printf("  Max: %f\n", (double)selectBuffer[id + 2] / UINT_MAX);
            printf("   ID: %u\n", selectBuffer[id + 3]);
            id += 4;
        }
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* ev) {
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* ev) {
}

void OpenGLWidget::drawObjects() const {
    // Prepare for selection
    glInitNames();
    glPushName(0);

    // First
    glColor3f(1.0f, 0.0f, 0.0f);
    glLoadName(1);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 0.0f);
    glEnd();

    // Second
    glColor3f(0.0f, 1.0f, 0.0f);
    glLoadName(2);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glEnd();
}