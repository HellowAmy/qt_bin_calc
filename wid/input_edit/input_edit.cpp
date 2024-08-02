
#include "input_edit.h"

input_edit::input_edit(QWidget *parent) : QLineEdit(parent)
{
    this->setObjectName("QLineEditInputEdit");
    this->setAlignment(Qt::AlignRight);
}

input_edit::~input_edit()
{
}