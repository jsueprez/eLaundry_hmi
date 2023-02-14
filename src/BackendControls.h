#pragma once

#include <QObject>

#include "IBackend.h"
#include "IQtObject.h"
//#include "IWallbox.h"

//#include "IChargerCore.h"

class BackendControls : public IBackend
{
    Q_OBJECT

public:
    BackendControls() = default;

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

private:

    /**
     * @brief Front-end pointer
     */
    IQtObject *m_frontend = nullptr;

    /**
     * @brief Charger core pointer
     */
    //IChargerCore *m_chargerCore  = nullptr;
};
