#include "../../../2_Emulator/Src/emulator_main.cpp"
#include <gtest/gtest.h>

TEST(EmulatorMainTest, trialOne) {

    // Do checks
    ASSERT_EQ(0, 0);

}

//__Test_Main_____________________________________________
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}