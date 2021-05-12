#pragma once

#include "simulator.hpp"
#include <QWidget>

class QBoxLayout;
class QTimer;
class Scene;

class Window : public QWidget {
public:
    Window();
private:
    int n1 = 1;
    int framerate = 60;

    Simulator simulator;
    Scene *scene;

    QBoxLayout *mainLayout;
    QBoxLayout *controlLayout;
    QTimer *timer;

    void createControlBlock();

    void addSpeedControl();
    void addVelocityShowControl();

    void addMassControl();
};
