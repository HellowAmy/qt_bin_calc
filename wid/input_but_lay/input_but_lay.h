
#ifndef INPUT_BUT_LAY_H
#define INPUT_BUT_LAY_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include <vector>

static QString _E_BIN_ZERO_ = "0";
static QString _E_BIN_ONE_ = "1";
static QString _E_BIN_DISABLE_ = "-";

class input_but_lay : public QFrame
{
    Q_OBJECT
public:
    input_but_lay(QWidget *parent = nullptr);
    ~input_but_lay();


    void set_binary_ls(const QString &s);

    void set_binary_valid(const QString &s);

    void set_bit_size(int size);

    QString get_binary_ls();

    QString get_binary_valid();

    void clear_data_ls();

signals:
    void sn_click_pos(int pos,bool val);

protected:

private:
    std::vector<QPushButton*> _vec_but;

};
#endif // INPUT_BUT_LAY_H
