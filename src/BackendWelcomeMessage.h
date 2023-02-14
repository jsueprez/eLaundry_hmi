#pragma once

#include <QObject>

#include "IBackend.h"
#include "IQtObject.h"

//#include "IChargerCore.h"

class BackendWelcomeMessage : public IBackend
{
    Q_OBJECT

public:
    BackendWelcomeMessage() = default;

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
    Q_INVOKABLE void on_welcome_message_end();

    /**
     * @brief Inherited from IBackend
     */
    void on_start() override final;

private:
    /**
     * @brief Charger core pointer
     */
    //IChargerCore *m_chargerCore  = nullptr;

    /**
     * @brief Front-end pointer
     */
    IQtObject *m_frontend = nullptr;

    /**
     * @brief Last iteration value for pers_image
     */
    std::string m_logged_userName = "ELaundry";
};
