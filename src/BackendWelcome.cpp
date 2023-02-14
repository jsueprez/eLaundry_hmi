#include "BackendWelcome.h"

#include <sys/types.h>
#include <sys/stat.h>

#include "HMILog.h"

#define FOLDER "/home/root/.wallbox/"

void BackendWelcome::set_interface(void *p_interface, const char *p_class)
{
    if (strcmp(p_class, "IQtObject") == 0)
    {
        m_frontend = reinterpret_cast<IQtObject*>(p_interface);
    }
    else if (strcmp(p_class, "INovaCore") == 0)
    {
        m_novaCore = reinterpret_cast<INovaCore*>(p_interface);
    }
    else
    {
        assert(0);
    }
}

void BackendWelcome::set_frontend(QQuickItem *p_frontend)
{
    m_frontend->set_item(p_frontend);
}

void BackendWelcome::init()
{
}

void BackendWelcome::on_hide()
{
}

void BackendWelcome::on_show()
{
}
void BackendWelcome::on_start()
{
}

void BackendWelcome::refresh()
{
}

void BackendWelcome::on_welcome_animation_end()
{
    HMILog log(__func__);
    m_novaCore->on_welcome_animation_end();
}
