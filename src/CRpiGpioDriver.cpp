#include "CRpiGpioDriver.h"
#include "wlog.h"
#include <fstream>

CRpiGpioDriver::CRpiGpioDriver()
{

}

void CRpiGpioDriver::set_interface(void *p_interface, const char *p_class)
{
     wError("No interfaces for this module: %s\n", p_class);
}

bool CRpiGpioDriver::init_gpio(int p_pin_number, int p_direction)
{
    export_gpio(p_pin_number);

    Direction direction = static_cast<Direction>(p_direction);

    set_direction(p_pin_number, direction);

    return 1;

}


bool CRpiGpioDriver::set_value(int p_pin_number, int p_value) const
{
    std::string path = "/sys/class/gpio/gpio";
    path.append(std::to_string(p_pin_number));
    path.append("/value");
    std::ofstream out("/sys/class/gpio/gpio",std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio value for writing!");
        return 1;
    }

    // goto to position 0
    out.seekp(0);

    out << std::to_string(p_value);

    wInfo("Gpio %d set to %d", p_pin_number, p_value);

    out.close();

    return 0;
}

bool CRpiGpioDriver::deinit_gpio(int p_pin_number) const
{
    return 0;
}

void CRpiGpioDriver::export_gpio(int p_pin_number) const
{
    std::ofstream out("/sys/class/gpio/export",std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio value for writing!");
        return;
    }

    // goto to position 0
    out.seekp(0);

    out << p_pin_number;

    wInfo("Gpio %d exported", p_pin_number);

    out.close();
}

void CRpiGpioDriver::set_direction(int p_pin_number, Direction p_direction) const
{
    std::string path = "/sys/class/gpio/gpio";
    path.append(std::to_string(p_pin_number));
    path.append("/direction");

    std::ofstream out(path,std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio value for writing!");
        return;
    }

    std::string direction = (p_direction == Direction::Out ? "out" : "in");

    out << direction;

    wInfo("Set Gpio %d as %s", p_pin_number, direction.c_str());

    out.close();
}
