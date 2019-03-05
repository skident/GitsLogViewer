#pragma once

#include "LogLine.h"

#include <QList>
#include <QAbstractListModel>

struct RoleInfo
{
    int id;
    QString roleName;
    QString title;
};

class RolesContainer
{
    std::vector<RoleInfo> m_roles;

public:
    void clear()
    {
        m_roles.clear();
    }

    void add(const RoleInfo& info)
    {
        m_roles.emplace_back(info);
    }

    RoleInfo getById(const int id) const
    {
        for (const auto& elem : m_roles)
        {
            if (elem.id == id)
            {
                return elem;
            }
        }
        return {};
    }

    RoleInfo getByRoleName(const QString& roleName) const
    {
        for (const auto& elem : m_roles)
        {
            if (elem.roleName == roleName)
            {
                return elem;
            }
        }
        return {};
    }

    RoleInfo getByRoleTitle(const QString& title) const
    {
        for (const auto& elem : m_roles)
        {
            if (elem.title == title)
            {
                return elem;
            }
        }
        return {};
    }

    void updateTitles(const QVariantMap& roleToTitleMap)
    {
        for (auto& elem : m_roles)
        {
            auto it = roleToTitleMap.find(elem.roleName);
            if (it != roleToTitleMap.end())
            {
                elem.title = it.value().toString();
            }
        }
    }

    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> hash;
        for (const auto& elem : m_roles)
        {
            hash.insert(elem.id, elem.roleName.toUtf8());
        }
        return hash;
    }

    QStringList titles() const
    {
        QStringList titles;
        for (const auto& elem : m_roles)
        {
            titles << elem.title;
        }
        return titles;
    }
};


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
        m_rolesContainer.clear();

        int rolesCount = logs.at(0).m_line.size(); // count of elements in on log line
        for (int i = 1; i <= rolesCount; i++)
        {
            int roleId = Qt::UserRole + i;
            QString roleName = "Column #" + QString::number(i);

            m_rolesContainer.add({roleId, roleName, roleName});
        }

        beginResetModel();
        m_lines = logs;
        endResetModel();

        emit modelReloaded();
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
        RoleInfo info = m_rolesContainer.getByRoleTitle(columnName);
        int idx = info.id % (Qt::UserRole + 1);

        std::sort(m_lines.begin(), m_lines.end(),
                  [idx](const LogLine& lhs, const LogLine& rhs){ return lhs.m_line[idx] < rhs.m_line[idx]; });

        dataChanged(createIndex(0, 0), createIndex(rowCount()-1, 0));
    }

    QStringList titles() const
    {
        return m_rolesContainer.titles();
    }

    Q_INVOKABLE void updateTitles(const QVariantMap& roleToTitleMap)
    {
        m_rolesContainer.updateTitles(roleToTitleMap);
        emit titlesChanged();
    }

    Q_INVOKABLE QString getTitle(const QString& roleName) const
    {
        return m_rolesContainer.getByRoleName(roleName).title;
    }

signals:
    void titlesChanged();
    void modelReloaded();

protected:
    QHash<int, QByteArray> roleNames() const override
    {
        return m_rolesContainer.roleNames();
    }

private:
    QList<LogLine> m_lines;
//    QHash<int, QByteArray> m_rolesMap;
    RolesContainer m_rolesContainer;
};
