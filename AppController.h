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
        m_filename = filepath;

        QList<LogLine> logs = parser.parse(filepath.toStdString());
        model.reset(logs);
    }

    LogModel& logModel()
    {
        return model;
    }

    Q_INVOKABLE void setRegex(const QString& regex)
    {
        parser.setRegex(regex.toStdString());
        openFile(m_filename);
    }

private:
    LogModel model;
    LogParser parser;
    QString m_filename;

};
