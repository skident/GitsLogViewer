#pragma once

#include <QString>

class LogLine
{
    QString m_timestamp;
    QString m_threadId;
    QString m_severity;
    QString m_message;

public:
    LogLine(const QString& timestamp,
            const QString& threadId,
            const QString& severity,
            const QString& message)
        : m_timestamp(timestamp)
        , m_threadId(threadId)
        , m_severity(severity)
        , m_message(message)
    {

    }

    LogLine() = default;

    QString timestamp() const
    {
        return m_timestamp;
    }

    QString threadId() const
    {
        return m_threadId;
    }

    QString severity() const
    {
        return m_severity;
    }

    QString message() const
    {
        return m_message;
    }
};

struct Comparator
{
    enum class Field
    {
        Timestamp,
        ThreadId,
        Severity,
        Message,
    };

    static bool compare(const LogLine& lhs, const LogLine& rhs, const Field field = Field::Timestamp)
    {
        switch (field)
        {
        case Field::ThreadId:
            return lhs.threadId() < rhs.threadId();

        case Field::Severity:
            return lhs.severity() < rhs.severity();

        case Field::Message:
            return lhs.message() < rhs.message();

        default:
            break;
        }
        return lhs.timestamp() < rhs.timestamp();
    }
};
