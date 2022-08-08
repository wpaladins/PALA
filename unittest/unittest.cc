#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gflags/gflags.h>

#include "tools/random_generator.h"
#include "flags.h"
#include "concurrent_array.h"
#include "worker.h"

using namespace std;
using namespace pala;

DECLARE_int32(WORKER_NUM);
DECLARE_int32(WORKER_OP_NUM);

namespace {
    array<int, ARRAY_SIZE> mock_data;
    vector<vector<int>> positions;
    int position_index = 0;
}

// (link period) mock RandomGenerator
RandomGenerator::RandomGenerator() {}
void RandomGenerator::Generate(int& source1, int& source2, int& source3, int& target) {
    assert(position_index < positions.size());
    source1 = positions[position_index][0];
    source2 = positions[position_index][1];
    source3 = positions[position_index][2];
    target  = positions[position_index][3];
    position_index++;
}

class PalaUnittest : public testing::Test {
protected:
    void SetUp() override {
        FLAGS_WORKER_NUM = 1;  // must be 1
        FLAGS_WORKER_OP_NUM = 50;
        positions.clear();
        position_index = 0;

        // random data
        for (int i = 0; i < ARRAY_SIZE; i++) {
            mock_data[i] = rand() % 1000;
        }
        mConcurrentArray = ConcurrentArray<ARRAY_SIZE>::get_instance();
        mConcurrentArray->Init(mock_data);

        // random position
        for (int i = 0; i < FLAGS_WORKER_OP_NUM; i++) {
            vector<int> pos(4);
            pos[0] = rand() % ARRAY_SIZE;
            do {
                pos[1] = rand() % ARRAY_SIZE;
            } while (pos[1] == pos[0]);
            do {
                pos[2] = rand() % ARRAY_SIZE;
            } while (pos[2] == pos[0] || pos[2] == pos[1]);
            pos[3] = rand() % ARRAY_SIZE;
            positions.emplace_back(pos.begin(), pos.end());
        }

        // target = source1/2/3
        assert(FLAGS_WORKER_OP_NUM >= 3);
        positions[0][3] = positions[0][1];
        positions[1][3] = positions[1][2];
        positions[2][3] = positions[2][3];

        // sequential caculate
        for (int i = 0; i < FLAGS_WORKER_OP_NUM; i++) {
            auto& pos = positions[i];
            mock_data[pos[3]] = mock_data[pos[0]] + mock_data[pos[1]] + mock_data[pos[2]];
        }
    }
    ConcurrentArray<ARRAY_SIZE>* mConcurrentArray;
};

TEST_F(PalaUnittest, Test) {
    vector<Worker> workers(FLAGS_WORKER_NUM);
    for (auto& worker : workers) {
        worker.Wait();
    }

    const auto& dat = mConcurrentArray->get_data();
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(dat[i], mock_data[i]);
    }
}
