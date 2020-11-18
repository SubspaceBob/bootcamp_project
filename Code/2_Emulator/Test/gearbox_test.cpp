#include "../../../2_Emulator/Src/gearbox.cpp"
#include <gtest/gtest.h>

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

//__Test_Main_____________________________________________
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}