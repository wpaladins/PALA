#ifndef SRC_TOOLS_RANDOM_GENERATOR_H
#define SRC_TOOLS_RANDOM_GENERATOR_H

namespace pala {

class RandomGenerator {
public:
    RandomGenerator();
    void Generate(int& source1, int& source2, int& source3, int& target);
};

}  // namespace pala

#endif  // SRC_TOOLS_RANDOM_GENERATOR_H
