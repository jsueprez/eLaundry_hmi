#include "QtObject.h"

#include <QQuickItem>
#include <assert.h>

void QtObject::set_item(QObject *p_item)
{
    assert(p_item);
    m_item = p_item;
}

bool QtObject::is_null() const
{
    return m_item == nullptr;
}

QQuickItem *QtObject::find_child(QString p_name)
{
    return m_item->findChild<QQuickItem*>(p_name);
}

QQuickItem *QtObject::find_child(QString p_child, QString p_grandchild)
{
    return m_item->findChild<QQuickItem*>(p_child)->findChild<QQuickItem*>(p_grandchild);
}

QVariant QtObject::property(const char *p_property) const
{
    return m_item->property(p_property);
}

void QtObject::set_property(const char *p_property, const QVariant &p_value)
{
    m_item->setProperty(p_property, p_value);
}

void QtObject::set_property(const char *p_child, const char *p_property, const QVariant &p_value)
{
    auto child = m_item->findChild<QQuickItem*>(p_child);
    assert(child);

    child->setProperty(p_property, p_value);
}

void QtObject::call(const char *p_function) const
{
    QMetaObject::invokeMethod(m_item, p_function);
}

void QtObject::call(const char *p_function, QVariant p_arg1) const
{
    QMetaObject::invokeMethod(m_item, p_function, Q_ARG(QVariant, p_arg1));
}

void QtObject::call(const char *p_function, QVariant p_arg1, QVariant p_arg2) const
{
    QMetaObject::invokeMethod(m_item, p_function, Q_ARG(QVariant, p_arg1), Q_ARG(QVariant, p_arg2));
}
