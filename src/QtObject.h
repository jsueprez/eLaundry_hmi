#pragma  once

#include "IQtObject.h"

class QtObject : public IQtObject
{
public:
    QtObject() = default;

    /**
     * @brief Inherited from IQtObject
     */
    void set_item(QObject *p_item) override final;

    /**
     * @brief Inherited from IQtObject
     */
    bool is_null() const override final;

    /**
     * @brief Inherited from IQtObject
     */
    QQuickItem *find_child(QString p_name) override final;
    QQuickItem *find_child(QString p_child, QString p_grandchild) override final;

    /**
     * @brief Inherited from IQtObject
     */
    QVariant property(const char *p_property) const override final;

    /**
     * @brief Inherited from IQtObject
     */
    void set_property(const char *p_property, const QVariant &p_value) override final;
    void set_property(const char *p_child, const char *p_property, const QVariant &p_value) override final;

    /**
     * @brief Inherited from IQtObject
     */
    void call(const char *p_function) const override final;
    void call(const char *p_function, QVariant p_arg1) const override final;
    void call(const char *p_function, QVariant p_arg1, QVariant p_arg2) const override final;

private:
    QObject *m_item = nullptr;
};
