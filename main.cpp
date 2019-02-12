#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "LogParser.h"
#include "LogModel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    LogModel model;
    LogParser parser;
    QList<LogLine> logs = parser.parse("/Users/skident/Documents/Projects/LiveCoding/GitsLogViewer/resources/MyLog.txt"); // TODO: remove hardcoded path

    model.reset(logs);

    engine.rootContext()->setContextProperty("LogModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
