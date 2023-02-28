#pragma once

#include <QObject>
#include <QAbstractItemModel>

#include "IBackend.h"
#include "IQtObject.h"

#include "INovaCore.h"
#include "INovaDb.h"

class BackendDashboard : public IBackend
{
    Q_OBJECT

    Q_PROPERTY(QAbstractItemModel* model MEMBER m_model CONSTANT)

public:
    BackendDashboard();

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

    /**
     * @brief Login with userId and PIN
     * @return +2 if user and pin are valid and user is admin
     *         +1 if user and pin are valid and user is not admin
     *         -1 if user is unknown
     *         -2 if PIN is incorrect
     */
    Q_INVOKABLE void update_lock_state(QString p_novaLockerId, QString p_state);
//    /void update_lock_state(const int p_novaLockerId, const int p_state);

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
     * @brief Model for NovaLockers list
     */
    QAbstractItemModel *m_model = nullptr;

    /**
     * @brief Nova core pointer
     */
    INovaCore *m_novaCore   = nullptr;

    /**
     * @brief Nova DB pointer
     */
    INovaDB *m_novaDB       = nullptr;

    std::vector<NovaLocker> m_novaLockers;

    /**
     * @brief Apply modifications to model
     */
    void insert_novaLockers();
    void remove_novaLockers();

    /**
     * @brief Find row by variable name inside model
     * @return Return row number or -1, if variable does not exist
     */
    int find_row(int p_userId) const;

    /**
     * @brief Set data in model
     */
    void set_row_data(const NovaLocker &p_novaLocker, int p_row);

};
