#include <gtest/gtest.h>
#include "Stk.h"
#include "../include/modules/EchoNode.h"
#include "../include/modules/DelayNode.h"

// test member function of delay node
TEST(DelayNodeTest, DelayNodeFunctions) {
    DelayNode delayNode = DelayNode();
    // set length
    ASSERT_EQ(delayNode.setDelayLength(237.0f), true);
    ASSERT_EQ(delayNode.getDelayLength(), 237.0f);

    ASSERT_EQ(delayNode.setDelayLength(-1.0f), true);
    ASSERT_EQ(delayNode.getDelayLength(), 0.0f);
}
