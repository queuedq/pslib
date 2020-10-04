#include <gtest/gtest.h>
#include "dsu.cc"

TEST(DSU, DSUWorks) {
  const int size = 25;
  disjoint_set D(size);

  for (int i=0; i<20; i++) D.merge(i, i+5);

  EXPECT_EQ(D.find(3), D.find(23));
  EXPECT_TRUE(D.same(3, 23));
  EXPECT_EQ(D.size(13), 5);
}
