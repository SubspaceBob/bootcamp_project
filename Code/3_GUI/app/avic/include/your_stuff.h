#ifndef YOUR_STUFF_H
#define YOUR_STUFF_H
#include "can_opener.h"
#include "cluster_updater.h"

class yourStuff : public QObject {
    Q_OBJECT
public:
    yourStuff() = delete;
    yourStuff(const std::string &_ifName, QObject *_);




private:
    bool run();
    void YouHaveJustRecievedACANFrame(const canfd_frame * const _frame);
    void readMyEngineFrame(const unsigned char * const _data);
    void timerEvent(QTimerEvent*) override;
//signals:
//    void die();

private:
    size_t Counter;
    CANOpener CANReader;
    ClusterUpdater InstrumentCluster;
    _icons telltales;
    bool ignitionOn=false;
    bool engineRunning=false;
    size_t startuptimer=0;

};

#endif // YOUR_STUFF_H