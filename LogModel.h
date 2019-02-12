#pragma once

#include "LogLine.h"

#include <QList>
#include <QAbstractListModel>

class LogModel : public QAbstractListModel
{
    Q_OBJECT

    QList<LogLine> m_lines;

    enum LogRoles
    {
        TimestampRole = Qt::UserRole + 1,
        ThreadIdRole,
        SeverityRole,
        MessageRole,
    };

public:
    void reset(const QList<LogLine>& logs)
    {
        m_lines = logs;
        dataChanged(createIndex(0, 0), createIndex(rowCount()-1, 0));
    }

    void add(const LogLine& line)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_lines << line;
        endInsertRows();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        (void)parent; // unused
        return m_lines.count();
    }

    QVariant data(const QModelIndex& index, int role) const override
    {
        if (index.row() < 0 || index.row() > m_lines.count())
        {
            return QVariant();
        }

        const LogLine& line = m_lines[index.row()];
        switch (role)
        {
        case TimestampRole:
            return line.timestamp();

        case ThreadIdRole:
            return line.threadId();

        case SeverityRole:
            return line.severity();

        case MessageRole:
            return line.message();

        default:
            break;
        }

        return QVariant();
    }

    Q_INVOKABLE void orderBy(int column)
    {
        Comparator::Field field = static_cast<Comparator::Field>(column);

        // order by timestamp first
        if (field != Comparator::Field::Timestamp)
        {
            std::sort(m_lines.begin(), m_lines.end(),
                      [](const LogLine& lhs, const LogLine& rhs){ return Comparator::compare(lhs, rhs, Comparator::Field::Timestamp); });
        }

        // order by selected field
        std::sort(m_lines.begin(), m_lines.end(),
                  [field](const LogLine& lhs, const LogLine& rhs){ return Comparator::compare(lhs, rhs, field); });
        dataChanged(createIndex(0, 0), createIndex(rowCount()-1, 0));
    }

protected:
    QHash<int, QByteArray> roleNames() const override
    {
        static const QHash<int, QByteArray> roles =
        {
            {TimestampRole, "timestamp"},
            {ThreadIdRole, "threadId"},
            {SeverityRole, "severity"},
            {MessageRole, "message"}
        };

        return roles;
    }

private:

};
