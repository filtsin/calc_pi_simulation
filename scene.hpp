#pragma once 

#include "simulator.hpp"
#include <QWidget>
#include <vector>

class Scene : public QWidget {
public:
    Scene(QWidget *parent = nullptr);
    void updateScene(const Simulator &simulator);
    void drawVector(bool v);
    void drawCircle(bool v);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Body body1;
    Body body2;
    uint64_t hits;

    // Draw floor and the wall
    void drawEnv();
    void drawBodies();

    void drawHits();

    int padding = 5;

    std::vector<std::pair<double, double>> coords;

    bool needDrawVector = false;
};

