
#include "main_window.h"


main_window::main_window(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Calculator");

#if 0
    QVBoxLayout *lay_main = new QVBoxLayout(this);
    // {
    //     wid_input *w = new wid_input(this);

    //     connect(w,&wid_input::sn_click_symbol,[=](const QString &symbol){
    //         vlogd($Q(symbol));
    //     });

    //     lay_main->addWidget(w);
    // }

    {
        input_but_lay *w = new input_but_lay(this);

        long long val = 123456789;
        auto cs = Fbyte::Tto_sbyte(val);
        auto fcs = Fbyte::format_sbyte(cs);
        vlogd($(cs));
        vlogd($(fcs));
        w->set_binary_ls(QString::fromStdString(cs));




        connect(w,&input_but_lay::sn_click_pos,[=](int pos,bool val){
            vlogd($(pos) $(val));

            auto sbin = w->get_binary_ls();
            vlogd($Q(sbin));
        });

        lay_main->addWidget(w);
    }




    QPushButton *b = new QPushButton(this);
    lay_main->addWidget(b);


#else
    init_wid(parent);
#endif


}

main_window::~main_window()
{
}

void main_window::init_wid(QWidget *parent)
{
    std::shared_ptr<bool> sp_focus_float = std::make_shared<bool>(false);
    std::shared_ptr<bool> sp_focus_integer = std::make_shared<bool>(false);
    std::shared_ptr<bool> sp_focus_hex = std::make_shared<bool>(false);
    std::shared_ptr<bool> sp_focus_calc = std::make_shared<bool>(false);
    std::shared_ptr<bool> sp_focus_binary = std::make_shared<bool>(false);
    std::shared_ptr<bool> sp_focus_key = std::make_shared<bool>(false);

    input_edit *edt_float = new input_edit(this);
    input_edit *edt_integer = new input_edit(this);
    input_edit *edt_hex = new input_edit(this);
    input_edit *edt_calc = new input_edit(this);
    input_but_lay *board_binary = new input_but_lay(this);
    wid_input *board_key = new wid_input(this);

    edt_float->setPlaceholderText("F");
    edt_integer->setPlaceholderText("D");
    edt_hex->setPlaceholderText("HEX");
    edt_calc->setPlaceholderText("CALC");

    auto fn_is_focus = [=](const std::shared_ptr<bool> &sp){
        if(*sp == true) { return true; }
        return false;
    };

    auto fn_switch_focus = [=](const std::shared_ptr<bool> &sp){
        *sp_focus_float = false;
        *sp_focus_integer = false;
        *sp_focus_hex = false;
        *sp_focus_calc = false;
        *sp_focus_binary = false;
        *sp_focus_key = false;
        *sp = true;
    };

    auto fn_to_str_integer = [=](const std::string &hex,bool is_unsigned,bool is_swap){
        std::string ret_integer;
        size_t bsize = hex.size();
        if(bsize == 1)
        {
            ret_integer = Fbyte::Thto_mem_str<int8_t,uint8_t>(hex,is_unsigned,is_swap);
        }
        else if(bsize == 2)
        {
            ret_integer = Fbyte::Thto_mem_str<int16_t,uint16_t>(hex,is_unsigned,is_swap);
        }
        else if(bsize == 4)
        {
            ret_integer = Fbyte::Thto_mem_str<int32_t,uint32_t>(hex,is_unsigned,is_swap);
        }
        else if(bsize == 8)
        {
            ret_integer = Fbyte::Thto_mem_str<int64_t,uint64_t>(hex,is_unsigned,is_swap);
        }
        return ret_integer;
    };
    
    auto fn_to_sbyte_integer = [=](const std::string &val,int bsize,bool is_swap){
        std::string ret_integer;
        if(bsize == 1)
        {
            auto t = Fbyte::Tfrom_string<int8_t>(val);
            if(is_swap)
            {
                t = Fbyte::Tto_swap_endian<int8_t>(t);
            }
            ret_integer = Fbyte::Tmem_str(t);
        }
        else if(bsize == 2)
        {
            auto t = Fbyte::Tfrom_string<int16_t>(val);
            if(is_swap)
            {
                t = Fbyte::Tto_swap_endian<int16_t>(t);
            }
            ret_integer = Fbyte::Tmem_str(t);
        }
        else if(bsize == 4)
        {
            auto t = Fbyte::Tfrom_string<int32_t>(val);
            if(is_swap)
            {
                t = Fbyte::Tto_swap_endian<int32_t>(t);
            }
            ret_integer = Fbyte::Tmem_str(t);
        }
        else if(bsize == 8)
        {
            auto t = Fbyte::Tfrom_string<int64_t>(val);
            if(is_swap)
            {
                t = Fbyte::Tto_swap_endian<int64_t>(t);
            }
            ret_integer = Fbyte::Tmem_str(t);
        }
        ret_integer = Fbyte::to_strbyte(ret_integer);
        return ret_integer;
    };
    
    auto fn_to_sbyte_float = [=](const std::string &val,int bsize){
        std::string ret_integer;
        if(bsize == 4)
        {
            ret_integer = Fbyte::Tmem_str(Fbyte::Tfrom_string<float>(val));
        }
        else if(bsize == 8)
        {
            ret_integer = Fbyte::Tmem_str(Fbyte::Tfrom_string<double>(val));
        }
        ret_integer = Fbyte::to_strbyte(ret_integer);
        return ret_integer;
    };

    auto fn_to_str_float = [=](const std::string &hex,bool is_unsigned,bool is_swap,bool is_float,bool is_double){
        std::string ret_float;
        if(is_float)
        {
            ret_float = Fbyte::Thto_mem_str<float,float>(hex,is_unsigned,is_swap);
        }
        else if(is_double)
        {
            ret_float = Fbyte::Thto_mem_str<double,double>(hex,is_unsigned,is_swap);
        }
        return ret_float;
    };

    auto fn_update_data = [=](){
        bool is_2B = board_key->get_check_status(_E_2B_);
        bool is_8O = board_key->get_check_status(_E_8O_);
        bool is_10D = board_key->get_check_status(_E_10D_);
        bool is_16H = board_key->get_check_status(_E_16H_);
        std::string sbyte = board_binary->get_binary_valid().toStdString();
        int bsize = board_key->to_bit_size(board_key->get_bt_group()) / 8;
        std::string shex = Fbyte::sbyte_shex(sbyte);
        {
            std::string shexup = Fbyte::to_upper(shex);
            std::string fshex = Fbyte::format_str(shexup,"",4);

            if(fn_is_focus(sp_focus_hex) == false)
            {
                if(is_16H)
                {
                    edt_hex->setText(QString::fromStdString(fshex));
                }
                if(is_10D)
                {
                    edt_hex->setText(edt_integer->text());
                }
                if(is_8O)
                {
                    auto rebyte = Fbyte::sbyte_soct(sbyte);
                    std::reverse(rebyte.begin(),rebyte.end());
                    edt_hex->setText(QString::fromStdString(rebyte));
                }
                if(is_2B)
                {
                    edt_hex->setText(QString::fromStdString(sbyte));
                }
            }
        }
        {
            bool is_swap = board_key->get_check_status(_E_BW_);
            bool is_unsigned = board_key->get_check_status(_E_UD_);
            bool is_float = board_key->get_check_status(_E_FF_);
            bool is_double = board_key->get_check_status(_E_FD_);
            std::string ret_integer;
            std::string ret_float;
            std::string hex = Fbyte::sto_hex(shex);

            ret_integer = fn_to_str_integer(hex,is_unsigned,is_swap);
            ret_float = fn_to_str_float(hex,is_unsigned,is_swap,is_float,is_double);

            if(fn_is_focus(sp_focus_float) == false)
            {
                edt_float->setText(QString::fromStdString(ret_float));
            }
            if(fn_is_focus(sp_focus_integer) == false)
            {
                edt_integer->setText(QString::fromStdString(ret_integer));
            }
        }
    };

    auto fn_to_MVL = [=](){
        QString sbyte = board_binary->get_binary_valid();
        sbyte.push_back("0");
        sbyte.remove(0,1);
        board_binary->set_binary_valid(sbyte);
    };

    auto fn_to_MVR = [=](){
        QString sbyte = board_binary->get_binary_valid();
        sbyte.insert(0,"0");
        sbyte.remove(sbyte.size()-1,1);
        board_binary->set_binary_valid(sbyte);
    };

    auto fn_calc_formula = [=](){
        QString txt = edt_calc->text();
        std::string ret_integer;
        std::string ret_sbyte;
        bool is_swap = board_key->get_check_status(_E_BW_);
        bool is_unsigned = board_key->get_check_status(_E_UD_);
        bool is_float = board_key->get_check_status(_E_FF_);
        bool is_double = board_key->get_check_status(_E_FD_);

        int bsize = board_key->to_bit_size(board_key->get_bt_group()) / 8;
        auto ret = Fcalc::parse_calc_ls(txt.toStdString());
        vlogd($(txt.toStdString()));
        if(ret.is_valid())
        {
            if(Fcalc::is_float(ret))
            {
                ret_sbyte = fn_to_sbyte_float(ret._value,bsize);
            }
            else 
            {
                ret_sbyte = fn_to_sbyte_integer(ret._value,bsize,is_swap);
            }
            vlogd($(ret._value));
            board_binary->set_binary_valid(QString::fromStdString(ret_sbyte));
        }
        else 
        {
            board_binary->clear_data_ls();
        }
    };

    auto fn_calc_clear = [=](){
        edt_calc->setText("");
        fn_calc_formula();
    };

    auto fn_calc_delete = [=](){
        QString txt = edt_calc->text();
        edt_calc->setText(QString(txt.begin(),txt.size() -1));
        fn_calc_formula();
    };

    auto fn_append_calc = [=](const QString &symbol){
        QString txt = edt_calc->text();
        txt += symbol;
        edt_calc->setText(txt);
        fn_calc_formula();
    };

    auto fn_edit_float = [=](const QString &str){

        bool is_float = board_key->get_check_status(_E_FF_);
        bool is_double = board_key->get_check_status(_E_FD_);
        if(is_float)
        {
            float val = Fbyte::Tfrom_string<float>(str.toStdString());
            std::string hex = Fbyte::Tmem_str<float>(val);
            std::string sbyte = Fbyte::to_strbyte(hex);
            board_binary->set_binary_valid(QString::fromStdString(sbyte));
        }
        if(is_double)
        {
            double val = Fbyte::Tfrom_string<double>(str.toStdString());
            std::string hex = Fbyte::Tmem_str<double>(val);
            std::string sbyte = Fbyte::to_strbyte(hex);
            board_binary->set_binary_valid(QString::fromStdString(sbyte));
        }
    };

    auto fn_edit_integer = [=](const QString &str){
        bool is_unsigned = board_key->get_check_status(_E_UD_);
        bool is_swap = board_key->get_check_status(_E_BW_);
        int bsize = board_key->to_bit_size(board_key->get_bt_group()) / 8;

        std::string ret_integer;
        if(bsize == 1)
        {
            if(is_unsigned)
            {
                uint8_t ret = str.toUShort();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<uint8_t>(ret);
                }
                auto s = Fbyte::Tmem_str<uint8_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int8_t ret = str.toShort();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<int8_t>(ret);
                }
                auto s = Fbyte::Tmem_str<int8_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 2)
        {
            if(is_unsigned)
            {
                uint16_t ret = str.toUShort();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<uint16_t>(ret);
                }
                auto s = Fbyte::Tmem_str<uint16_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int16_t ret = str.toShort();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<int16_t>(ret);
                }
                auto s = Fbyte::Tmem_str<int16_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 4)
        {
            if(is_unsigned)
            {
                uint32_t ret = str.toUInt();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<int32_t>(ret);
                }
                auto s = Fbyte::Tmem_str<uint32_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int32_t ret = str.toInt();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<int32_t>(ret);
                }
                auto s = Fbyte::Tmem_str<int32_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 8)
        {
            if(is_unsigned)
            {
                uint64_t ret = str.toULongLong();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<uint64_t>(ret);
                }
                auto s = Fbyte::Tmem_str<uint64_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int64_t ret = str.toLongLong();
                if(is_swap)
                {
                    ret = Fbyte::Tto_swap_endian<int64_t>(ret);
                }
                auto s = Fbyte::Tmem_str<int64_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        board_binary->set_binary_valid(QString::fromStdString(ret_integer));
    };

    auto fn_edit_hex = [=](const QString &str){
        vlogd($Q(str));

        bool is_2B = board_key->get_check_status(_E_2B_);
        bool is_8O = board_key->get_check_status(_E_8O_);
        bool is_10D = board_key->get_check_status(_E_10D_);
        bool is_16H = board_key->get_check_status(_E_16H_);

        if(is_16H)
        {
            auto hex = Fbyte::sto_hex(str.toStdString());
            auto sbyte = Fbyte::to_strbyte(hex);
            
            std::string sbv;
            sbv.resize(board_binary->get_binary_valid().size());
            std::fill(sbv.begin(),sbv.end(),'0');
            for(int i=0;i<sbv.size() && i<sbyte.size();i++)
            {
                sbv[i] = sbyte[i];
            }
            board_binary->set_binary_valid(QString::fromStdString(sbv));
        }
        if(is_10D)
        {
            fn_edit_integer(edt_hex->text());
        }
        if(is_8O)
        {
            auto soct = str.toStdString();
            auto sbyte = Fbyte::soct_sbyte(soct);

            std::string sbv;
            sbv.resize(board_binary->get_binary_valid().size());
            std::fill(sbv.begin(),sbv.end(),'0');
            for(int i=0;i<sbv.size() && i<sbyte.size();i++)
            {
                sbv[i] = sbyte[i];
            }
            std::reverse(sbv.begin(),sbv.end());
            board_binary->set_binary_valid(QString::fromStdString(sbv));
        }
        if(is_2B)
        {
            auto sbyte = str.toStdString();

            std::string sbv;
            sbv.resize(board_binary->get_binary_valid().size());
            std::fill(sbv.begin(),sbv.end(),'0');
            for(int i=0;i<sbv.size() && i<sbyte.size();i++)
            {
                sbv[i] = sbyte[i];
            }
            board_binary->set_binary_valid(QString::fromStdString(sbv));
        }
    };

    auto fn_edit_calc = [=](const QString &str){
        fn_calc_formula();
    };

    connect(edt_float,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_float);

        fn_edit_float(str);
        fn_update_data();

    });
    connect(edt_integer,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_integer);

        fn_edit_integer(str);
        fn_update_data();
    });
    connect(edt_hex,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_hex);

        fn_edit_hex(str);
        fn_update_data();
    });
    connect(edt_calc,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_calc);

        fn_edit_calc(str);
        fn_update_data();
    });

    connect(board_binary,&input_but_lay::sn_click_pos,[=](int pos,bool val){
        vlogd($(pos) $(val));
        fn_switch_focus(sp_focus_binary);

        fn_update_data();
    });

    connect(board_key,&wid_input::sn_check_enable,[=](const QString &symbol,bool check){
        vlogd($Q(symbol) $(check));
        fn_switch_focus(sp_focus_key);

        fn_update_data();
    });
    connect(board_key,&wid_input::sn_check_group,[=](const QString &symbol){
        vlogd($Q(symbol));
        fn_switch_focus(sp_focus_key);

        if(board_key->is_bt_symbol(symbol))
        {
            board_binary->set_bit_size(board_key->to_bit_size(symbol));
        }
        fn_update_data();
    });
    connect(board_key,&wid_input::sn_click_symbol,[=](const QString &symbol){
        vlogd($Q(symbol));
        fn_switch_focus(sp_focus_key);

        if(board_key->is_calc_symbol(symbol)) { fn_append_calc(symbol); }
        else if(symbol == _E_EQUAL_) { fn_calc_formula(); }
        else if(symbol == _E_CLR_) { fn_calc_clear(); } 
        else if(symbol == _E_DEL_) { fn_calc_delete(); } 
        else if(symbol == _E_MVL_) { fn_to_MVL(); } 
        else if(symbol == _E_MVR_) { fn_to_MVR(); } 

        fn_update_data();
    });

    QHBoxLayout *layh = new QHBoxLayout;
    layh->setContentsMargins(0,0,0,0);
    layh->setSpacing(5);
    layh->addWidget(edt_float);
    layh->addWidget(edt_integer);

    QVBoxLayout *lay_main = new QVBoxLayout(this);
    lay_main->addLayout(layh);
    lay_main->addWidget(edt_hex);
    lay_main->addWidget(edt_calc);
    lay_main->addWidget(board_binary);
    lay_main->addWidget(board_key);
}
