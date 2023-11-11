#include <gtest/gtest.h>

#include "application.h"

#include <numeric>

TEST(ApplicationTest, run) {
    using namespace std::chrono;

    steady_clock::time_point mockTime = steady_clock::now();
    std::vector<steady_clock::duration> sleepDurations;
    auto mockClock = [&mockTime] {
        return mockTime;
    };

    auto mockSleepFunction = [&mockTime, &sleepDurations](int ms) {
        auto duration = std::chrono::milliseconds(ms);
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

TEST(ApplicationTest, sleep) {
    using namespace std::chrono;
    const int n = 50;
    std::vector<int> sleeps;
    sleeps.reserve(n);
    for (int i = 0; i < n; i++) {
        auto start = high_resolution_clock::now();
        defaultSleepFunction(120);
        auto end = high_resolution_clock::now();
        int ms = duration_cast<milliseconds>(end - start).count();
        sleeps.push_back(ms);
    }
    double average = static_cast<double>(
                         std::accumulate(sleeps.begin(), sleeps.end(), 0)) /
                     sleeps.size();

    ASSERT_NEAR(average, 120, 1);
}
