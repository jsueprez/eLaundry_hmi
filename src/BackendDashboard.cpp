#include "BackendDashboard.h"

#include <QTime>
#include "HMILog.h"

void BackendDashboard::set_interface(void *p_interface, const char *p_class)
{
    if (strcmp(p_class, "IQtObject") == 0)
    {
        m_frontend = reinterpret_cast<IQtObject*>(p_interface);
    }
    else if (strcmp(p_class, "IChargerCore") == 0)
    {
        //m_chargerCore = reinterpret_cast<IChargerCore*>(p_interface);
    }
    else
    {
        assert(0);
    }
}

void BackendDashboard::set_frontend(QQuickItem *p_frontend)
{
    m_frontend->set_item(p_frontend);
}

void BackendDashboard::init()
{
}

void BackendDashboard::on_hide()
{
}

void BackendDashboard::on_show()
{
}

void BackendDashboard::on_start()
{

}

void BackendDashboard::refresh()
{
    HMILog log(__func__);

    if(m_frontend->is_null()) return;

    /* Update the front-end values for current and energy */
    //m_frontend->set_property("userAmperes",  m_chargerCore->get_user_ampere());
    //m_frontend->set_property("power", format(m_chargerCore->get_power()));
}

void BackendDashboard::on_locked_end()
{
    HMILog log(__func__);
    //m_chargerCore->on_locked_end();
}

void BackendDashboard::on_play_end()
{
    HMILog log(__func__);
    //m_chargerCore->on_play_end();
}

void BackendDashboard::on_pause_end()
{
    HMILog log(__func__);
    //m_chargerCore->on_pause_end();
}

QString BackendDashboard::format(double p_value) const
{
    return QString::asprintf("%.1f", p_value);
}

