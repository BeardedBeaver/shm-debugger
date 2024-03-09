#include <gtest/gtest.h>

#include "data_iracing.h"
#include "irsdk_defines.h"

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

        {
            irsdk_varHeader headerEntry;
            headerEntry.type = 1;
            headerEntry.offset = 2;
            headerEntry.count = 3;
            headerEntry.countAsTime = true;
            strcpy_s(headerEntry.name, "TestName");
            strcpy_s(headerEntry.desc, "TestDesc");
            strcpy_s(headerEntry.unit, "TestUnit");

            testData.headerEntries.push_back(headerEntry);
        }

        {
            irsdk_varHeader headerEntry;
            headerEntry.type = 2;
            headerEntry.offset = 3;
            headerEntry.count = 4;
            headerEntry.countAsTime = true;
            strcpy_s(headerEntry.name, "TestName2");
            strcpy_s(headerEntry.desc, "TestDesc2");
            strcpy_s(headerEntry.unit, "TestUnit2");

            testData.headerEntries.push_back(headerEntry);
        }

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

    for (int i = 0; i < lhs.header.numVars; i++) {
        EXPECT_EQ(lhs.headerEntries[i].type, rhs.headerEntries[i].type);
        EXPECT_EQ(lhs.headerEntries[i].offset, rhs.headerEntries[i].offset);
        EXPECT_EQ(lhs.headerEntries[i].count, rhs.headerEntries[i].count);
        EXPECT_EQ(lhs.headerEntries[i].countAsTime, rhs.headerEntries[i].countAsTime);
        EXPECT_STREQ(lhs.headerEntries[i].name, rhs.headerEntries[i].name);
        EXPECT_STREQ(lhs.headerEntries[i].desc, rhs.headerEntries[i].desc);
        EXPECT_STREQ(lhs.headerEntries[i].unit, rhs.headerEntries[i].unit);
    }

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
