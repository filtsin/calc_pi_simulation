#include "window.hpp"
#include "scene.hpp"
#include "simulator.hpp"

#include <QBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
#include <QtMath>

Window::Window() 
    : QWidget()
    , simulator(1) {
    mainLayout = new QHBoxLayout(this);

    
    scene = new Scene;
    scene->updateScene(simulator);

    mainLayout->addWidget(scene);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        simulator.step();
        this->scene->updateScene(simulator);
    });

    timer->setTimerType(Qt::PreciseTimer);

    timer->start(1000 / framerate);

    createControlBlock();
}

void Window::createControlBlock() {
    auto widgetControl = new QWidget;
    widgetControl->setMaximumWidth(300);

    controlLayout = new QVBoxLayout(widgetControl);
    controlLayout->setAlignment(Qt::AlignTop);

    addSpeedControl();
    addVelocityShowControl();
    addMassControl();

    mainLayout->addWidget(widgetControl);
}

void Window::addSpeedControl() {
    controlLayout->addWidget(new QLabel("Speed of simulation:"));

    auto slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(1);
    slider->setMaximum(17);

    connect(slider, &QSlider::valueChanged, [this](int v) {
            framerate = 60 * v;
            timer->setInterval(1000 / framerate);
    });

    controlLayout->addWidget(slider);
}

void Window::addVelocityShowControl() {
    auto checkbox = new QCheckBox("Show vector of velocity");

    connect(checkbox, &QCheckBox::stateChanged, [this](int v) {
        this->scene->drawVector(v > 0);
    });

    controlLayout->addWidget(checkbox);
}

void Window::addMassControl() {
    controlLayout->addWidget(new QLabel("N power of mass: 100^N"));

    auto spinBox = new QSpinBox;
    spinBox->setValue(n1);

    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this](int v) {
        simulator = Simulator(qPow(100, v));
    });

    controlLayout->addWidget(spinBox);
}

