#pragma once 

#include <cstdint>
#include <utility>
#include <vector>

struct Body {
    double velocity;
    double position;
    uint64_t m;
};

class Simulator {
public:
    Simulator(uint64_t m1);
    
    void step();

    Body getBody1() const noexcept;
    Body getBody2() const noexcept;

    double getRadius() const noexcept;

    uint64_t getHits() const noexcept;

    std::vector<std::pair<double, double>> getCoords() noexcept;

private:
    Body body1, body2;

    double energy;
    double impulse;

    uint64_t hits = 0;

    class Circle {
    public:
        Circle(double energy, double m1, double m2);
    
        std::pair<double, double> getXy(double impulse) const noexcept;

    private:
        double radius;
        double m1, m2;
        double slope;
        double twoenergy;
    } circle;
};

