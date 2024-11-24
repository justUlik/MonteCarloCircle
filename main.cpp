#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <vector>
#include <iomanip>

struct Circle {
    double x, y, r;
};

bool IsInCircle(double px, double py, const Circle& circle) {
    return (px - circle.x) * (px - circle.x) + (py - circle.y) * (py - circle.y) <= circle.r * circle.r;
}

long double MonteCarloIntersection(const Circle& c1, const Circle& c2, const Circle& c3, std::mt19937& gen, std::uniform_real_distribution<>& dist, bool is_wide_area, int num_points) {
    double x_min = 0.0;
    double x_max = 0.0;
    double y_min = 0.0;
    double y_max = 0.0;
    if (is_wide_area) {
        x_min = std::min({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
        x_max = std::max({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
        y_min = std::min({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
        y_max = std::max({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});
    } else {
        x_min = std::max({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
        x_max = std::min({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
        y_min = std::max({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
        y_max = std::min({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});
    }

    int count_inside = 0;

    for (int i = 0; i < num_points; ++i) {
        double px = dist(gen) * (x_max - x_min) + x_min;
        double py = dist(gen) * (y_max - y_min) + y_min;

        if (IsInCircle(px, py, c1) && IsInCircle(px, py, c2) && IsInCircle(px, py, c3)) {
            ++count_inside;
        }
    }

    long double area_rectangle = (x_max - x_min) * (y_max - y_min);
    return static_cast<long double>(count_inside) / num_points * area_rectangle;
}

void ManualInput() {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<> dist(0.0, 1.0);

    Circle c1, c2, c3;
    std::cin >> c1.x >> c1.y >> c1.r;
    std::cin >> c2.x >> c2.y >> c2.r;
    std::cin >> c3.x >> c3.y >> c3.r;

    int num_points = 10000000;

    long double intersection_area = MonteCarloIntersection(c1, c2, c3, gen, dist, false, num_points);

    std::cout << std::fixed << std::setprecision(12) << intersection_area << std::endl;
}

void Gen() {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<> dist(0.0, 1.0);

    int min_n = 100;
    int max_n = 100000;
    int step = 500;

    Circle c1 = {1, 1, 1};
    double radius = sqrt(5) / 2;
    Circle c2 = {1.5, 2, radius};
    Circle c3 = {2, 1.5, radius};


    for (int cur = min_n; cur <= max_n; cur += step) {
        long double intersection_area = MonteCarloIntersection(c1, c2, c3, gen, dist, true, cur);
        //std::cout << cur << " " << std::fixed << std::setprecision(12) << intersection_area << std::endl;
        std::cout << std::fixed << std::setprecision(12) << intersection_area << std::endl;
    }
}

int main() {
    Gen();
    return 0;
}
