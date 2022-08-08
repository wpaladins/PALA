#include <random>

#include "random_generator.h"
#include "flags.h"

using namespace pala;

RandomGenerator::RandomGenerator() {
    srand(time(nullptr));
}

void RandomGenerator::Generate(int& source1, int& source2, int& source3, int& target) {
    source1 = rand() % ARRAY_SIZE;
    do {
        source2 = rand() % ARRAY_SIZE;
    } while (source2 == source1);
    do {
        source3 = rand() % ARRAY_SIZE;
    } while (source3 == source1 || source3 == source2);
    target = rand() % ARRAY_SIZE;
}
