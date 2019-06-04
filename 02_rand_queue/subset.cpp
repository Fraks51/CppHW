#include "randomized_queue.hpp"

int main(int argc, char ** argv)
{
    randomized_queue<std::string>rand_queue;
    char *end;
    std::string temp_str;
    int k;
    k = std::strtol(argv[0], &end, 10);
    while (getline(std::cin, temp_str)) {
        rand_queue.enqueue(temp_str);
    }
    for (int i = 0; i < k; i++) {
        std::cout << rand_queue.dequeue() << "\n";
    }
    return 0;
}
