#include "../../../2_Emulator/Src/engine.cpp"
#include <gtest/gtest.h>

#include "gearbox.h"

//__Test_of_constructor___________________________________
TEST(engineTest, constructor) {
    // Set up test
    Engine engine;

    // Do checks
    ASSERT_EQ(engine.getEngSts(), Off);
    ASSERT_EQ(engine.getEngTrq(), 0);
}

//__TestFixture_EngineRun_starts_here_____________________
class EngineRun : public ::testing::Test {
public:
    void SetUp(uint8_t brkPdl, uint8_t accPdl, bool startBtn, int gearStick) {
        //Set up stuff here
        // Engine currently don't care about some signals 
        frame3.data.accPdl = accPdl;
        frame3.data.brkPdl = brkPdl;
        frame4.data.gearReq = 0;
        frame1.data.quitEmul = 0;
        frame1.data.startBtn = startBtn;
        frame6.data.gearStick = gearStick;
    }

    void TearDown() override {/*Tear down stuff here*/}

    // Declare needed parts for test
    Engine engine;
    Frame1 frame1;
    Frame3 frame3;
    Frame4 frame4;
    Frame5 frame5;
    Frame6 frame6;
    SharedMemory<Frame5> frame5Mem;
};

//__Individual_inputs_no_action_expected__________________
TEST_F(EngineRun, engineRun_brkPdlPress) {
    SetUp(100,0,0,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

TEST_F(EngineRun, engineRun_accBtnPress) {
    SetUp(0,100,0,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

TEST_F(EngineRun, engineRun_startBtnPress) {
    SetUp(0,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

TEST_F(EngineRun, EngineRun_engineRun_gearStick_P) {
    SetUp(0,0,0,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

TEST_F(EngineRun, engineRun_gearStick_R) {
    SetUp(0,0,0,1);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

TEST_F(EngineRun, engineRun_gearStick_N) {
    SetUp(0,0,0,2);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

TEST_F(EngineRun, engineRun_gearStick_D) {
    SetUp(0,0,0,3);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

//__Turn_on_engine________________________________________
TEST_F(EngineRun, engineRun_turnOn) {
    SetUp(100,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), On);
    EXPECT_EQ(engine.getEngTrq(), 20);
}

//__Gas_pedal_pressed_____________________________________
TEST_F(EngineRun, engineRun_pedalToTheMetall) {
    //  Turn on engine
    SetUp(100,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);

    // Set up for test
    SetUp(0,100,0,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), On);
    EXPECT_EQ(engine.getEngTrq(), 450);
}

//__Engine_off_posible_only_in_P__________________________
TEST_F(EngineRun, engineRun_noTurnOff_R) {
    //  Turn on engine
    SetUp(100,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);

    // Set up for test
    SetUp(0,0,1,1);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), On);
    EXPECT_EQ(engine.getEngTrq(), 20);
}

TEST_F(EngineRun, engineRun_noTurnOff_N) {
    //  Turn on engine
    SetUp(100,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);

    // Set up for test
    SetUp(0,0,1,2);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), On);
    EXPECT_EQ(engine.getEngTrq(), 20);
}

TEST_F(EngineRun, engineRun_noTurnOff_D) {
    //  Turn on engine
    SetUp(100,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);

    // Set up for test
    SetUp(0,0,1,3);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), On);
    EXPECT_EQ(engine.getEngTrq(), 20);
}

TEST_F(EngineRun, engineRun_turnOff) {
    //  Turn on engine
    SetUp(100,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);

    //  Run once more to reset debounce
    SetUp(0,0,0,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);

    // Set up for test
    SetUp(0,0,1,0);
    engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
    
    EXPECT_EQ(engine.getEngSts(), Off);
    EXPECT_EQ(engine.getEngTrq(), 0);
}

//__Test_Main_____________________________________________
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}