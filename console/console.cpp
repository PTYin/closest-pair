#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include "core.hpp"

using rng_type = mt19937;
using dist = uniform_real_distribution<>;

struct Reg {
    static const unsigned NUM = 1, TOP = 2, RIGHT = 3, BOTTOM = 4, LEFT = 5;
};
constexpr int REG_SIZE = Reg::LEFT;
unsigned config[REG_SIZE + 1] = {0, static_cast<int>(1e3), 1000, 1000, 0, 0};

void process(int num, dist &distX, dist &distY, rng_type &rng) {

    vector<pair<double, double>> points(num);
    for (auto &point: points) {
        point.first = distX(rng), point.second = distY(rng);
    }

    auto current = []() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    };
    chrono::milliseconds start = current();
    auto ans = run<double>(points, [](const auto &p) { return p.first; }, [](const auto &p) { return p.second; });
    cout << num << ", " << (current() - start).count() << ", ";
    start = current();
    ans = runNaive<double>(points, [](const auto &p) { return p.first; }, [](const auto &p) { return p.second; });
    cout << (current() - start).count() << endl;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++)
        config[i] = strtol(argv[i], nullptr, 10);

    random_device dev;
    rng_type rng(dev());
    dist distX(config[Reg::LEFT], config[Reg::RIGHT]), distY(config[Reg::BOTTOM], config[Reg::TOP]);

    vector<pair<double, double>> points(config[Reg::NUM]);
    for (auto &point: points) {
        point.first = distX(rng), point.second = distY(rng);
    }

    if (argc > 1) {
        auto current = []() {
            return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
        };
        chrono::milliseconds start = current();
        auto ans = run<double>(points, [](const auto &p) { return p.first; }, [](const auto &p) { return p.second; });
        cout << "The closest pair of points: P1(" << points[ans.first].first << ", " << points[ans.first].second
             << ")  "
             << "P2(" << points[ans.second].first << ", " << points[ans.second].second << ")." << endl;
        cout << "The distance: " << dis<double>(points[ans.first], points[ans.second]) << endl;
        cout << "The elapsed time equals " << (current() - start).count() << "ms." << endl;
    } else {
        cout << "N, O(n lgn), O(n2)" << endl;
        for (unsigned num = config[Reg::NUM] / 1000; num <= config[Reg::NUM]; num += config[Reg::NUM] / 1000)
            process(num, distX, distY, rng);
    }
    return 0;
}