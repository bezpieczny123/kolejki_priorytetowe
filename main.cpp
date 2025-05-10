#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "list_queue.hpp"

std::ofstream file;

std::chrono::steady_clock::time_point begin, end;

void startTimer() {
    begin = std::chrono::steady_clock::now();
}

void stopTimer() {
    end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    file << duration << ",";
    std::cout << duration << ",";
}

#define MEASURE_SOME(function_call) \
    startTimer(); \
    function_call; \
    stopTimer();



template <template <typename, typename> class StructureType>
void measure_structure(const std::string& structureName, const std::vector<int>& listSizes) {
    file.open(structureName + ".csv");
    file << structureName << "\n";
    file << "size, add, remove, peek, changePriority, size\n";

    StructureType<int, std::less<>> List;
    long global_index = 1500000;
    long current_min = global_index;
    long current_max = global_index;

    for (int a = 1; a < static_cast<int>(listSizes.size()); a++) {
        const int n = listSizes[a];
        for (int i = listSizes[a - 1]; i < n; ++i) {
            List.add(global_index, global_index);
            current_min = std::min(current_min, global_index);
            current_max = std::max(current_max, global_index);
            --global_index;
        }

        for (int i = 0; i < 100; ++i) {
            int mid = static_cast<int>((current_min + current_max) / 2);

            file << n << ",";
            std::cout << n << ",";
            MEASURE_SOME(List.add(mid, mid));
            MEASURE_SOME(List.remove());
            MEASURE_SOME(List.peek());

            int oldVal = mid - 10;
            int newVal = mid + 10;
            List.add(oldVal, oldVal);
            MEASURE_SOME(List.changePriority(oldVal, newVal));
            MEASURE_SOME(List.size());

            std::cout << std::endl;
            file << "\n";

            current_min = std::min(current_min, static_cast<long>(newVal));
            current_max = std::max(current_max, static_cast<long>(newVal));
        }
    }

    file.close();
}

int main() {
    std::vector<int> listSizes = {0, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
	measure_structure<ListPriorityQueue>("ListQueue", listSizes);

    return EXIT_SUCCESS;
}