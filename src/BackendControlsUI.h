#pragma once

#include <QObject>

#include "IBackend.h"
#include "IQtObject.h"

class BackendControlsUI : public IBackend
{
    Q_OBJECT

public:
    BackendControlsUI() = default;

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
    Q_INVOKABLE void on_start() override final;

    /**
     * @brief Inherited from IBackend
     */
    void refresh() override final;

    /**
     * @brief Return current system time formatted as hh:mm
     */
    Q_INVOKABLE QString now() const;

private:
    /**
     * @brief Front-end pointer
     */
    IQtObject *m_frontend = nullptr;
};
