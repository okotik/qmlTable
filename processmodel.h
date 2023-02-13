#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H
#include <QAbstractTableModel>

class QFont;
struct Person
{
    bool SELECT = false;
    int ID;
    int IC;
    int Type;
    QString Name;
    float ControlCard;
    QString Gender;
    QString Avatar;
    int Time;
    int Birthday;
    int CertType;
    int IDNumber;
    int PhoneNumber;
    QString Nation;
    QString City;
    QString Address;
    QString Note;
};

class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcessModel)

public:
    enum class Role
    {
        TypeRole = Qt::UserRole + 1,
        Sort,
        Number,
        Type,
        FirstDataRole // here begins the data field roles
    };
    Q_ENUM(Role)

    enum columnName
        {
            SELECT = 0,
            ID,
            IC,
            Type,
            Name,
            ControlCard,
            Gender,
            Avatar,
            Time,
            Birthday,
            CertType,
            IDNumber,
            PhoneNumber,
            Nation,
            City,
            Address,
            Note,
            columnNameSize //it have to be last
        };

    ProcessModel(QObject *parrent = nullptr);
    QHash <int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);
    Q_INVOKABLE void update();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    //void insertFieldRoles();
    QVector<Person> m_persons;
    QVector<int> m_columnWidths = QVector<int>(columnNameSize);
    int m_tinerId;
};

#endif // PROCESSMODEL_H
