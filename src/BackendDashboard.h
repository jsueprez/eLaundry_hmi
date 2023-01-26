#pragma once

#include <QObject>

#include "IBackend.h"
#include "IQtObject.h"
//#include "IWallbox.h"

//#include "IChargerCore.h"

class BackendDashboard : public IBackend
{
    Q_OBJECT

public:
    BackendDashboard() = default;

    /**
     * @brief Inherited from IBackend
     */
    void set_interface(void *p_interface, const char *p_class) override final;

    /**
     * @brief Inherited from IBackend
     */
    Q_INVOKABLE void set_frontend(QQuickItem *p_frontend) override final;

    /**
     * @brief Inherited from IBackend
     */
    void init() override final;

    /**
     * @brief Inherited from IBackend
     */
    Q_INVOKABLE void on_hide() override final;

    /**
     * @brief Inherited from IBackend
     */
    Q_INVOKABLE void on_show() override final;

    /**
     * @brief Inherited from IBackend
     */
    void refresh() override final;

    /**
     * @brief Inherited from IBackend
     */
    void on_start() override final;

    /**
     * @brief Inherited from IBackend
     */
    Q_INVOKABLE void on_locked_end();

    /**
     * @brief Inherited from IBackend
     */
    Q_INVOKABLE void on_play_end() ;

    /**
     * @brief Inherited from IBackend
     */
    Q_INVOKABLE void on_pause_end() ;

private:

    /**
     * @brief Format value to a 'presentable' number
     */
    QString format(double p_value) const;

    /**
     * @brief Front-end pointer
     */
    IQtObject *m_frontend = nullptr;

    /**
     * @brief Charger core pointer
     */
    //IChargerCore *m_chargerCore  = nullptr;
};
