#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "HMILog.h"

//#include "IQtObject.h"
//#include "BackendDashboard.h"

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



int main(int argc, char *argv[])
{
    parse_arg(argc, argv);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    /*QtObject appWindow;
    QtObject frontendDashboard;

    BackendDashboard backendDashboard;

    backendDashboard.set_interface(&frontendDashboard, "IQtObject");

    engine.rootContext()->setContextProperty("backendDashboard", &backendDashboard);*/
    /* Load main front-end file */
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //appWindow.set_item(qobject_cast<QObject*>(engine.rootObjects().first()));

    return app.exec();
}
