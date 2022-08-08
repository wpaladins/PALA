#ifndef SRC_FLAGS_H
#define SRC_FLAGS_H

#ifndef PALA_UNITTEST
static constexpr int ARRAY_SIZE = 100 * 1000;
#else
static constexpr int ARRAY_SIZE = 100;
#endif

#endif  // SRC_FLAGS_H
