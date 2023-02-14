#include "BackendControls.h"

#include <QTime>
#include "HMILog.h"

void BackendControls::set_interface(void *p_interface, const char *p_class)
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

void BackendControls::set_frontend(QQuickItem *p_frontend)
{
    m_frontend->set_item(p_frontend);
}

void BackendControls::init()
{
}

void BackendControls::on_hide()
{
}

void BackendControls::on_show()
{
}

void BackendControls::on_start()
{

}

void BackendControls::refresh()
{
}

