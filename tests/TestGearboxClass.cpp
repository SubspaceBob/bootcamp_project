#include "GearClass.h"
#include <iomanip>
#include "engine.h"
#include "CanInput.h"

int main()
{
    Gearbox x;
    Engine Eng;
    canInput InputVal;

    InputVal.GearReq=2;
    Eng.setEngTrq(4);

    x.run(InputVal, Eng);


    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << x.getSpeed() << std::endl;
    std::cout << x.getRPS()<< std::endl;
    std::cout << static_cast <int> (x.getGearStick()) << std::endl;
    printf("%d  \n", x.getEngagedGear());
}
