#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include "core.hpp"

using rng_type = mt19937;
using dist = uniform_int_distribution<rng_type::result_type>;

struct Reg {
    static const unsigned NUM = 1, TOP = 2, RIGHT = 3, BOTTOM = 4, LEFT = 5;
};
constexpr int REG_SIZE = Reg::LEFT;
int config[REG_SIZE + 1] = {-1, static_cast<int>(1e6), 1000, 1000, 0, 0};

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++)
        config[i] = strtol(argv[i], nullptr, 10);

    random_device dev;
    rng_type rng(dev());
    dist distX(config[Reg::LEFT], config[Reg::RIGHT]), distY(config[Reg::BOTTOM], config[Reg::TOP]);

    vector<pair<unsigned, unsigned>> points(config[Reg::NUM]);
    for (auto &point : points) {
        point.first = distX(rng), point.second = distY(rng);
    }

    auto ans = run(points, [](const auto &p) { return p.first; }, [](const auto &p) { return p.second; });
}