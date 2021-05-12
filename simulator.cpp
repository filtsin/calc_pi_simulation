#include "simulator.hpp"

#include <QtMath>
#include <QtDebug>

Simulator::Simulator(uint64_t m1)
    : body1 { -1.0, 1200.0, m1 }
    , body2 { 0.0, 1000.0, 1 }
    , energy(static_cast<double>(m1) * qPow(body1.velocity, 2) / 2)
    , impulse(body1.velocity * m1)
    , circle(energy, body1.m, body2.m) { }

void Simulator::step() {
    // Hack for stop calculating if square behind the screen
    if (body1.position >= 200000) {
        return;
    }

    double t = 1.0;

    if (body2.velocity > 10.0 || body2.velocity < -10.0) {
        t = 0.01;
    }

    double s1 = body1.velocity * t;
    double s2 = body2.velocity * 1.0;


    // Movement
    body1.position += s1;
    body2.position += s2;

    if (body1.position < 0) {
        body1.position = 0;
    }

    // Check collision 2nd body with the wall
    if (body2.position <= 0) {
        body2.position = 0;
        body2.velocity = -body2.velocity;
        impulse = body2.m * body2.velocity + body1.m * body1.velocity;
        hits += 1;
    }
    // Check collision between 1st and 2nd bodies
    else if (body2.position >= body1.position) {
        body2.position = body1.position;
        auto [v1, v2] = circle.getXy(impulse);
        body2.velocity = v2 / qSqrt(body2.m);
        body1.velocity = v1 / qSqrt(body1.m);
        hits += 1;
    }
}

Body Simulator::getBody1() const noexcept { return body1; }
Body Simulator::getBody2() const noexcept { return body2; }

double Simulator::getRadius() const noexcept { return energy * 2; }

uint64_t Simulator::getHits() const noexcept { return hits; }

Simulator::Circle::Circle(double energy, double m1, double m2)
    : radius(qSqrt(2 * energy))
    , m1(m1)
    , m2(m2)
    , slope(m1 / m2)
    , twoenergy(energy * 2)
{

}

std::pair<double, double> Simulator::Circle::getXy(double impulse) const noexcept { 
    // We have circle on (0, 0) with r = sqrt(2 * energy)
    // Now we should found intersection between line
    // slope * x + y = impulse
    // (x0, y0) - closest point from center of circle to line
    // d = distance between (x0, y0) to our points
    // dpow = d^2
    // At this point we can find two points, but one point
    // for our task we already know
    double x0 = - qSqrt(slope) * (-impulse) / (slope + 1);
    double y0 = impulse / (slope + 1);

    double dpow = twoenergy - qPow(impulse, 2) / (slope + 1);

    double sqr = qSqrt(dpow / (slope + 1));

    double x = x0 + sqr;
    double y = y0 - qSqrt(slope) * sqr;

    return std::make_pair(x, y);
}
