#include "BackendWelcomeMessage.h"

#include <sys/types.h>
#include <sys/stat.h>

#include "HMILog.h"

#define FOLDER "/home/root/.wallbox/"

void BackendWelcomeMessage::set_interface(void *p_interface, const char *p_class)
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

void BackendWelcomeMessage::set_frontend(QQuickItem *p_frontend)
{
    m_frontend->set_item(p_frontend);
}

void BackendWelcomeMessage::init()
{
}

void BackendWelcomeMessage::on_hide()
{
    HMILog log(__func__);
    m_frontend->set_property("visible", false);
}

void BackendWelcomeMessage::on_show()
{
    HMILog log(__func__);
    m_frontend->set_property("visible", true);
}
void BackendWelcomeMessage::on_start()
{
    HMILog log(__func__);
    /* Start the animation for branding if it is needed */
    m_frontend->call("startAnimation");
}

void BackendWelcomeMessage::refresh()
{
}

void BackendWelcomeMessage::on_welcome_message_end()
{
    HMILog log(__func__);
    //m_chargerCore->on_welcome_message_end();
}
