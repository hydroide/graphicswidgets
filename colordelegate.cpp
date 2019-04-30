#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "colordelegate.h"

ColorDelegate::ColorDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

QWidget *ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto widget = new QColorDialog(parent);
//    widget->setWindowFlags(Qt::Widget);
    widget->setOptions(
//                QColorDialog::ShowAlphaChannel |
//                       QColorDialog::NoButtons |
                       QColorDialog::DontUseNativeDialog);
    return widget;
}

void ColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QColor value = index.model()->data(index, Qt::BackgroundRole).value<QColor>();
    auto *widget = static_cast<QColorDialog*>(editor);
    widget->setCurrentColor(value);
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto *widget = static_cast<QColorDialog*>(editor);
    QColor value = widget->currentColor();
    model->setData(index, value, Qt::BackgroundRole);
}

void ColorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
