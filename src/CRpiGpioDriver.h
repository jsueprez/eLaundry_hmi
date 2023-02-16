#pragma once

#include <IGpioDriver.h>

class CRpiGpioDriver : public IGpioDriver
{
public:
    CRpiGpioDriver() = default;
    ~CRpiGpioDriver() = default;

    /**
     * @brief Inherited from IGpioDriver
     */
    void set_interface(void *p_interface, const char *p_class) override final;

    /**
     * @brief Inherited from IGpioDriver
     */
    bool init_gpio(int p_pin_number, int p_direction) override final;

    /**
     * @brief Inherited from IGpioDriver
     */
    bool set_value(int p_pin_number, int p_value) const override final;

    /**
     * @brief Inherited from IGpioDriver
     */
    bool deinit_gpio(int p_pin_number) const override final;

    bool is_init(int p_pin_number) const ;

private:

    enum Direction {Out, in};

    bool is_exported(int p_number) const;
    bool export_gpio(int p_pin_number) const;
    bool unexport_gpio(int p_number) const;
    bool set_direction(int p_pin_number, Direction p_direction) const;

};

