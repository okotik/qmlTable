#include "sortfilterprocessmodel.h"

SortFilterProcessModel::SortFilterProcessModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    setSourceModel(&m_processModel);

    m_ColumnName << ProcessModel::columnName::SELECT << ProcessModel::columnName::ID << ProcessModel::columnName::IC << ProcessModel::columnName::Type
                << ProcessModel::columnName::Name << ProcessModel::columnName::ControlCard
                << ProcessModel::columnName::Gender << ProcessModel::columnName::Avatar << ProcessModel::columnName::Time
                << ProcessModel::columnName::Birthday << ProcessModel::columnName::CertType
                << ProcessModel::columnName::IDNumber << ProcessModel::columnName::PhoneNumber
                << ProcessModel::columnName::Nation << ProcessModel::columnName::City
                << ProcessModel::columnName::Address << ProcessModel::columnName::Note;
}

void SortFilterProcessModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << column << m_ColumnName[column] << order;
    QSortFilterProxyModel::sort(m_ColumnName[column], order);
}

int SortFilterProcessModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_ColumnName.count();
}

int SortFilterProcessModel::columnWidth(int c, const QFont *font)
{
    if(c < 0 || c > m_ColumnName.count())
        return 0;

    return m_processModel.columnWidth(m_ColumnName[c], font);
}

Qt::SortOrder SortFilterProcessModel::initialSortOrder(int column) const
{
    Q_UNUSED(column)
    return Qt::AscendingOrder;
}

void SortFilterProcessModel::reorderColumn(int col, int x)
{
    int xc = columnWidth(0);
    int destCol = 0;
    while(xc < x && destCol < m_ColumnName.count())
        xc += columnWidth(++destCol); // assuming default font
    if(col == destCol)
        return;
    qDebug() << "reordering col " << col << headerData(col, Qt::Horizontal).toString() << "@" << x
             << "before" << destCol << headerData(destCol, Qt::Horizontal).toString() << "@" << xc;

    beginMoveColumns(QModelIndex(), col, col, index(0, destCol), destCol);
    m_ColumnName.insert(destCol, m_ColumnName.takeAt(col));
    endMoveColumns();
}

QModelIndex SortFilterProcessModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    int row = QSortFilterProxyModel::mapFromSource(sourceIndex).row();
    ProcessModel::columnName field = ProcessModel::columnName(sourceIndex.column());
    return m_processModel.index(row, m_ColumnName.indexOf(field));
}

QModelIndex SortFilterProcessModel::mapToSource(const QModelIndex &proxyIndex) const
{
    QModelIndex rowIndex = QSortFilterProxyModel::mapToSource(proxyIndex);
    int col = -1;
    if(proxyIndex.column() >=0 && proxyIndex.column() < m_ColumnName.count())
        col = m_ColumnName[proxyIndex.column()];
    return m_processModel.index(rowIndex.row(), col);
}

QString SortFilterProcessModel::getFilterText() const
{
    return m_filterText;
}

void SortFilterProcessModel::setFilterText(const QString &newFilterText)
{
    if(m_filterText == newFilterText)
        return;
    m_filterText = newFilterText;
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRegularExpression(m_filterText);
    emit filterTextChanged(m_filterText);
}
