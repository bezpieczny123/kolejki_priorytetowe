#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "../../kolejki_priorytetowe/list_queue.hpp"
#include "../../kolejki_priorytetowe/heap_queue.hpp"
#include "../../kolejki_priorytetowe/dynamic_array.hpp"

static std::ofstream file;

template <typename Clock = std::chrono::steady_clock>
using TimePoint = std::chrono::time_point<Clock>;

template <typename Clock = std::chrono::steady_clock>
long long measureNs(std::function<void()> fn) {
    auto start = Clock::now();
    fn();
    auto end = Clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <template <typename, typename> class PQ>
void measure_structure(const std::string& name, const std::vector<int>& sizes) {
    file.open(name + ".csv");
    file << name << "\n"
        << "size;add;remove;peek;changePriority;size\n";

    PQ<int, std::less<>> Q;
    long global_index = 1'500'000;
    long current_min = global_index;
    long current_max = global_index;

    for (size_t idx = 1; idx < sizes.size(); ++idx) {
        int target = sizes[idx];
        for (int i = sizes[idx - 1]; i < target; ++i) {
            Q.add(global_index, global_index);
            current_min = std::min(current_min, global_index);
            current_max = std::max(current_max, global_index);
            --global_index;
        }

        std::vector<long long> timesAdd, timesRemove, timesPeek, timesChange, timesSize;
        const int trials = 100;

		// pomiary czasu
        for (int t = 0; t < trials; ++t) {
            int mid = static_cast<int>((current_min + current_max) / 2);
            int oldPr = mid - 10;
            int newPr = mid + 10;

            timesAdd.push_back(measureNs([&]() { Q.add(mid, mid); }));

            timesRemove.push_back(measureNs([&]() { Q.remove(); }));

            timesPeek.push_back(measureNs([&]() { Q.peek(); }));

            Q.add(oldPr, oldPr);
            timesChange.push_back(measureNs([&]() { Q.changePriority(oldPr, oldPr, newPr); }));

            timesSize.push_back(measureNs([&]() { Q.size(); }));

            current_min = std::min(current_min, static_cast<long>(newPr));
            current_max = std::max(current_max, static_cast<long>(newPr));
        }

        // liczenie mediany
        auto median = [&](std::vector<long long>& v) {
            std::sort(v.begin(), v.end());
            if (v.size() % 2 == 0) {
                return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2;
            }
            else {
                return v[v.size() / 2];
            }
            };

        long long medAdd = median(timesAdd);
        long long medRemove = median(timesRemove);
        long long medPeek = median(timesPeek);
        long long medChange = median(timesChange);
        long long medSize = median(timesSize);

        file << target << ";"
            << medAdd << ";"
            << medRemove << ";"
            << medPeek << ";"
            << medChange << ";"
            << medSize << "\n";
    }

    file.close();
}


int main() {
    std::vector<int> sizes = {
        0, 1'000, 2'000, 4'000, 8'000, 16'000,
        32'000, 64'000, 128'000, 256'000, 512'000, 1'024'000
    };

    measure_structure<ListPriorityQueue>("ListQueue", sizes);
    measure_structure<HeapPriorityQueue>("HeapQueue", sizes);

    return EXIT_SUCCESS;
}
