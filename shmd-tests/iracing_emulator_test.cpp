#include <gtest/gtest.h>

#include "iracing_emulator.h"

TEST(iRacingEmulatorTest, Construction) {
    iRacing::Emulator emulator;

    // verify asserts in initialize() and stop()
    emulator.initialize();
    emulator.stop();
    emulator.initialize();
}
