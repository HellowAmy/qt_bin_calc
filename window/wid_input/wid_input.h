
#ifndef WID_INPUT_H
#define WID_INPUT_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

#include <vector>
#include <set>
#include <map>

static QString _E_NULL_ = "";
static QString _E_0_ = "0";
static QString _E_1_ = "1";
static QString _E_2_ = "2";
static QString _E_3_ = "3";
static QString _E_4_ = "4";
static QString _E_5_ = "5";
static QString _E_6_ = "6";
static QString _E_7_ = "7";
static QString _E_8_ = "8";
static QString _E_9_ = "9";
static QString _E_A_ = "A";
static QString _E_B_ = "B";
static QString _E_C_ = "C";
static QString _E_D_ = "D";
static QString _E_E_ = "E";
static QString _E_F_ = "F";
static QString _E_2B_ = "2B";
static QString _E_8O_ = "8O";
static QString _E_10D_ = "10D";
static QString _E_16H_ = "16H";
static QString _E_1BT_ = "1BT";
static QString _E_2BT_ = "2BT";
static QString _E_4BT_ = "4BT";
static QString _E_8BT_ = "8BT";
static QString _E_ADD_ = "+";
static QString _E_SUB_ = "-";
static QString _E_MULT_ = "*";
static QString _E_DIVI_ = "/";
static QString _E_DOT_ = ".";
static QString _E_EQUAL_ = "=";
static QString _E_MVL_ = "<<";
static QString _E_MVR_ = ">>";
static QString _E_BKL_ = "(";
static QString _E_BKR_ = ")";
static QString _E_CLR_ = "[C]";
static QString _E_DEL_ = "[D]";
static QString _E_FD_ = "[FD]";
static QString _E_FF_ = "[FF]";
static QString _E_UD_ = "[UD]";
static QString _E_BW_ = "[BW]";


class wid_input : public QFrame
{
    Q_OBJECT
public:
    wid_input(QWidget *parent = nullptr);
    ~wid_input();

    void set_special_checkable(QPushButton *but);

    bool is_base_symbol(const QString &symbol);
    bool is_bt_symbol(const QString &symbol);
    bool is_calc_symbol(const QString &symbol);
    bool is_checkable_symbol(const QString &symbol);

    void set_check_status(const QString &symbol,bool check);
    bool get_check_status(const QString &symbol);

    int to_bit_size(const QString &symbol);

    QString get_base_group();
    QString get_bt_group();

signals:    
    void sn_click_symbol(const QString &symbol);
    void sn_check_group(const QString &symbol);
    void sn_check_enable(const QString &symbol,bool check);

protected:
    bool update_checkble(QPushButton *but);
    bool uncheck_group(QString symbol,const std::set<QString> &set);

private:
    std::vector<std::vector<QString>> _vec_input_but_word;
    std::map<QString,QPushButton*> _map_but;
    std::set<QString> _set_calc;
    std::set<QString> _set_checkable;
    std::set<QString> _set_base;
    std::set<QString> _set_bt;

};
#endif // WID_INPUT_H
