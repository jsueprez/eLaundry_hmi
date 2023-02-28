#include "BackendDashboard.h"

#include <QStandardItemModel>
#include <QTime>

#include "CardNovaLocker.h"
#include "HMILog.h"

BackendDashboard::BackendDashboard()
{
    m_model = new QStandardItemModel(0, 1, this);
}

void BackendDashboard::set_interface(void *p_interface, const char *p_class)
{
    if (strcmp(p_class, "IQtObject") == 0)
    {
        m_frontend = reinterpret_cast<IQtObject*>(p_interface);
    }
    else if (strcmp(p_class, "INovaCore") == 0)
    {
        m_novaCore = reinterpret_cast<INovaCore*>(p_interface);
    }
    else if (strcmp(p_class, "INovaDB") == 0)
    {
        m_novaDB = reinterpret_cast<INovaDB*>(p_interface);
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
    assert(m_novaDB);

    // TODO: This should be a shared memory and not query in multiple sources
    m_novaLockers = m_novaDB->get_all_novaLockers();

    insert_novaLockers();

}

void BackendDashboard::on_hide()
{
}

void BackendDashboard::on_show()
{
    HMILog log(__func__);
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

void BackendDashboard::insert_novaLockers()
{
    HMILog log(__func__);

    for (auto &item : m_novaLockers)
    {
        const int row = m_model->rowCount();

        m_model->insertRow(row);
        set_row_data(item, row);
    }
}

void BackendDashboard::remove_novaLockers()
{
    HMILog log(__func__);

    for (auto &item : m_novaLockers)
    {
        auto row = find_row(item.id);

        if (row >= 0)
        {
            m_model->removeRow(row);
        }
        else
        {
            log.error("Id not found while removing user", item.id);
        }
    }
}

void BackendDashboard::update_lock_state(QString p_novaLockerId, QString p_state)
{
    HMILog log(__func__);

    auto index = p_novaLockerId.toInt() - 1;

    //TODO: This is ugly please fix or refactor
    if(m_novaLockers[index].locked == true)
    {
        m_novaLockers[index].locked = false;
    }
    else
    {
        m_novaLockers[index].locked = true;
    }

    auto row = find_row(p_novaLockerId.toInt());
    if (row >= 0)
    {
        set_row_data(m_novaLockers[index], row);
    }
    else
    {
        log.error("Id not found while updating user", index);
    }

}

int BackendDashboard::find_row(int p_userId) const
{
    for (int row = 0; row < m_model->rowCount(); ++row)
    {
        auto userId = m_model->data(m_model->index(row, 0), Qt::DisplayRole).value<CardNovaLocker>().m_novaLockerId;
        if (userId == p_userId) return row;
    }

    return -1;
}

void BackendDashboard::set_row_data(const NovaLocker &p_novaLocker, int p_row)
{
    HMILog log(__func__);

    std::vector<std::string> lines;

    lines.push_back(std::to_string(p_novaLocker.id));
    lines.push_back(std::to_string(p_novaLocker.locked));
    lines.push_back(p_novaLocker.type);

    CardNovaLocker card;
    card.m_novaLockerId = p_novaLocker.id;

    if (!lines.empty())
    {
        card.m_line1 = QString::fromStdString(lines.back());
        lines.pop_back();
    }

    if (!lines.empty())
    {
        card.m_line2 = QString::fromStdString(lines.back());
        lines.pop_back();
    }

    if (!lines.empty())
    {
        card.m_line3 = QString::fromStdString(lines.back());
        lines.pop_back();
    }

    m_model->setData(m_model->index(p_row, 0), QVariant::fromValue(card), Qt::DisplayRole);
}

