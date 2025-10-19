#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

// Global templated functions
template <typename T>
T getMin(const std::vector<T>& values) {
    static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");
    if (values.empty()) {
        throw std::invalid_argument("getMin: values is empty");
    }
    return *std::min_element(values.begin(), values.end());
}

template <typename T>
T getMax(const std::vector<T>& values) {
    static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");
    if (values.empty()) {
        throw std::invalid_argument("getMax: values is empty");
    }
    return *std::max_element(values.begin(), values.end());
}

template <typename T>
double getAverage(const std::vector<T>& values) {
    static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");
    if (values.empty()) {
        throw std::invalid_argument("getAverage: values is empty");
    }
    // Use long double for safer accumulation, then convert to double
    long double sum = std::accumulate(values.begin(), values.end(), static_cast<long double>(0));
    return static_cast<double>(sum / static_cast<long double>(values.size()));
}

// Templated class
template <typename T>
class Statistics {
private:
    std::vector<T> data;

public:
    static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");

    Statistics() = default;

    // Optional convenience ctor
    Statistics(std::initializer_list<T> init) : data(init) {}

    void addValue(const T& value) {
        data.push_back(value);
    }

    T getMin() const {
        return ::getMin(data);
    }

    T getMax() const {
        return ::getMax(data);
    }

    double getAverage() const {
        return ::getAverage(data);
    }

    // Optional helper to bulk add
    void addValues(const std::vector<T>& values) {
        data.insert(data.end(), values.begin(), values.end());
    }

    // Optional accessor if needed elsewhere
    const std::vector<T>& values() const noexcept { return data; }
};

#endif // STATISTICS_H

