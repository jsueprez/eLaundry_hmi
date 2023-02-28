#pragma once

#include <QObject>

struct CardNovaLocker
{
    Q_GADGET

    Q_PROPERTY(QString line1 MEMBER m_line1 CONSTANT)
    Q_PROPERTY(QString line2 MEMBER m_line2 CONSTANT)
    Q_PROPERTY(QString line3 MEMBER m_line3 CONSTANT)

    Q_PROPERTY(int novaLockerId MEMBER m_novaLockerId CONSTANT)

public:
    QString m_line1;
    QString m_line2;
    QString m_line3;

    int m_novaLockerId;
};

