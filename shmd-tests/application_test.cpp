#include <gtest/gtest.h>

#include "application.h"

TEST(ApplicationTest, run) {
    using namespace std::chrono;

    steady_clock::time_point mockTime = steady_clock::now();
    std::vector<steady_clock::duration> sleepDurations;
    auto mockClock = [&mockTime] {
        return mockTime;
    };

    auto mockSleepFunction = [&mockTime, &sleepDurations](steady_clock::duration duration) {
        mockTime += duration;
        sleepDurations.push_back(duration);
    };

    int count = 0;
    auto callable = [&count, &mockTime] {
        mockTime += milliseconds(100 * count);
        count++;
        return count >= 5;
    };

    Application app;

    app.run(callable, 2, mockClock, mockSleepFunction);

    EXPECT_EQ(count, 5);

    EXPECT_EQ(sleepDurations.size(), 4);
    EXPECT_EQ(sleepDurations[0], milliseconds(500));
    EXPECT_EQ(sleepDurations[1], milliseconds(400));
    EXPECT_EQ(sleepDurations[2], milliseconds(300));
    EXPECT_EQ(sleepDurations[3], milliseconds(200));
}
