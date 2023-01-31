#pragma once

#include <assert.h>
#include <QQuickItem>

#include <QObject>

#define ARG_UNUSED(X)

class IBackend : public QObject
{
public:
    virtual ~IBackend() = default;

    /**
     * @brief Set interface pointers.
     */
    virtual void set_interface(void *p_interface, const char *p_class) = 0;

    /**
     * @brief Set pointer to front-end object
     */
    virtual void set_frontend(QQuickItem *p_frontend) = 0;

    /**
     * @brief Initialize back-end services, threads, variables, etc
     */
    virtual void init() = 0;

    /**
     * @brief Function called when the front-end counterpart becomes invisible
     */
    virtual void on_hide() = 0;

    /**
     * @brief Function called when the front-end counterpart becomes visible
     */
    virtual void on_show() = 0;

    /**
     * @brief Refresh information on front-end
     */
    virtual void refresh() = 0;

    /**
     * @brief start animation standalone in front-end information on front-end
     */
    virtual void on_start() = 0;
};
