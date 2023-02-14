#include "NovaCore.h"

#include <fstream>

#include <systemd/sd-daemon.h>

#include <assert.h>
#include <chrono>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <QTimer>
#include "HMILog.h"

#define SCREEN_ON   true
#define SCREEN_OFF  false

constexpr uint32_t hash(const char *p_str, int p_off = 0) noexcept
{
    return !p_str[p_off] ? 5381 : (hash(p_str, p_off + 1) * 33) ^ static_cast<uint32_t>(p_str[p_off]);
}

void NovaCore::set_interface(void *p_interface, const char *p_class)
{
    if(strcmp(p_class, "IQtObject") == 0)
    {
        m_window = reinterpret_cast<IQtObject*>(p_interface);
    }
    else if (strcmp(p_class, "IGpioDriver") == 0)
    {
        m_gpioDriver = reinterpret_cast<IGpioDriver*>(p_interface);
    }
    else if (strcmp(p_class, "BackendDashboard") == 0)
    {
        m_backendDashboard = reinterpret_cast<IBackend*>(p_interface);
    }
    else
    {
        assert(0);
    }

}

void NovaCore::init()
{
    HMILog log(__func__);
    log.info("Initializing Nova data object");

    // set refresh function.
    m_refreshFunction = &NovaCore::refresh_main;

    /* VeryCoarseTimer has errors up to 500ms, but reduces CPU usage */
    startTimer(1000, Qt::VeryCoarseTimer);

    // turn on screen
    reset_user_interaction();

    // Set intial state of the HMI
//    m_window->set_property("stateUI", static_cast<int>(UIState::Welcome_Animation));
//    m_window->set_property("stateWB", static_cast<int>(m_session.state));

}

void NovaCore::timerEvent(QTimerEvent*)
{
    HMILog log(__func__);

    assert(m_refreshFunction);

    //notify_watchdog();

    // update current time
    m_now = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::steady_clock::now() - m_start).count() * 0.001;

    // call selected refresh function
    (this->*m_refreshFunction)();
}

void NovaCore::refresh_main()
{
    HMILog log(__func__);

    if (m_now - m_last_refresh_2s > 2.0)
    {
        refresh_2000ms_backlight();
        m_last_refresh_2s = m_now;
    }
}

bool NovaCore::eventFilter(QObject */*watched*/, QEvent *p_event)
{
    if((p_event->type() != QEvent::MouseButtonPress) && (p_event->type() != QEvent::KeyRelease))
    {
        return false;
    }

    HMILog log(__func__);

    log.info("touched");

    // if the last user activity was 2min ago (i.e. screen is off), turn it on
    if(m_now - m_last_user_interaction > m_backlight_timeout)
    {
        m_window->set_property("stateUI", static_cast<int>(UIState::Welcome_Message));
        reset_user_interaction();
        return true;
    }

    reset_user_interaction();

    return false;
}

void NovaCore::reset_user_interaction()
{
    HMILog log(__func__);

    m_last_user_interaction = m_now;
    set_screen_backlight(SCREEN_ON);

    log.debug("Action", m_last_user_interaction);
    log.debug("   Now", m_now);
}

void NovaCore::refresh_2000ms_backlight()
{
    HMILog log(__func__);

    if (m_now - m_last_user_interaction < m_backlight_timeout)
        return;

    set_screen_backlight(SCREEN_OFF);
}

void NovaCore::set_screen_backlight(bool p_status)
{
    HMILog log(__func__);

    /* Prevent unnecessary writings */
    if (m_backlight == p_status) return;
#ifndef __x86_64__

    std::ofstream out("/sys/class/backlight/rpi_backlight/brightness",std::ios_base::out);

    if(!out)
    {
        log.error("Failed to open gpio value for writing!");
        return;
    }

    // goto to position 0
    out.seekp(0);

    out << (p_status == SCREEN_ON ? "100" : "0") << "\n";
    m_backlight = p_status;

    log.info("Backlight turned", p_status == SCREEN_ON ? "on" : "off");

    out.close();

#else
    m_backlight = p_status;
#endif
}

void NovaCore::on_welcome_animation_end()
{
    HMILog log(__func__);
    m_window->set_property("stateUI", static_cast<int>(UIState::Dashboard));
    m_backendDashboard->refresh();
}
