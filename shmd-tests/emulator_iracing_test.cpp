#include <gtest/gtest.h>

#include "emulator_iracing.h"

TEST(iRacingEmulatorTest, Construction) {
    iRacing::Emulator emulator;

    // verify asserts in initialize() and stop()
    emulator.initialize();
    emulator.stop();
    emulator.initialize();
}
