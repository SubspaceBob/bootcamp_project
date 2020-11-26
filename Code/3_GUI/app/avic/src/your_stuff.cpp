//#include <chrono>
#include <thread>
#include <iostream>
#include "your_stuff.h"
#include "cluster_updater.h"
#include <bitset>

namespace CANID {
const canid_t frame4=0x004;
const canid_t frame5=0x005;
const canid_t frame6=0x006;
const canid_t frame7=0x007;

}

void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
        switch (_frame->can_id) {
        case CANID::frame4: {
                this->InstrumentCluster.setSpeed(static_cast <double> (_frame->data[0]));
                break;  
        }
        case CANID::frame5 : {
            double rpm =_frame->data[1];
            rpm=rpm*256;
            rpm =rpm+_frame->data[2];
            this->InstrumentCluster.setGearPindle_int(_frame->data[0]);
            this->InstrumentCluster.setRPM(rpm);
            // IF D or R gear start on gear1
            if (static_cast<int> (_frame->data[0]) == 3 || static_cast<int> (_frame->data[0]) == 1) 
                {this->InstrumentCluster.setGear(static_cast<const char &> (_frame->data[3] +1));}
            // IF N or P gear lock on gear0
            else 
                {this->InstrumentCluster.setGear(static_cast<const char &> (_frame->data[3]));}
            break;
        }

        case CANID::frame6 : {
            if (std::bitset <8> (0b00000001 & _frame->data[0]).any())
                this->telltales.hazard=1;
            else
                this->telltales.hazard=0;

            if (std::bitset <8> (0b00000010 & _frame->data[0]).any())
                this->telltales.right_blinker=1;
            else
                this->telltales.right_blinker=0;

            if (std::bitset <8> (0b00000100 & _frame->data[0]).any())
                this->telltales.left_blinker=1;
            else
                this->telltales.left_blinker=0;

            if (std::bitset <8> (0b00001000 & _frame->data[0]).any())
                this->telltales.engine_check=1;
            else
                this->telltales.engine_check=0;
            
            if (std::bitset <8> (0b00010000 & _frame->data[0]).any())
                this->telltales.oil_check=1;
            else
                this->telltales.oil_check=0;

            if (std::bitset <8> (0b00100000 & _frame->data[0]).any())
                this->telltales.abs=1;
            else
                this->telltales.abs=0;   

            if (std::bitset <8> (0b01000000 & _frame->data[0]).any())
                this->telltales.battery=1;
            else
                this->telltales.battery=0;

            if (std::bitset <8> (0b10000000 & _frame->data[0]).any())
                this->telltales.seat_belt=1;
            else
                this->telltales.seat_belt=0;

            if (std::bitset <8> (0b00000001 & _frame->data[1]).any())
                this->telltales.doors_open=1;
            else
                this->telltales.doors_open=0;

            if (std::bitset <8> (0b00000010 & _frame->data[1]).any())
                this->telltales.high_beam=1;
            else
                this->telltales.high_beam=0;

            if (std::bitset <8> (0b00000100 & _frame->data[1]).any())
                this->telltales.hand_break=1;
            else
                this->telltales.hand_break=0;                 


            this->InstrumentCluster.setIcon(const_cast<const struct _icons * >(&(this->telltales)));
            break;
            }
        case CANID::frame7 : {
            if (_frame->data[0]==1 && this->engineRunning==false) {
                this->InstrumentCluster.ignite(1);
                this->ignitionOn=true;
                this->startuptimer=0;
                this->engineRunning=true;
            }
            else if(_frame->data[0]!=1)
            {
                this->InstrumentCluster.ignite(0);
                this->engineRunning=false;
            }
            break;
        }

            default:
            break;
        }
    
   
        



}

void yourStuff::readMyEngineFrame(const unsigned char * const _data) {
    this->InstrumentCluster.setSpeed(static_cast<double>(_data[0]));
}










/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();
    this->InstrumentCluster.init(_vs);

    this->startTimer(1);
}

bool yourStuff::run() {
    bool ret = true;
    canfd_frame frame;    
    CANOpener::ReadStatus status = this->CANReader.read(&frame);    

    if (status == CANOpener::ReadStatus::ERROR) ret = false;

    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;

    else if (status == CANOpener::ReadStatus::OK) {
        this->Counter = 0;
        if(this->ignitionOn){
            if(++this->startuptimer>500)
                this->ignitionOn=false;
        }
        else
        {
            this->YouHaveJustRecievedACANFrame(&frame);
        }
        
        

    }
    //if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
    exit(-1);
    }
}

