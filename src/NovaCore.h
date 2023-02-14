#pragma once

#include "IBackend.h"
#include "IGpioDriver.h"
#include "INovaCore.h"
#include "IQtObject.h"

class NovaCore : public INovaCore
{
    Q_OBJECT
    using RefreshFunction = void (NovaCore::*)(void);
public:
    NovaCore() = default;
    ~NovaCore() override = default;

    void set_interface(void *p_interface, const char *p_class) override final;

    /**
    * @brief Inherited from INOvaCore
    */
    void set_screen_backlight(bool p_status) override final;

    /**
    * @brief Inherited from INovaCore
    */
    void init() override final;

    /**
     * @brief Inherited from QObject
     */
    void timerEvent(QTimerEvent *p_event) override final;

    /**
     * @brief Inherited object from QObject
     */
    bool eventFilter(QObject *p_object, QEvent *p_event) override final;

    /**
     * @brief Inherited from INovaCore
     */
    void on_welcome_animation_end() override final;

private:

    /**
    * @brief Refresh sub-routines
    */
    void refresh_main();

    /**
    * @brief Refresh the state of backlight
    */
    void refresh_2000ms_backlight();

    /**
     * @brief Reset user action timestamp
     */
    void reset_user_interaction();

    /**
    * @brief Dependencies pointers
    */
    IQtObject *m_window = nullptr;
    IGpioDriver * m_gpioDriver = nullptr;

    /**
     * @brief Back-end objects pointers
     */
    IBackend *m_backendDashboard = nullptr;

    /**
    * @brief Current elapsed time (timestamp in seconds)
    */
    double m_now = 0.0;

    /**
    * @brief Last user activity (timestamp in seconds)
    */
    double m_last_user_interaction = 0.0;

    /**
    * @brief Backlight timeout (timestamp in seconds)
    */
    double m_backlight_timeout = 20.0;

    /**
     * @brief Last refresh timestamps (timestamp in seconds)
     */
    double m_last_refresh_2s = -99999.0;
    double m_last_refresh_10s = -99999.0;

    /**
    * @brief Backlight on/off status
    */
    bool m_backlight = false;

    /**
     * @brief Power on time, used to measure ellapsed time
     */
    std::chrono::steady_clock::time_point m_start = std::chrono::steady_clock::now();

    /**
     * @brief Function pointer to be called on timer timeout
     */
    RefreshFunction m_refreshFunction = nullptr;
};
