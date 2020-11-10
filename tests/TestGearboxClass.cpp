#include "GearClass.h"
#include <iomanip>

int main()
{
    float y=19.259;
    Gearbox x;

    x.setSpeed(119.258963);
    x.setRPS(12.3);
    x.setGearStick(D);
    x.setEngagedGear(2);

    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << x.getSpeed() << std::endl;
    std::cout << x.getRPS()<< std::endl;
    std::cout << x.getGearStick() << std::endl;
    printf("%d  \n", x.getEngagedGear());

    x.setSpeed(-111119.258963);
    x.setRPS(-14849562.354656546546);
    x.setGearStick(P);
    x.setEngagedGear(6);

    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << x.getSpeed() << std::endl;
    std::cout << x.getRPS()<< std::endl;
    std::cout << x.getGearStick() << std::endl;
    printf("%d  \n", x.getEngagedGear());

}
