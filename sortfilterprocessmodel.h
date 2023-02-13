#ifndef SORTFILTERPROCESSMODEL_H
#define SORTFILTERPROCESSMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "processmodel.h"

class SortFilterProcessModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(ProcessModel *processModel READ processModel CONSTANT)
    Q_PROPERTY(QString filterText READ getFilterText WRITE setFilterText NOTIFY filterTextChanged)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    SortFilterProcessModel(QObject *parent = nullptr);

    ProcessModel *processModel() {return &m_processModel;}
    Q_INVOKABLE void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    int columnCount(const QModelIndex &parent) const override;
    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);
    Q_INVOKABLE Qt::SortOrder initialSortOrder(int column) const;
    Q_INVOKABLE void reorderColumn(int col, int x);

    //оригінальна модель, яка містить дані в довільному порядку
//бере значення індексу, які є в оригінальній моделі і повертає значення індексу, які відображаються в таблиці
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
    //бере значення індексу, які відображаються в таблиці і повертає оригінальні значення індексу які закладені в моделі
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;

    QString getFilterText() const;
    void setFilterText(const QString &newFilterText);

signals:
    void filterTextChanged(QString filterText);
private:
    ProcessModel m_processModel;
    QVector<ProcessModel::columnName> m_ColumnName;
    QString m_filterText;
};

#endif // SORTFILTERPROCESSMODEL_H
