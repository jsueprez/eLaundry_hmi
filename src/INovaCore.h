#pragma once

#include <QObject>
#include <string>

#include "types.h"

class INovaCore : public QObject
{
public:
    virtual ~INovaCore() = default;

    /**
    * @brief Set interface pointers
    */
    virtual void set_interface(void *p_interface, const char *p_class) = 0;

    /**
    * @brief Turn screen on/off
    */
    virtual void set_screen_backlight(bool p_status)  = 0;

    /**
    * @brief Initialize database conection, update thread, etc
    */
    virtual void init() = 0;
};
