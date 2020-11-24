#include <gtest/gtest.h>
#include "../../../2_Emulator/Include/gearbox.h"

class Gearbox_Mock : Gearbox
{
public:
    // Wrappers for accessing protected members from outside (for testing) 
    int8_t mockGetEngagedGear(){return engagedGear;}
    void mockSetGearStickPosition(GearPattern TEST_GearStickPosition)
    {
        gearStickPosition = TEST_GearStickPosition;
    }

    void mockGearShiftLogic(int8_t TEST_engagedGear, float TEST_engineRPS, GearPattern TEST_GearStickPosition, int8_t expectedGear){
        engagedGear         = TEST_engagedGear;
        engineRPS           = TEST_engineRPS;
        gearStickPosition   = TEST_GearStickPosition;
        gearShiftLogic();
        EXPECT_EQ(engagedGear, expectedGear);
    }

    Trq mockCalculateBrakeTorque(const int8_t &brakePdl)
    {
        return calculateBrakeTorque(brakePdl);
    }
};