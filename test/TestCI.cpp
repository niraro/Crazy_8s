/**
 * @author Crazy-8 groups
 * @date 2023-02
*/

#include "gtest/gtest.h"
#include "CI.h"

TEST(TestCI, SetCIStrategyTest) {
    Hand* hand = new Hand();
    CI* ci = new CI("ci", 1, hand);
    CI* ci2 = new CI();

    ci->setStrategy(CIStrategy::PlaySameRank);
    EXPECT_EQ(ci->getStrategy(), CIStrategy::PlaySameRank);
    EXPECT_EQ(ci2->getStrategy(), CIStrategy::PlaySameRank);

    ci->setStrategy(CIStrategy::PlaySameSuit);
    EXPECT_NE(ci->getStrategy(), CIStrategy::PlaySameRank);

    delete ci;
    delete ci2;
}
