#pragma once

#include <QObject>

#include "IBackend.h"
#include "IQtObject.h"

#include "INovaCore.h"

class BackendWelcome : public IBackend
{
    Q_OBJECT

public:
    BackendWelcome() = default;

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
    Q_INVOKABLE void refresh() override final;

    /**
     * @brief Inherited from IBackend
     */
    void on_start() override final;

    /**
     * @brief
     */
    Q_INVOKABLE void on_welcome_animation_end();

private:
    /**
     * @brief Charger core pointer
     */
    INovaCore *m_novaCore  = nullptr;

    /**
     * @brief Front-end pointer
     */
    IQtObject *m_frontend = nullptr;
};
