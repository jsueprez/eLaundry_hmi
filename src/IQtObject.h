#pragma once

#include <QObject>
#include <QQuickItem>
#include <QVariant>

class IQtObject
{
public:
    virtual ~IQtObject() = default;

    /**
     * @brief Set real QObject
     */
    virtual void set_item(QObject *p_item) = 0;

    /**
     * @brief Return true if QQuickItem is null
     */
    virtual bool is_null() const = 0;

    /**
     * @brief Find child by object name
     */
    virtual QQuickItem* find_child(QString p_name) = 0;
    virtual QQuickItem* find_child(QString p_child, QString p_grandchild) = 0;

    /**
     * @brief Get property
     */
    virtual QVariant property(const char *p_property) const = 0;

    /**
     * @brief Set property
     */
    virtual void set_property(const char *p_property, const QVariant &p_value) = 0;
    virtual void set_property(const char *p_child, const char *p_property, const QVariant &p_value) = 0;

    /**
     * @brief Call QML function from C++
     */
    virtual void call(const char *p_function) const = 0;
    virtual void call(const char *p_function, QVariant p_arg1) const = 0;
    virtual void call(const char *p_function, QVariant p_arg1, QVariant p_arg2) const = 0;
};
