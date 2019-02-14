#pragma once

#include <QObject>
#include <QUrl>
#include <QString>

#include "LogParser.h"
#include "LogModel.h"


class AppController : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void openFile(const QUrl& filepath)
    {
        openFile(filepath.toLocalFile());
    }

    void openFile(const QString& filepath)
    {
        QList<LogLine> logs = parser.parse(filepath.toStdString());
        model.reset(logs);
    }

    LogModel& logModel()
    {
        return model;
    }

private:
    LogModel model;
    LogParser parser;


};
