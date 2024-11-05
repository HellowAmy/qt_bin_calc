
#include "wid_list.h"

wid_list::wid_list(QWidget *parent) : QListWidget(parent)
{
}

wid_list::~wid_list()
{
}

void wid_list::push_data(const QString &s)
{
    QListWidgetItem *it = new QListWidgetItem;
    it->setText(s);
    it->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    this->addItem(it);
}

void wid_list::bar_move_bottom()
{
    this->setCurrentRow(this->count()-1);
}
