#pragma once

#include "LogLine.h"

#include <QList>
#include <QAbstractListModel>

class LogModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList titles READ titles NOTIFY titlesChanged)

public:
    void reset(const QList<LogLine>& logs)
    {
        if (logs.empty())
        {
            return;
        }

        m_lines.clear();
        m_rolesMap.clear();

        int rolesCount = logs.at(0).m_line.size(); // count of elements in on log line
        for (int i = 1; i <= rolesCount; i++)
        {
            int roleId = Qt::UserRole + i;
            QString roleName = "Column #" + QString::number(i);

            m_rolesMap.insert(roleId, roleName.toLocal8Bit());
        }

        beginResetModel();
        m_lines = logs;
        endResetModel();

        emit titlesChanged();
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
        int idx = role % (Qt::UserRole+1);
        if (idx < line.m_line.size())
        {
            return line.m_line[idx];
        }

        return {};
    }

    Q_INVOKABLE void orderBy(const QString& columnName)
    {
        int idx = 0;
        for (auto it = m_rolesMap.begin(); it != m_rolesMap.end(); ++it)
        {
            if (QString(it.value()) == columnName)
            {
                idx = it.key() % (Qt::UserRole + 1);
            }
        }
        std::sort(m_lines.begin(), m_lines.end(),
                  [idx](const LogLine& lhs, const LogLine& rhs){ return lhs.m_line[idx] < rhs.m_line[idx]; });

        dataChanged(createIndex(0, 0), createIndex(rowCount()-1, 0));
    }

    QStringList titles() const
    {
        QMap<int, QString> map;

        for (auto it = m_rolesMap.begin(); it != m_rolesMap.end(); ++it)
        {
            map.insert(it.key(), QString(it.value()));
        }

        return map.values();
    }

signals:
    void titlesChanged();

protected:
    QHash<int, QByteArray> roleNames() const override
    {
        return m_rolesMap;
    }

private:
    QList<LogLine> m_lines;
    QHash<int, QByteArray> m_rolesMap;
};
