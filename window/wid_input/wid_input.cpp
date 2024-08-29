
#include "wid_input.h"

wid_input::wid_input(QWidget *parent) : QFrame(parent)
{
    this->setObjectName("QFrameInputKeyBoard");

    _vec_input_but_word = {
        {_E_NULL_,  _E_NULL_,   _E_F_,  _E_MVL_,    _E_MVR_,    _E_UD_,     _E_BW_      },
        {_E_NULL_,  _E_HC_,     _E_E_,  _E_BKL_,    _E_BKR_,    _E_CLR_,    _E_DEL_     },
        {_E_16H_,   _E_8BT_,    _E_D_,  _E_1_,      _E_2_,      _E_3_,      _E_ADD_     },
        {_E_10D_,   _E_4BT_,    _E_C_,  _E_4_,      _E_5_,      _E_6_,      _E_SUB_     },
        {_E_8O_,    _E_2BT_,    _E_B_,  _E_7_,      _E_8_,      _E_9_,      _E_MULT_    },
        {_E_2B_,    _E_1BT_,    _E_A_,  _E_DOT_,    _E_0_,      _E_EQUAL_,  _E_DIVI_    },
    };

    _set_calc = {
        _E_0_,  _E_1_,  _E_2_,  _E_3_,  _E_4_,  _E_5_,  _E_6_,  _E_7_,  _E_8_,  _E_9_,
        _E_A_,  _E_B_,  _E_C_,  _E_D_,  _E_E_,  _E_F_,
        _E_ADD_,    _E_SUB_,    _E_MULT_,   _E_DIVI_,
        _E_DOT_,    _E_BKL_,    _E_BKR_
    };

    _set_checkable = {
        _E_16H_,    _E_10D_,    _E_8O_,     _E_2B_, 
        _E_8BT_,    _E_4BT_,    _E_2BT_,    _E_1BT_, 
        _E_UD_,     _E_BW_,     _E_HC_
    };

    _set_base = {
        _E_16H_,    _E_10D_,    _E_8O_,     _E_2B_
    };

    _set_bt = {
        _E_8BT_,    _E_4BT_,    _E_2BT_,    _E_1BT_, 
    };

    QVBoxLayout *laybv = new QVBoxLayout;
    for(auto a:_vec_input_but_word)
    {
        QHBoxLayout *laybh = new QHBoxLayout;
        for(auto b:a)
        {
            QPushButton *but = new QPushButton(this);
            but->setObjectName("QPushButtonInputSymbol");
            but->setText(b);
            set_special_checkable(but);

            connect(but,&QPushButton::clicked,[=](){
                if(update_checkble(but)) { emit sn_check_group(but->text()); }
                else 
                {
                    if(but->isCheckable()) { emit sn_check_enable(but->text(),but->isChecked()); }
                    else { emit sn_click_symbol(but->text()); }
                }
            });

            laybh->addWidget(but);
            _map_but.emplace(b,but);
        }
        laybv->addLayout(laybh);
    }

    QHBoxLayout *lay_main = new QHBoxLayout(this);
    lay_main->setContentsMargins(5,5,5,5);
    lay_main->addLayout(laybv);

    uncheck_group(_E_16H_,_set_base);
    uncheck_group(_E_8BT_,_set_bt);
}

wid_input::~wid_input()
{
}

void wid_input::set_special_checkable(QPushButton *but)
{
    auto it = _set_checkable.find(but->text());
    if(it != _set_checkable.end())
    {
        but->setCheckable(true);
    }
}

bool wid_input::is_base_symbol(const QString &symbol)
{
    if(_set_base.find(symbol) != _set_base.end())
    {
        return true;
    }
    return false;
}

bool wid_input::is_bt_symbol(const QString &symbol)
{
    if(_set_bt.find(symbol) != _set_bt.end())
    {
        return true;
    }
    return false;
}

bool wid_input::is_calc_symbol(const QString &symbol)
{
    if(_set_calc.find(symbol) != _set_calc.end())
    {
        return true;
    }
    return false;
}

bool wid_input::is_checkable_symbol(const QString &symbol)
{
    if(_set_checkable.find(symbol) != _set_checkable.end())
    {
        return true;
    }
    return false;
}

void wid_input::set_check_status(const QString &symbol, bool check)
{
    _map_but[symbol]->setChecked(check);
}

bool wid_input::get_check_status(const QString &symbol)
{
    return _map_but[symbol]->isChecked();
}

int wid_input::to_bit_size(const QString &symbol)
{
    if(symbol == _E_1BT_) { return 8*1; }
    if(symbol == _E_2BT_) { return 8*2; }
    if(symbol == _E_4BT_) { return 8*4; }
    if(symbol == _E_8BT_) { return 8*8; }
    return 0;
}

QString wid_input::get_base_group()
{
    for(auto &a:_set_base)
    {
        if(_map_but[a]->isChecked())
        {
            return a;
        }
    }
    return "";
}

QString wid_input::get_bt_group()
{
    for(auto &a:_set_bt)
    {
        if(_map_but[a]->isChecked())
        {
            return a;
        }
    }
    return "";
}

bool wid_input::update_checkble(QPushButton *but)
{
    auto symbol = but->text();
    if(uncheck_group(symbol,_set_base)) { }
    else if(uncheck_group(symbol,_set_bt)) { }
    else { return false; }
    return true;
}

bool wid_input::uncheck_group(QString symbol, const std::set<QString> &symbols)
{
    if(symbols.find(symbol) != symbols.end())
    {
        for(auto &a:symbols)
        {
            _map_but[a]->setChecked(false);
        }
        _map_but[symbol]->setChecked(true);
        return true;
    }
    return false;
}
