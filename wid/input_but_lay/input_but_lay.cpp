
#include "input_but_lay.h"

input_but_lay::input_but_lay(QWidget *parent) : QFrame(parent)
{
    this->setObjectName("QFrameInputBinaryLay");

    QVBoxLayout *lay_main = new QVBoxLayout(this);
    lay_main->setContentsMargins(5,5,5,5);
    lay_main->setSpacing(0);

    for(int row=0;row<2;row++)
    {
        QHBoxLayout *layh = new QHBoxLayout;
        layh->setContentsMargins(0,0,0,0);
        layh->setSpacing(10);

        QHBoxLayout *laylab = new QHBoxLayout;
        laylab->setContentsMargins(0,0,0,0);
        laylab->setSpacing(10);

        for(int part=0;part<4;part++)
        {   
            QHBoxLayout *layhp = new QHBoxLayout;
            layhp->setContentsMargins(0,0,0,0);
            layhp->setSpacing(0);

            QLabel *lab = new QLabel(this);
            lab->setObjectName("QLabelBinaryListPos");
            lab->setText(QString::number((64 - (32 * row) - part * 8) -1));
            laylab->addWidget(lab);
            
            for(int byte=0;byte<8;byte++)
            {
                QPushButton *but = new QPushButton(this);
                but->setObjectName("QPushButtonInputBinaryList");
                but->setText(_E_BIN_ZERO_);
                _vec_but.push_back(but);

                connect(but,&QPushButton::clicked,[=](){
                    if(but->text() == _E_BIN_DISABLE_)
                    {
                        return;
                    }

                    bool val = false;
                    if(but->text() == _E_BIN_ONE_)
                    {
                        val = false;
                        but->setText(_E_BIN_ZERO_);
                    }
                    else 
                    {
                        val = true;
                        but->setText(_E_BIN_ONE_);
                    }
                    emit sn_click_pos(64 -(32*row) -(8*part) -byte -1,val);
                });

                layhp->addWidget(but);
            }
            layh->addLayout(layhp);   
        }

        lay_main->addLayout(layh);
        lay_main->addLayout(laylab);
    }
}

input_but_lay::~input_but_lay()
{
}

QString input_but_lay::get_binary_ls()
{
    QString s;
    for(int i=0;i<_vec_but.size();i++)
    {
        s.push_back(_vec_but[i]->text());
    }
    return s;
}

QString input_but_lay::get_binary_valid()
{
    QString s;
    for(int i=0;i<_vec_but.size();i++)
    {
        auto txt = _vec_but[i]->text();
        if(txt != _E_BIN_DISABLE_)
        {
            s.push_back(_vec_but[i]->text());
        }
    }
    return s;
}

void input_but_lay::clear_data_ls()
{
    for(int i=0;i<_vec_but.size();i++)
    {
        auto txt = _vec_but[i]->text();
        if(txt != _E_BIN_DISABLE_)
        {
            _vec_but[i]->setText(_E_BIN_ZERO_);
        }
    }
}

void input_but_lay::set_binary_ls(const QString &s)
{
    if(s.size() > _vec_but.size())
    {
        return ;
    }

    for(int i=0;i<s.size();i++)
    {
        _vec_but[i]->setText(s[i]);
    }
}

void input_but_lay::set_binary_valid(const QString &s)
{
    int count = 0;
    for(int i=0;i<_vec_but.size();i++)
    {
        auto txt = _vec_but[i]->text();
        if(txt != _E_BIN_DISABLE_)
        {
            if(count >= s.size())
            {
                break;
            }
            _vec_but[i]->setText(s[count]);
            count++;
        }
    }
}

void input_but_lay::set_bit_size(int size)
{
    int hide_size = _vec_but.size() - size;
    for(int i=0;i<_vec_but.size();i++)
    {
        if(i < hide_size)
        {
            _vec_but[i]->setText(_E_BIN_DISABLE_);
        }
        else 
        {
            _vec_but[i]->setText(_E_BIN_ZERO_);
        }
    }
}
