#include <QGuiApplication>
#include <QtQml>

#include "HMILog.h"

#include <IQtObject.h>
#include <IGpioDriver.h>
#include <CRpiGpioDriver.h>
#include <BackendDashboard.h>
#include <BackendWelcome.h>
#include <NovaCore.h>
#include <QtObject.h>

void parse_arg(int argc, char **argv)
{
    for (int arg = 0; arg < argc; ++arg)
    {
        if (strcasecmp(argv[arg], "all") == 0)
        {
            HMILog::LOG_DEBUG = true;
            HMILog::LOG_ERROR = true;
            HMILog::LOG_INFO = true;
            HMILog::LOG_TRACE = true;
            HMILog::LOG_WARNING = true;
            continue;
        }

        if (strcasecmp(argv[arg], "debug") == 0)   { HMILog::LOG_DEBUG = true;   continue; }
        if (strcasecmp(argv[arg], "info") == 0)    { HMILog::LOG_INFO = true;    continue; }
        if (strcasecmp(argv[arg], "trace") == 0)   { HMILog::LOG_TRACE = true;   continue; }
        if (strcasecmp(argv[arg], "warning") == 0) { HMILog::LOG_WARNING = true; continue; }
        if (strcasecmp(argv[arg], "error") == 0)   { HMILog::LOG_ERROR = true;   continue; }
    }
}



int main(int argc, char **argv)
{
    parse_arg(argc, argv);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /* Create back-end objects */
    NovaCore novaCore;
    CRpiGpioDriver gpioDriver;

    QtObject appWindow;
    QtObject frontendDashboard;
    QtObject frontendWelcome;

    BackendDashboard backendDashboard;
    BackendWelcome backendWelcome;

    /* Set dependencies */
    backendDashboard.set_interface(&frontendDashboard, "IQtObject");
    backendDashboard.set_interface(&novaCore, "INovaCore");

    backendWelcome.set_interface(&frontendWelcome, "IQtObject");
    backendWelcome.set_interface(&novaCore, "INovaCore");

    novaCore.set_interface(&appWindow, "IQtObject");
    novaCore.set_interface(&gpioDriver, "IGpioDriver");
    novaCore.set_interface(&backendDashboard, "BackendDashboard");

    engine.rootContext()->setContextProperty("backendDashboard", &backendDashboard);
    engine.rootContext()->setContextProperty("backendWelcome", &backendWelcome);

    /* Load main front-end file */
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    appWindow.set_item(qobject_cast<QObject*>(engine.rootObjects().first()));

    app.installEventFilter(&novaCore);
    novaCore.init();

    return app.exec();
}
