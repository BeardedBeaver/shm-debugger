#include <gtest/gtest.h>

#include "iracing_data.h"

class iRacingDataTest : public ::testing::Test {
protected:
    void SetUp() override {
        testData.header.ver = 123;
        testData.header.status = 456;
        testData.header.tickRate = 789;
        testData.header.sessionInfoUpdate = 1;
        testData.header.sessionInfoLen = 10;
        testData.header.sessionInfoOffset = 20;
        testData.header.numVars = 2;
        testData.header.varHeaderOffset = 30;
        testData.header.numBuf = 1;
        testData.header.bufLen = 40;

        testData.headerEntry.type = 1;
        testData.headerEntry.offset = 2;
        testData.headerEntry.count = 3;
        testData.headerEntry.countAsTime = true;
        strcpy_s(testData.headerEntry.name, "TestName");
        strcpy_s(testData.headerEntry.desc, "TestDesc");
        strcpy_s(testData.headerEntry.unit, "TestUnit");

        testData.sessionInfo = "Sample session info";

        testData.rawDataLength = 4;
        testData.rawData = std::make_unique<char[]>(testData.rawDataLength);
        testData.rawData[0] = 'A';
        testData.rawData[1] = 'B';
        testData.rawData[2] = 'C';
        testData.rawData[3] = 'D';
    }

    void TearDown() override {
        testData.rawData = nullptr;
    }

    iRacing::Data testData;
};

void compareData(const iRacing::Data& lhs, const iRacing::Data& rhs) {
    EXPECT_EQ(lhs.header.ver, rhs.header.ver);
    EXPECT_EQ(lhs.header.status, rhs.header.status);
    EXPECT_EQ(lhs.header.tickRate, rhs.header.tickRate);
    EXPECT_EQ(lhs.header.sessionInfoUpdate, rhs.header.sessionInfoUpdate);
    EXPECT_EQ(lhs.header.sessionInfoLen, rhs.header.sessionInfoLen);
    EXPECT_EQ(lhs.header.sessionInfoOffset, rhs.header.sessionInfoOffset);
    EXPECT_EQ(lhs.header.numVars, rhs.header.numVars);
    EXPECT_EQ(lhs.header.varHeaderOffset, rhs.header.varHeaderOffset);
    EXPECT_EQ(lhs.header.numBuf, rhs.header.numBuf);
    EXPECT_EQ(lhs.header.bufLen, rhs.header.bufLen);

    EXPECT_EQ(lhs.headerEntry.type, rhs.headerEntry.type);
    EXPECT_EQ(lhs.headerEntry.offset, rhs.headerEntry.offset);
    EXPECT_EQ(lhs.headerEntry.count, rhs.headerEntry.count);
    EXPECT_EQ(lhs.headerEntry.countAsTime, rhs.headerEntry.countAsTime);
    EXPECT_STREQ(lhs.headerEntry.name, rhs.headerEntry.name);
    EXPECT_STREQ(lhs.headerEntry.desc, rhs.headerEntry.desc);
    EXPECT_STREQ(lhs.headerEntry.unit, rhs.headerEntry.unit);

    EXPECT_EQ(lhs.sessionInfo, rhs.sessionInfo);

    EXPECT_EQ(lhs.rawDataLength, rhs.rawDataLength);
    for (size_t i = 0; i < rhs.rawDataLength; ++i) {
        EXPECT_EQ(lhs.rawData[i], rhs.rawData[i]);
    }
}

TEST_F(iRacingDataTest, serialize) {
    auto serializedData = serializeData(testData);
    iRacing::Data deserializedData = iRacing::deserializeData(serializedData);
    compareData(deserializedData, testData);
}

TEST_F(iRacingDataTest, serializeNoSessionInfo) {
    testData.sessionInfo.clear();
    auto serializedData = serializeData(testData);
    iRacing::Data deserializedData = iRacing::deserializeData(serializedData);
    compareData(deserializedData, testData);
}