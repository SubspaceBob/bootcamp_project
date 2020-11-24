#include "../../../2_Emulator/Src/gearbox.cpp"
#include "../../../2_Emulator/Include/gearbox.h"
#include <gtest/gtest.h>

#include "gearbox_mock.h"

//__Test_of_constructor___________________________________
TEST(gearboxTest, constructor) {
    // Set up test
    Gearbox gearbox;

    // Do checks
    ASSERT_EQ(gearbox.getEngagedGear(), 0);
    // TODO: Overload =operator in order to 
    // compare gearpattern instead of int
    ASSERT_EQ((int)gearbox.getGearStick() , 0);
    ASSERT_EQ(gearbox.getRPS() , 0);
}

TEST(gearboxTest, calculateEngineRPS_EngineOff) 
{
    ASSERT_EQ(calculateEngineRPS(50, 10, EngSts::Off), 0);
}

TEST(gearboxTest, calculateEngineRPS_EngineOn_IDLE) 
{
    ASSERT_EQ(calculateEngineRPS(1, 10, EngSts::On), VEHICLE::ENGINE_IDLE_RPS);
}

TEST(gearboxTest, calculateEngineRPS_EngineOn_RUNNING) 
{
    ASSERT_EQ(calculateEngineRPS(2, 10, EngSts::On), 20);
}

TEST(gearboxTest, gearShiftLogic)
{
    Gearbox_Mock gb;

    // mockGearShiftLogic(engagedGear, rps,     GearPattern::D,     expectedEngagedGear) 
    // upshifting
    gb.mockGearShiftLogic(0,           5000/60, GearPattern::D,     0);
    gb.mockGearShiftLogic(0,           6100/60, GearPattern::D,     1);
    gb.mockGearShiftLogic(1,           6100/60, GearPattern::D,     2);
    gb.mockGearShiftLogic(2,           6100/60, GearPattern::D,     3);
    gb.mockGearShiftLogic(3,           6100/60, GearPattern::D,     4);
    gb.mockGearShiftLogic(4,           6100/60, GearPattern::D,     5);
    gb.mockGearShiftLogic(5,           6100/60, GearPattern::D,     6);
    gb.mockGearShiftLogic(6,           6100/60, GearPattern::D,     7);
    gb.mockGearShiftLogic(7,           6100/60, GearPattern::D,     7);

    // downshifting
    gb.mockGearShiftLogic(7,           1000/60, GearPattern::D,     6);
    gb.mockGearShiftLogic(6,           1000/60, GearPattern::D,     5);
    gb.mockGearShiftLogic(5,           1000/60, GearPattern::D,     4);
    gb.mockGearShiftLogic(4,           1000/60, GearPattern::D,     3);
    gb.mockGearShiftLogic(3,           1000/60, GearPattern::D,     2);
    gb.mockGearShiftLogic(2,           1000/60, GearPattern::D,     1);
    gb.mockGearShiftLogic(1,           1000/60, GearPattern::D,     0);
    gb.mockGearShiftLogic(0,           1000/60, GearPattern::D,     0);

    // No gear shifting in RND
    gb.mockGearShiftLogic(0,           6100/60, GearPattern::P,     0);
    gb.mockGearShiftLogic(0,           6100/60, GearPattern::R,     0);
    gb.mockGearShiftLogic(0,           6100/60, GearPattern::N,     0);

}

TEST(gearboxTest, calculateGearRatio) 
{
    Gearbox_Mock gb;

    int8_t engagedGear = -1; // out-of-range, treat as 0
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[0        ] * VEHICLE::FINALGEAR);

    engagedGear = 0;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 1;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 2;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 3;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 5;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 6;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 7;
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR);
    
    engagedGear = 8;    // out-of-range, treat as 7
    EXPECT_EQ(calculateGearRatio(GearPattern::D, engagedGear), VEHICLE::GEARRATIOS[7        ] * VEHICLE::FINALGEAR);

    EXPECT_EQ(calculateGearRatio(GearPattern::R, engagedGear), VEHICLE::REVERSE_GEARRATIO * VEHICLE::FINALGEAR);
    EXPECT_EQ(calculateGearRatio(GearPattern::N, engagedGear), 0);
    EXPECT_EQ(calculateGearRatio(GearPattern::P, engagedGear), 0);
    //EXPECT_EQ(test_gb.test_engagedGear(), 0);
}

TEST(gearboxTest, calculateBrakeTorque) 
{
    Gearbox_Mock gb;
    //test_gb.engagedGear = 5;
    // stand still
    EXPECT_EQ(gb.mockCalculateBrakeTorque(-1),  0);     // below-range
    EXPECT_EQ(gb.mockCalculateBrakeTorque(0),   0);     // Zero pedal
    EXPECT_EQ(gb.mockCalculateBrakeTorque(50),  10000); // middle value
    EXPECT_EQ(gb.mockCalculateBrakeTorque(100), 20000); // Max brakepedal
    EXPECT_EQ(gb.mockCalculateBrakeTorque(127), 20000); // If brakepedal value is above range, it is limited to max
    EXPECT_EQ(gb.mockCalculateBrakeTorque(128), 0); // If brakepedal value is above range, it is limited to max
}
//__Test_Main_____________________________________________
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
