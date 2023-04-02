#include <gtest/gtest.h>

TEST(sampletest, pass) {
  EXPECT_EQ(0, 0);
}

TEST(sampletest, fail) {
  EXPECT_EQ(0, 1);
}