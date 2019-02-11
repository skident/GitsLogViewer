#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "LogParser.h"

void run()
{
    LogParser parser;
    parser.parse("/Users/skident/Documents/Projects/LiveCoding/GitsLogViewer/resources/MyLog.txt"); // TODO: remove hardcoded path
}


int main(int argc, char *argv[])
{
    run();
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
}
