#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QtWidgets>

/**
 * @brief The ColorDelegate class, 颜色选择器代理
 */
class ColorDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ColorDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COLORDELEGATE_H
