#include "BackendControlsUI.h"

#include <QTime>
#include "HMILog.h"

void BackendControlsUI::set_interface(void *p_interface, const char *p_class)
{
    if (strcmp(p_class, "IQtObject") == 0)
    {
        m_frontend = reinterpret_cast<IQtObject*>(p_interface);
    }
    else
    {
        assert(0);
    }
}

void BackendControlsUI::set_frontend(QQuickItem *p_frontend)
{
    m_frontend->set_item(p_frontend);
}

void BackendControlsUI::init()
{
}

void BackendControlsUI::on_hide()
{
}

void BackendControlsUI::on_show()
{
}

void BackendControlsUI::on_start()
{
}

void BackendControlsUI::refresh()
{
}

QString BackendControlsUI::now() const
{
    return QTime::currentTime().toString("hh:mm");
}
