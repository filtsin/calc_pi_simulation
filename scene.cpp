#include "scene.hpp"
#include <QDebug>
#include <QPainter>

Scene::Scene(QWidget *parent)
    : QWidget(parent) { }

void Scene::paintEvent(QPaintEvent *event) {
    drawEnv();
    drawBodies();
    drawHits();
}

void Scene::drawEnv() {
    QPainter painter(this);

    int xstart = padding;
    int ystart = height() - padding;
    
    auto floor = QLine(xstart, ystart, width(), ystart);
    auto wall = QLine(xstart, ystart, padding, 0);

    painter.drawLine(floor);
    painter.drawLine(wall);

    int delta = 10;

    int nx = width() / delta;
    int ny = height() / delta;

    for (int i = 0; i < nx; ++i) {
        auto line = QLine(i * delta, ystart, i * delta - padding, height());
        painter.drawLine(line);
    }

    for (int i = 0; i < ny; ++i) {
        auto line = QLine(padding, i * delta, 0, i * delta + padding);
        painter.drawLine(line);
    }
}

void Scene::drawBodies() {
    // width and height of bodies
    double w1 = 150.0;
    double w2 = 100.0;

    double h1 = 150.0;
    double h2 = 100.0;

    // shift for drawing
    // becase for second body in simulator we have right bottom point
    // and we check this point for 0 (wall)
    // so we draw two bodies with shift
    double shift = w2 + padding;

    qDebug() << body1.position << body2.position;

    auto square1 = QRectF(body1.position + padding + shift, height() - h1 - padding,
                          w1, h1);


    auto square2 = QRectF(body2.position - w2 + padding + shift, height() - h2 - padding,
                          w2, h2);

    QPainter painter(this);
    painter.drawRect(square1);
    painter.drawRect(square2);

    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);

    QString m1 = QString::number(body1.m);
    QString m2 = QString::number(body2.m);

    QString v1 = QString::number(body1.velocity, 'f', 2);
    QString v2 = QString::number(body2.velocity, 'f', 2);

    QString body1Info = QString("%1kg\n%2").arg(m1, v1);
    QString body2Info = QString("%1kg\n%2").arg(m2, v2);

    painter.drawText(square1, Qt::AlignCenter, body1Info);
    painter.drawText(square2, Qt::AlignCenter, body2Info);

    if (needDrawVector) {
        double v1 = body1.velocity;
        double v2 = body2.velocity;

        double len1 = v1 * 80;
        double len2 = v2 * 80;

        auto square1Center = square1.center();
        auto line1 = QLineF(square1Center, { square1Center.x() + len1, square1Center.y() });

        auto square2Center = square2.center();
        auto line2 = QLineF(square2Center, { square2Center.x() + len2, square2Center.y() });

        auto pen = painter.pen();
        pen.setWidth(3);
        pen.setCosmetic(true);
        painter.setPen(pen);

        painter.drawLine(line1);
        painter.drawLine(line2);

        double arrowLen = 5.0;

        auto arrow1 = QPointF { arrowLen, -arrowLen };
        auto arrow2 = QPointF { arrowLen, arrowLen };

        int line1neg = len1 < 0 ? 1 : -1;
        int line2neg = len2 < 0 ? 1 : -1;

        painter.drawLine(line1.p2(), line1.p2() + arrow1 * line1neg);
        painter.drawLine(line1.p2(), line1.p2() + arrow2 * line1neg);

        painter.drawLine(line2.p2(), line2.p2() + arrow1 * line2neg);
        painter.drawLine(line2.p2(), line2.p2() + arrow2 * line2neg);
    }
}

void Scene::drawHits() {
    QPainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);

    auto infoRect = QRect(padding * 2, padding * 2, 500, 500);
    painter.drawText(infoRect, QString("Hits: %1").arg(hits));
}


void Scene::updateScene(const Simulator &simulator) {
    body1 = simulator.getBody1();
    body2 = simulator.getBody2();
    hits = simulator.getHits();
    repaint();
}

void Scene::drawVector(bool v) {
    needDrawVector = v;
}

