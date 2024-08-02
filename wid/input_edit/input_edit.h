
#ifndef INPUT_EDIT_H
#define INPUT_EDIT_H

#include <QWidget>
#include <QLineEdit>

class input_edit : public QLineEdit
{
    Q_OBJECT
public:
    input_edit(QWidget *parent = nullptr);
    ~input_edit();

signals:

protected:

private:

};
#endif // INPUT_EDIT_H
