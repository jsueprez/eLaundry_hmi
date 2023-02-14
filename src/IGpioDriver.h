#pragma once

class IGpioDriver
{
public:
    virtual ~IGpioDriver() = default;

    /**
     * @brief Set interfaces
     */
    virtual void set_interface(void *p_interface, const char *p_class) = 0;

    virtual bool init_gpio(int p_pin_number, int p_direction) = 0;
    virtual bool set_value(int p_pin_number, int p_value) const = 0;
    virtual bool clear_pin(int p_pin_number) const = 0;
    virtual bool deinit_gpio(int p_pin_number) const = 0;
};
