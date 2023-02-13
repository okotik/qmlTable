#include <QDebug>
#include <QTimerEvent>
#include <QFont>
#include <QFontMetrics>
#include <QGuiApplication>
#include "processmodel.h"

/*-----------------------Global Variable START------------------------*/
//bool previous_flag_show_thread_prev = false; //previous state
//bool flag_show_thread = false; //too see informations on thread level
//int flag_thread_ok = true; //we presume a kernel 2.6.x using NPTL
//bool flag_session_start = false;
//bool flag_start_mini = false; // Need for Xorg.Session
//bool flag_refresh = true; // DEL
//bool flag_xcompmgr = false; // DEL test.compiz..
//bool flag_devel = false;
//bool flag_shedstat = false;
//bool flag_smallscreen = false;
//bool flag_firstRun = true; // test
/*----------------------END Global Variables--------------------------*/

ProcessModel::ProcessModel(QObject *parrent) : QAbstractTableModel(parrent)
{
//    m_roleNames = QAbstractTableModel::roleNames();
//    m_roleNames.insert(int(ProcessModel::Role::Sort), QByteArray("sort"));
//    m_roleNames.insert(int(ProcessModel::Role::Number), QByteArray("number"));
//    m_roleNames.insert(int(ProcessModel::Role::Type), QByteArray("type"));
    for(int i = 0; i < 100; ++i)
    {
        Person person;
        person.SELECT = false;
        person.ID = i;
        person.IC = i * 37 + 1;
        person.Type = i * 25 + 1;
        person.Name = "Orest" + QString::number(i);
        person.ControlCard = i/3.0f;
        person.Gender = i % 2 != 0 ? "Male" : "Famale";
        person.Avatar = "foto";
        person.Time = i * 328;
        person.Birthday = i * 741;
        person.CertType = 1880004 / (i+1);
        person.IDNumber = 1990004 / (i+1);
        person.PhoneNumber = 2990004 / (i+1);;
        person.Nation = "UA";
        person.City = i % 3 != 0 ? "Lviv" : "Kyiv";
        person.Address = i % 3 != 0 ? "Topolna" : "Troeshchina";
        person.Note = i % 7 != 0 ? "Good" : "Bad";;
        m_persons.push_back(person);
    }
    //insertFieldRoles();
    update();
    m_tinerId = startTimer(5000);
}

QHash<int, QByteArray> ProcessModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles = QAbstractTableModel::roleNames();
    roles[(int)ProcessModel::Role::TypeRole] = "type";
    roles[Qt::DisplayRole] = "display";
    roles[Qt::EditRole] = "edit";
    roles[(int)ProcessModel::Role::Sort] ="sort";
    roles[(int)ProcessModel::Role::Number] = "number";
    roles[(int)ProcessModel::Role::Type] = "type";
    return roles;
}

int ProcessModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_persons.count();
}

int ProcessModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return columnName::columnNameSize;
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if(index.column() >= columnName::columnNameSize)
        return QVariant();
    columnName currentColumnName = columnName(index.column());

    switch (role) {
    case Qt::DisplayRole:       
    {
        switch (index.column()) {

        case columnName::SELECT:
            return false;
        case columnName::ID:
            return m_persons.at(index.row()).ID;
        case columnName::IC:
            return m_persons.at(index.row()).IC;
        case columnName::Type:
            return m_persons.at(index.row()).Type;
        case columnName::Name:
            return m_persons.at(index.row()).Name;
        case columnName::ControlCard:
            return m_persons.at(index.row()).ControlCard;
        case columnName::Gender:
            return m_persons.at(index.row()).Gender;
        case columnName::Avatar:
            return m_persons.at(index.row()).Avatar;
        case columnName::Time:
            return m_persons.at(index.row()).Time;
        case columnName::Birthday:
            return m_persons.at(index.row()).Birthday;
        case columnName::CertType:
            return m_persons.at(index.row()).CertType;
        case columnName::IDNumber:
            return m_persons.at(index.row()).IDNumber;
        case columnName::PhoneNumber:
            return m_persons.at(index.row()).PhoneNumber;
        case columnName::Nation:
            return m_persons.at(index.row()).Nation;
        case columnName::City:
            return m_persons.at(index.row()).City;
        case columnName::Address:
            return m_persons.at(index.row()).Address;
        case columnName::Note:
            return m_persons.at(index.row()).Note;
        }
    }
    case Qt::InitialSortOrderRole:
        return Qt::AscendingOrder;
    case int (ProcessModel::Role::Sort):
        return true;
    case int (ProcessModel::Role::Number):
        return m_persons[index.row()].ControlCard;
    case int (ProcessModel::Role::Type):
        switch(currentColumnName)
        {
        case ControlCard:
            return QLatin1String("%");
//        case F_PID:
//        case F_SID:
//        case F_TPGID:
//        case F_EUID:
//        case F_SUID:
//        case F_FSUID:
//        case F_SGID:
//            return QLatin1String("id");
//        case F_SIZE:
//        case F_RSS:
//        case F_TRS:
//        case F_DRS:
//        case F_STACK:
//        case F_SHARE:
//        case F_IOW:
//        case F_IOR:
//            return QLatin1String("size");
        case ID:
        case IC:
        case Type:
        case Time:
        case Birthday:
        case CertType:
        case IDNumber:
        case PhoneNumber:
            return QLatin1String("int");
        case SELECT:
            return QLatin1String("flags");
        default:
            return QLatin1String("string");
        }

    default:
        if(role >= int(Role::FirstDataRole))
            // convert the data role to a column and get the DisplayRole
            return data(QAbstractTableModel::index(index.row(), role - int(Role::FirstDataRole)), Qt::DisplayRole);
        return QVariant();
    }

    //    Category::string() is pre-existing functionality so we can avoid doing a switch like this:
    //        switch(field)
    //    {
    //        case F_PID:
    //            return pid;
    //        case F_USER:
    //            return pi->username;
    //        case F_CMD:
    //            return pi->command;
    //        default:
    //            return QString();
    //        }
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case columnName::SELECT:
            return qtTrId("");
        case columnName::ID:
            return qtTrId("devices.settings.std.id");
        case columnName::IC:
            return qtTrId("devices.settings.std.ic");
        case columnName::Type:
            return qtTrId("devices.settings.std.type");
        case columnName::Name:
            return qtTrId("devices.settings.std.name");
        case columnName::ControlCard:
            return qtTrId("devices.settings.std.accn");
        case columnName::Gender:
            return qtTrId("devices.settings.std.gender");
        case columnName::Avatar:
            return qtTrId("devices.settings.std.photo");
        case columnName::Time:
            return qtTrId("devices.settings.std.reg_time");
        case columnName::Birthday:
            return qtTrId("devices.settings.std.birthday");
        case columnName::CertType:
            return qtTrId("devices.settings.std.cert_type");
        case columnName::IDNumber:
            return qtTrId("devices.settings.std.id_number");
        case columnName::PhoneNumber:
            return qtTrId("devices.settings.std.phone_number");
        case columnName::Nation:
            return qtTrId("devices.settings.std.nation");
        case columnName::City:
            return qtTrId("devices.settings.std.city");
        case columnName::Address:
            return qtTrId("devices.settings.std.address");
        case columnName::Note:
            return qtTrId("devices.settings.std.note");

        default:
            return QVariant();
        }
    }
    return QVariant();
}

int ProcessModel::columnWidth(int c, const QFont *font)
{
    if(!m_columnWidths[c])
    {
        QFontMetrics defaultFontMetrics = QFontMetrics(QGuiApplication::font());
        QFontMetrics fm = (font ? QFontMetrics (*font) : defaultFontMetrics);
        int ret = fm.horizontalAdvance(headerData(c, Qt::Horizontal, Qt::DisplayRole).toString() + QLatin1String(" ^")) + 8;
        for (int r = 0; r < m_persons.count(); ++r)
            ret = qMax(ret, fm.horizontalAdvance(m_persons[0].Name));
        m_columnWidths[c] = ret;
    }
    return m_columnWidths[c];
}

void ProcessModel::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_tinerId)
        update();
}

//void ProcessModel::insertFieldRoles()
//{
//    int fdr = int(Role::FirstDataRole);
//    m_roleNames.insert(fdr + F_PID, QByteArray("pid"));
//    m_roleNames.insert(fdr + F_SID, QByteArray("sid"));
//    m_roleNames.insert(fdr + F_TPGID, QByteArray("tpgid"));
//    m_roleNames.insert(fdr + F_EUID, QByteArray("euid"));
//    m_roleNames.insert(fdr + F_SUID, QByteArray("suid"));
//    m_roleNames.insert(fdr + F_FSUID, QByteArray("fsuid"));
//    m_roleNames.insert(fdr + F_SGID, QByteArray("sgid"));
//    m_roleNames.insert(fdr + F_PRI, QByteArray("pri"));
//    m_roleNames.insert(fdr + F_NICE, QByteArray("nice"));
//    m_roleNames.insert(fdr + F_RPRI, QByteArray("rpri"));
//    m_roleNames.insert(fdr + F_MAJFLT, QByteArray("majflt"));
//    m_roleNames.insert(fdr + F_MINFLT, QByteArray("minflt"));
//    m_roleNames.insert(fdr + F_SIZE, QByteArray("size"));
//    m_roleNames.insert(fdr + F_RSS, QByteArray("rss"));
//    m_roleNames.insert(fdr + F_FLAGS, QByteArray("flags"));
//    m_roleNames.insert(fdr + F_WCPU, QByteArray("wcpu"));
//    m_roleNames.insert(fdr + F_CPU, QByteArray("cpu"));
//    m_roleNames.insert(fdr + F_PMEM, QByteArray("pmem"));
//    m_roleNames.insert(fdr + F_CMDLINE, QByteArray("cmdline"));
//}

void ProcessModel::update()
{
    beginResetModel();
    //TODO complete this: tell which rows are inserted and which are removed
    //beginInsertRows(QModelIndex(), 0, 0);
//    m_proc.refresh();
//    m_pids = m_proc.procs.keys().toVector();
//    std::sort(m_pids.begin(), m_pids.end());
    //endInsertRows();
    endResetModel();
}
