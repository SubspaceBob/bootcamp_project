#include "gearbox.h"
#include <iomanip>
#include "engine.h"
#include "can_io.h"

int main()
{
    Gearbox x;
<<<<<<< HEAD:Tests/test_gearbox.cpp
    Engine Eng;
    CanInput InputVal;
=======
    Engine eng;
    CanInput inputVal;
>>>>>>> 99eaef477f1ee83043fa951560d9f9d1f816fdcc:Tests/test_gearbox.cpp

    inputVal.gearReq=2;
    eng.setEngTrq(4);

    x.run(inputVal, eng);


    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << x.getSpeed() << std::endl;
    std::cout << x.getRPS()<< std::endl;
    std::cout << static_cast <int> (x.getGearStick()) << std::endl;
    printf("%d  \n", x.getengagedGear());
}
