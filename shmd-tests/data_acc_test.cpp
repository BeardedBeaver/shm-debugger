#include <gtest/gtest.h>

#include "data_acc.h"

#include <cwchar>

class ACCDataTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

SPageFilePhysicsACC generatePhysicsData() {
    SPageFilePhysicsACC result;

    result.packetId = 1234;
    result.gas = 0.75f;
    result.brake = 0.2f;
    result.fuel = 60.0f;
    result.gear = 3;
    result.rpms = 5000;
    result.steerAngle = 0.1f;
    result.speedKmh = 100.0f;
    result.velocity[0] = 10.0f;
    result.velocity[1] = 20.0f;
    result.velocity[2] = 30.0f;
    result.accG[0] = 0.1f;
    result.accG[1] = -0.2f;
    result.accG[2] = 0.0f;
    result.wheelSlip[0] = 0.1f;
    result.wheelSlip[1] = 0.2f;
    result.wheelSlip[2] = 0.3f;
    result.wheelSlip[3] = 0.4f;
    result.wheelLoad[0] = 500.0f;
    result.wheelLoad[1] = 550.0f;
    result.wheelLoad[2] = 510.0f;
    result.wheelLoad[3] = 520.0f;
    result.wheelsPressure[0] = 32.0f;
    result.wheelsPressure[1] = 32.5f;
    result.wheelsPressure[2] = 32.2f;
    result.wheelsPressure[3] = 31.8f;
    result.wheelAngularSpeed[0] = 50.0f;
    result.wheelAngularSpeed[1] = 52.0f;
    result.wheelAngularSpeed[2] = 48.0f;
    result.wheelAngularSpeed[3] = 55.0f;
    result.tyreWear[0] = 0.2f;
    result.tyreWear[1] = 0.25f;
    result.tyreWear[2] = 0.22f;
    result.tyreWear[3] = 0.21f;
    result.tyreDirtyLevel[0] = 0.05f;
    result.tyreDirtyLevel[1] = 0.08f;
    result.tyreDirtyLevel[2] = 0.06f;
    result.tyreDirtyLevel[3] = 0.07f;
    result.tyreCoreTemperature[0] = 80.0f;
    result.tyreCoreTemperature[1] = 82.0f;
    result.tyreCoreTemperature[2] = 85.0f;
    result.tyreCoreTemperature[3] = 81.0f;
    result.camberRAD[0] = 0.02f;
    result.camberRAD[1] = 0.03f;
    result.camberRAD[2] = 0.02f;
    result.camberRAD[3] = 0.01f;
    result.suspensionTravel[0] = 0.1f;
    result.suspensionTravel[1] = 0.09f;
    result.suspensionTravel[2] = 0.12f;
    result.suspensionTravel[3] = 0.11f;
    result.drs = 0.0f;
    result.tc = 0.0f;
    result.heading = 0.5f;
    result.pitch = -0.2f;
    result.roll = 0.0f;
    result.cgHeight = 0.5f;
    result.carDamage[0] = 0.0f;
    result.carDamage[1] = 0.0f;
    result.carDamage[2] = 0.0f;
    result.carDamage[3] = 0.0f;
    result.carDamage[4] = 0.0f;
    result.numberOfTyresOut = 0;
    result.pitLimiterOn = 0;
    result.abs = 0.0f;
    result.kersCharge = 0.8f;
    result.kersInput = 0.0f;
    result.autoShifterOn = 0;
    result.rideHeight[0] = 0.1f;
    result.rideHeight[1] = 0.1f;
    result.turboBoost = 0.2f;
    result.ballast = 50.0f;
    result.airDensity = 1.2f;
    result.airTemp = 25.0f;
    result.roadTemp = 30.0f;
    result.localAngularVel[0] = 0.0f;
    result.localAngularVel[1] = 0.0f;
    result.localAngularVel[2] = 0.0f;
    result.finalFF = 1.0f;
    result.performanceMeter = 90.0f;

    result.engineBrake = 0;
    result.ersRecoveryLevel = 2;
    result.ersPowerLevel = 3;
    result.ersHeatCharging = 0;
    result.ersIsCharging = 1;
    result.kersCurrentKJ = 2.5f;

    result.drsAvailable = 1;
    result.drsEnabled = 0;

    result.brakeTemp[0] = 200.0f;
    result.brakeTemp[1] = 180.0f;
    result.brakeTemp[2] = 210.0f;
    result.brakeTemp[3] = 220.0f;
    result.clutch = 0.8f;

    result.tyreTempI[0] = 80.0f;
    result.tyreTempI[1] = 85.0f;
    result.tyreTempI[2] = 90.0f;
    result.tyreTempI[3] = 88.0f;
    result.tyreTempM[0] = 85.0f;
    result.tyreTempM[1] = 88.0f;
    result.tyreTempM[2] = 86.0f;
    result.tyreTempM[3] = 80.0f;
    result.tyreTempO[0] = 90.0f;
    result.tyreTempO[1] = 92.0f;
    result.tyreTempO[2] = 95.0f;
    result.tyreTempO[3] = 93.0f;

    result.isAIControlled = 0;

    result.tyreContactPoint[0][0] = 0.1f;
    result.tyreContactPoint[0][1] = 0.2f;
    result.tyreContactPoint[0][2] = 0.3f;
    result.tyreContactPoint[1][0] = 0.2f;
    result.tyreContactPoint[1][1] = 0.3f;
    result.tyreContactPoint[1][2] = 0.4f;
    result.tyreContactPoint[2][0] = 0.3f;
    result.tyreContactPoint[2][1] = 0.4f;
    result.tyreContactPoint[2][2] = 0.5f;
    result.tyreContactPoint[3][0] = 0.4f;
    result.tyreContactPoint[3][1] = 0.5f;
    result.tyreContactPoint[3][2] = 0.6f;

    result.tyreContactNormal[0][0] = 0.0f;
    result.tyreContactNormal[0][1] = 0.0f;
    result.tyreContactNormal[0][2] = 1.0f;
    result.tyreContactNormal[1][0] = 0.0f;
    result.tyreContactNormal[1][1] = 0.0f;
    result.tyreContactNormal[1][2] = 1.0f;
    result.tyreContactNormal[2][0] = 0.0f;
    result.tyreContactNormal[2][1] = 0.0f;
    result.tyreContactNormal[2][2] = 1.0f;
    result.tyreContactNormal[3][0] = 0.0f;
    result.tyreContactNormal[3][1] = 0.0f;
    result.tyreContactNormal[3][2] = 1.0f;

    result.tyreContactHeading[0][0] = 0.0f;
    result.tyreContactHeading[0][1] = 1.0f;
    result.tyreContactHeading[0][2] = 0.0f;
    result.tyreContactHeading[1][0] = 0.0f;
    result.tyreContactHeading[1][1] = 1.0f;
    result.tyreContactHeading[1][2] = 0.0f;
    result.tyreContactHeading[2][0] = 0.0f;
    result.tyreContactHeading[2][1] = 1.0f;
    result.tyreContactHeading[2][2] = 0.0f;
    result.tyreContactHeading[3][0] = 0.0f;
    result.tyreContactHeading[3][1] = 1.0f;
    result.tyreContactHeading[3][2] = 0.0f;

    result.brakeBias = 0.6f;

    result.localVelocity[0] = 5.0f;
    result.localVelocity[1] = 0.0f;
    result.localVelocity[2] = -2.0f;

    result.P2PActivations = 1;
    result.P2PStatus = 0;

    result.currentMaxRpm = 8000;

    result.mz[0] = 0.1f;
    result.mz[1] = 0.2f;
    result.mz[2] = 0.3f;
    result.mz[3] = 0.4f;
    result.fx[0] = 1000.0f;
    result.fx[1] = 1020.0f;
    result.fx[2] = 980.0f;
    result.fx[3] = 1010.0f;
    result.fy[0] = 800.0f;
    result.fy[1] = 780.0f;
    result.fy[2] = 790.0f;
    result.fy[3] = 820.0f;
    result.slipRatio[0] = 0.1f;
    result.slipRatio[1] = 0.15f;
    result.slipRatio[2] = 0.12f;
    result.slipRatio[3] = 0.14f;
    result.slipAngle[0] = 0.02f;
    result.slipAngle[1] = 0.03f;
    result.slipAngle[2] = 0.01f;
    result.slipAngle[3] = 0.015f;

    result.tcinAction = 0;
    result.absInAction = 0;

    result.suspensionDamage[0] = 0.0f;
    result.suspensionDamage[1] = 0.0f;
    result.suspensionDamage[2] = 0.0f;
    result.suspensionDamage[3] = 0.0f;

    result.tyreTemp[0] = 80.0f;
    result.tyreTemp[1] = 85.0f;
    result.tyreTemp[2] = 82.0f;
    result.tyreTemp[3] = 86.0f;

    result.waterTemp = 90.0f;

    result.brakePressure[0] = 150.0f;
    result.brakePressure[1] = 160.0f;
    result.brakePressure[2] = 155.0f;
    result.brakePressure[3] = 158.0f;

    result.frontBrakeCompound = 0;
    result.rearBrakeCompound = 0;

    result.padLife[0] = 0.9f;
    result.padLife[1] = 0.85f;
    result.padLife[2] = 0.88f;
    result.padLife[3] = 0.86f;

    result.discLife[0] = 0.8f;
    result.discLife[1] = 0.82f;
    result.discLife[2] = 0.85f;
    result.discLife[3] = 0.88f;

    result.ignitionOn = 1;
    result.starterEngineOn = 0;
    result.isEngineRunning = 1;

    result.kerbVibration = 0.1f;
    result.slipVibrations = 0.2f;
    result.gVibrations = 0.15f;
    result.absVibrations = 0.18f;

    return result;
}

SPageFileGraphicACC generateGraphicData() {
    SPageFileGraphicACC result;

    // Assigning arbitrary values to each field
    result.packetId = 5678;
    result.status = AC_LIVE;
    result.session = ACC_QUALIFY;
    wcscpy_s(result.currentTime, L"01:23.456");
    wcscpy_s(result.lastTime, L"02:34.567");
    wcscpy_s(result.bestTime, L"01:21.345");
    wcscpy_s(result.split, L"00:00.100");
    result.completedLaps = 5;
    result.position = 3;
    result.iCurrentTime = 123456;
    result.iLastTime = 234567;
    result.iBestTime = 121345;
    result.sessionTimeLeft = 600.0f;
    result.distanceTraveled = 2500.0f;
    result.isInPit = 0;
    result.currentSectorIndex = 1;
    result.lastSectorTime = 30000;
    result.numberOfLaps = 15;
    wcscpy_s(result.tyreCompound, L"Soft");
    result.replayTimeMultiplier = 1.0f;
    result.normalizedCarPosition = 0.5f;

    result.activeCars = 20;
    for (int i = 0; i < ACC_CAR_NUMBER; ++i) {
        result.carCoordinates[i][0] = 100.0f + i * 10.0f;
        result.carCoordinates[i][1] = 200.0f + i * 5.0f;
        result.carCoordinates[i][2] = 300.0f + i * 2.5f;
        result.carID[i] = 1000 + i;
    }
    result.playerCarID = 1001;
    result.penaltyTime = 2.0f;
    result.flag = ACC_YELLOW_FLAG;
    result.penalty = PenaltyShortcut::DriveThrough_Cutting;
    result.idealLineOn = 1;
    result.isInPitLane = 0;

    result.surfaceGrip = 1.0f;
    result.mandatoryPitDone = 1;

    result.windSpeed = 5.0f;
    result.windDirection = 180.0f;

    result.isSetupMenuVisible = 0;

    result.mainDisplayIndex = 1;
    result.secondaryDisplayIndex = 2;
    result.TC = 2;
    result.TCCut = 0;
    result.EngineMap = 3;
    result.ABS = 1;
    result.fuelXLap = 3;
    result.rainLights = 0;
    result.flashingLights = 1;
    result.lightsStage = 2;
    result.exhaustTemperature = 800.0f;
    result.wiperLV = 0;
    result.driverStintTotalTimeLeft = 6000;
    result.driverStintTimeLeft = 1500;
    result.rainTyres = 0;

    result.sessionIndex = 2;
    result.usedFuel = 20.0f;
    wcscpy_s(result.deltaLapTime, L"-00:01.234");
    result.iDeltaLapTime = -1234;
    wcscpy_s(result.estimatedLapTime, L"01:30.000");
    result.iEstimatedLapTime = 90000;
    result.isDeltaPositive = 0;
    result.iSplit = 2;
    result.isValidLap = 1;
    result.fuelEstimatedLaps = 10.0f;
    wcscpy_s(result.trackStatus, L"Normal");
    result.missingMandatoryPits = 0;
    result.clock = 123.456f;
    result.directionLightsLeft = 1;
    result.directionLightsRight = 0;
    result.globalYellow = 1;
    result.globalYellow1 = 0;
    result.globalYellow2 = 0;
    result.globalYellow3 = 0;
    result.globalWhite = 0;
    result.globalGreen = 0;
    result.globalChequered = 0;
    result.globalRed = 0;
    result.mfdTyreSet = 1;
    result.mfdFuelToAdd = 5.0f;
    result.mfdTyrePressureLF = 2.0f;
    result.mfdTyrePressureRF = 2.2f;
    result.mfdTyrePressureLR = 2.1f;
    result.mfdTyrePressureRR = 2.3f;
    result.trackGripStatus = ACC_FAST;
    result.rainIntensity = ACC_DRIZZLE;
    result.rainIntensityIn10min = ACC_HEAVY_RAIN;
    result.rainIntensityIn30min = ACC_MEDIUM_RAIN;
    result.currentTyreSet = 2;
    result.strategyTyreSet = 3;
    result.gapAhead = 2;
    result.gapBehind = 3;

    return result;
}

SPageFileStaticACC generateStaticData() {
    SPageFileStaticACC result;

    wcscpy_s(result.smVersion, L"1.0.0");
    wcscpy_s(result.acVersion, L"1.8.0");

    result.numberOfSessions = 3;
    result.numCars = 20;
    wcscpy_s(result.carModel, L"CarModel");
    wcscpy_s(result.track, L"TrackName");
    wcscpy_s(result.playerName, L"John");
    wcscpy_s(result.playerSurname, L"Doe");
    wcscpy_s(result.playerNick, L"PlayerNick");
    result.sectorCount = 3;

    result.maxTorque = 600.0f;
    result.maxPower = 450.0f;
    result.maxRpm = 8000;
    result.maxFuel = 100.0f;
    result.suspensionMaxTravel[0] = 0.1f;
    result.suspensionMaxTravel[1] = 0.12f;
    result.suspensionMaxTravel[2] = 0.11f;
    result.suspensionMaxTravel[3] = 0.09f;
    result.tyreRadius[0] = 0.33f;
    result.tyreRadius[1] = 0.34f;
    result.tyreRadius[2] = 0.32f;
    result.tyreRadius[3] = 0.31f;
    result.maxTurboBoost = 1.5f;

    result.deprecated_1 = -273.0f;
    result.deprecated_2 = -273.0f;

    result.penaltiesEnabled = 1;

    result.aidFuelRate = 1.0f;
    result.aidTireRate = 1.2f;
    result.aidMechanicalDamage = 1.5f;
    result.aidAllowTyreBlankets = 1;
    result.aidStability = 0.8f;
    result.aidAutoClutch = 1;
    result.aidAutoBlip = 1;

    result.hasDRS = 1;
    result.hasERS = 1;
    result.hasKERS = 1;
    result.kersMaxJ = 2.5f;
    result.engineBrakeSettingsCount = 5;
    result.ersPowerControllerCount = 3;
    result.trackSplineLength = 5000.0f;
    wcscpy_s(result.trackConfiguration, L"ConfigA");
    result.ersMaxJ = 4.0f;

    result.isTimedRace = 1;
    result.hasExtraLap = 1;

    wcscpy_s(result.carSkin, L"CarSkin");
    result.reversedGridPositions = 10;
    result.PitWindowStart = 10;
    result.PitWindowEnd = 20;
    result.isOnline = 1;

    wcscpy_s(result.dryTyresName, L"DryTyres");

    return result;
}

TEST_F(ACCDataTest, serialize) {
    ACC::Data data;
    data.physics = generatePhysicsData();
    data.graphics = generateGraphicData();
    data.statics = generateStaticData();

    auto bytes = ACC::serializeData(data);
    auto deser = ACC::deserializeData(bytes);

    // physics
    ASSERT_EQ(data.physics.packetId, deser.physics.packetId);
    ASSERT_EQ(data.physics.gas, deser.physics.gas);
    ASSERT_EQ(data.physics.brake, deser.physics.brake);
    ASSERT_EQ(data.physics.fuel, deser.physics.fuel);
    ASSERT_EQ(data.physics.gear, deser.physics.gear);
    ASSERT_EQ(data.physics.rpms, deser.physics.rpms);
    // ... skipped some values here
    ASSERT_EQ(data.physics.kerbVibration, deser.physics.kerbVibration);
    ASSERT_EQ(data.physics.slipVibrations, deser.physics.slipVibrations);
    ASSERT_EQ(data.physics.gVibrations, deser.physics.gVibrations);
    ASSERT_EQ(data.physics.absVibrations, deser.physics.absVibrations);

    // graphics
    ASSERT_EQ(data.graphics.packetId, deser.graphics.packetId);
    ASSERT_EQ(data.graphics.status, deser.graphics.status);
    ASSERT_EQ(data.graphics.session, deser.graphics.session);
    ASSERT_EQ(wcscmp(data.graphics.currentTime, deser.graphics.currentTime), 0);
    ASSERT_EQ(wcscmp(data.graphics.lastTime, deser.graphics.lastTime), 0);
    ASSERT_EQ(wcscmp(data.graphics.bestTime, deser.graphics.bestTime), 0);
    ASSERT_EQ(wcscmp(data.graphics.split, deser.graphics.split), 0);
    // ... skipped some values here
    ASSERT_EQ(data.graphics.strategyTyreSet, deser.graphics.strategyTyreSet);
    ASSERT_EQ(data.graphics.gapAhead, deser.graphics.gapAhead);
    ASSERT_EQ(data.graphics.gapBehind, deser.graphics.gapBehind);

    // statics
    ASSERT_EQ(wcscmp(data.statics.smVersion, deser.statics.smVersion), 0);
    ASSERT_EQ(wcscmp(data.statics.acVersion, deser.statics.acVersion), 0);
    ASSERT_EQ(data.statics.numberOfSessions, deser.statics.numberOfSessions);
    ASSERT_EQ(data.statics.numCars, deser.statics.numCars);
    // ... skipped some values here
    ASSERT_EQ(data.statics.reversedGridPositions, deser.statics.reversedGridPositions);
    ASSERT_EQ(data.statics.PitWindowStart, deser.statics.PitWindowStart);
    ASSERT_EQ(data.statics.PitWindowEnd, deser.statics.PitWindowEnd);
    ASSERT_EQ(data.statics.isOnline, deser.statics.isOnline);

    ASSERT_EQ(wcscmp(data.statics.dryTyresName, deser.statics.dryTyresName), 0);
}
