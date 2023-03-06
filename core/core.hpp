#ifndef QT_CLOSEST_PAIR_FUNC_HPP
#define QT_CLOSEST_PAIR_FUNC_HPP

#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

template<typename T, typename P, typename X = function<T(const P &)>, typename Y = function<T(const P &)>>
auto dis(P &&a, P &&b, X x = [](const P &p) { return p.first; }, Y y = [](const P &p) { return p.second; }) {
    auto dx = x(a) - x(b);
    auto dy = y(a) - y(b);
    return sqrt(dx * dx + dy * dy);
}

template<typename T, template<typename, typename...> class C, typename P, typename X, typename Y, typename... Args>
static pair<int, int> _run(C<P, Args...> &points, X x, Y y) {
    size_t n = points.size();
    if (n <= 1)
        return {-1, -1};

    T l = static_cast<T>(1e9 + 7), r = 0;
    for (auto p: points) {
        l = min(l, x(p));
        r = max(r, x(p));
    }
    T mid = (l + r) / 2;

    vector<P> left, right;
    vector<int> idLeft, idRight;
    for (int i = 0; i < points.size(); i++) {
        if (x(points[i]) <= mid && left.size() < n / 2) {
            left.push_back(points[i]);
            idLeft.push_back(i);
        } else {
            right.push_back(points[i]);
            idRight.push_back(i);
        }
    }

    pair<int, int> ansLeft = _run<T>(left, x, y);
    pair<int, int> ansRight = _run<T>(right, x, y);
    pair<int, int> ans = {0, 0};
    double d = 1e18;

    if (ansLeft.first != -1 && ansLeft.second != -1) {
        double dLeft = dis<T>(left[ansLeft.first], left[ansLeft.second], x, y);
        if (dLeft < d) {
            d = dLeft;
            ans = {idLeft[ansLeft.first], idLeft[ansLeft.second]};
        }
    }

    if (ansRight.first != -1 && ansRight.second != -1) {
        double dRight = dis<T>(right[ansRight.first], right[ansRight.second], x, y);
        if (dRight < d) {
            d = dRight;
            ans = {idRight[ansRight.first], idRight[ansRight.second]};
        }
    }

    int head = 0, tail = 0;
    for (int i = 0; i < left.size(); i++) {
        T yLeft = y(left[i]);
        while (head < right.size() && y(right[head]) - yLeft < d)
            head++;
        while (tail < head && yLeft - y(right[tail]) > d)
            tail++;
        for (int j = tail; j < head; j++) {
            double dCenter = dis<T>(left[i], right[j], x, y);
            if (dCenter < d) {
                d = dCenter;
                ans = {idLeft[i], idRight[j]};
            }
        }
    }

    return ans;
}

template<typename T, template<typename, typename...> class C, typename P, typename X, typename Y, typename... Args>
pair<int, int> run(C<P, Args...> &points, X x, Y y) {
    sort(begin(points), end(points), [&y](auto &a, auto &b) { return y(a) < y(b); });
    return _run<T>(points, x, y);
}

template<typename T, template<typename, typename...> class C, typename P, typename X, typename Y, typename... Args>
pair<int, int> runNaive(C<P, Args...> &points, X x, Y y) {
    T minVal = static_cast<T>(1e9 + 7);
    pair<int, int> ans;
    for (int i = 0; i < size(points); i++) {
        for (int j = i + 1; j < size(points); j++) {
            T d = dis<T>(points[i], points[j], x, y);
            if (d < minVal) {
                minVal = d;
                ans = {i, j};
            }
        }
    }
    return ans;
}

#endif //QT_CLOSEST_PAIR_FUNC_HPP
