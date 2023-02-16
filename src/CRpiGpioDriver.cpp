#include "CRpiGpioDriver.h"
#include "wlog.h"
#include <fstream>
#include <filesystem>

void CRpiGpioDriver::set_interface(void *p_interface, const char *p_class)
{
     wError("No interfaces for this module: %s\n", p_class);
}

bool CRpiGpioDriver::init_gpio(int p_pin_number, int p_direction)
{
    export_gpio(p_pin_number);

    // find a better solution to wait until the gpio is indeed exported
    sleep(1);

    Direction direction = static_cast<Direction>(p_direction);

    if(set_direction(p_pin_number, direction))
    {
        wError("Error trying set direction of Gpio\n")
    }

    return 1;

}


bool CRpiGpioDriver::set_value(int p_pin_number, int p_value) const
{
    std::string path = "/sys/class/gpio/gpio";
    path.append(std::to_string(p_pin_number));
    path.append("/value");

    std::ofstream out(path,std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio value for writing!\n");
        return 1;
    }

    // goto to position 0
    out.seekp(0);

    out << p_value << std::endl;;

    wInfo("Gpio %d set to %d\n", p_pin_number, p_value);

    out.close();

    return 0;
}

bool CRpiGpioDriver::deinit_gpio(int p_pin_number) const
{
    return unexport_gpio(p_pin_number);
}

bool CRpiGpioDriver::is_exported(int p_pin_number) const
{
    const std::filesystem::path gpio{"/sys/class/gpio/gpio" + std::to_string(p_pin_number)};

    if(std::filesystem::exists(gpio))
    {
        wInfo("The Gpio %d was already exported\n", p_pin_number);
        return 1;
    }

    return 0;
}

bool CRpiGpioDriver::export_gpio(int p_pin_number) const
{
    if(is_exported(p_pin_number)) return 1;

    std::string path{"/sys/class/gpio/export"};

    std::ofstream out(path,std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio export for writing!\n");
        return 1;
    }

    // goto to position 0
    out.seekp(0);

    out << p_pin_number << std::endl;;

    wInfo("Gpio %d exported\n", p_pin_number);

    out.close();

    return 0;
}

bool CRpiGpioDriver::unexport_gpio(int p_pin_number) const
{
    if(!is_exported(p_pin_number)) return 1;

    std::string path{"/sys/class/gpio/unexport"};

    std::ofstream out(path,std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio unexport for writing!\n");
        return 1;
    }

    // goto to position 0
    out.seekp(0);

    out << p_pin_number << std::endl;;

    wInfo("Gpio %d unexported\n", p_pin_number);

    out.close();

    return 0;
}

bool CRpiGpioDriver::set_direction(int p_pin_number, Direction p_direction) const
{
    std::string path{"/sys/class/gpio/gpio" + std::to_string(p_pin_number) + "/direction"};

    std::ofstream out(path,std::ios_base::out);

    if(!out)
    {
        wError("Failed to open gpio value for writing!\n");
        return 1;
    }

    std::string direction = (p_direction == Direction::Out ? "out" : "in");

    out << direction << std::endl;;

    wInfo("Set Gpio %d as %s\n", p_pin_number, direction.c_str());

    out.close();

    return 0;
}
