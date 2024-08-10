
#include "main_window.h"


main_window::main_window(QWidget *parent) : QWidget(parent)
{
    QString endina;

#if IS_BIG_ENDIAN
    endina = "Big";
#else
    endina = "Little";
#endif

    this->setWindowTitle(QString("Calculator [ %1 ]").arg(endina));

#if 1
    init_wid(parent);
#else

#endif


}

main_window::~main_window()
{
}

void main_window::init_wid(QWidget *parent)
{
    union super_var_t
    {
        int64_t _t64;
        int32_t _t32;
        int16_t _t16;
        int8_t _t8;
        uint64_t _ut64;
        uint32_t _ut32;
        uint16_t _ut16;
        uint8_t _ut8;
        float _ff;
        double _fd;
    };

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

    auto fn_to_sfloat = [=](const std::string &sbyte,int size){
        super_var_t ret;
        if(size == 8) { ret._fd = Fbyte::Tmem_str<double>(Fbyte::sbyte_hex(sbyte)); }
        else if(size == 4) { ret._ff = Fbyte::Tmem_str<float>(Fbyte::sbyte_hex(sbyte)); }
        return ret;
    };
    auto fn_from_sfloat = [=](super_var_t sint,int size){
        std::string ret;
        if(size == 8) { ret = Fbyte::to_strbyte(Fbyte::Tmem_str(sint._fd)); }
        else if(size == 4) { ret = Fbyte::to_strbyte(Fbyte::Tmem_str(sint._ff)); }
        return ret;
    };
    auto fn_to_sint = [=](const std::string &sbyte,int size){
        super_var_t ret;
        if(size == 8) { ret._t64 = Fbyte::Tmem_str<int64_t>(Fbyte::sbyte_hex(sbyte)); }
        else if(size == 4) { ret._t64 = Fbyte::Tmem_str<int32_t>(Fbyte::sbyte_hex(sbyte)); }
        else if(size == 2) { ret._t64 = Fbyte::Tmem_str<int16_t>(Fbyte::sbyte_hex(sbyte)); }
        else if(size == 1) { ret._t64 = Fbyte::Tmem_str<int8_t>(Fbyte::sbyte_hex(sbyte)); }
        return ret;
    };
    auto fn_from_sint = [=](super_var_t sint,int size){
        std::string ret;
        if(size == 8) { ret = Fbyte::to_strbyte(Fbyte::Tmem_str(sint._t64)); }
        else if(size == 4) { ret = Fbyte::to_strbyte(Fbyte::Tmem_str(sint._t32)); }
        else if(size == 2) { ret = Fbyte::to_strbyte(Fbyte::Tmem_str(sint._t16)); }
        else if(size == 1) { ret = Fbyte::to_strbyte(Fbyte::Tmem_str(sint._t8)); }
        return ret;
    };
    auto fn_get_size = [=](){
        if(board_key->get_check_status(_E_8BT_)) { return 8; }
        if(board_key->get_check_status(_E_4BT_)) { return 4; }
        if(board_key->get_check_status(_E_2BT_)) { return 2; }
        if(board_key->get_check_status(_E_1BT_)) { return 1; }
        return 0;
    };


    auto fn_show_F = [=](std::string sbyte,int size){
        int fsize = fn_get_size();
        if(fsize == 8 || fsize == 4)
        {
            std::string sret;
            super_var_t ret = fn_to_sfloat(sbyte,fn_get_size());
            if(fsize == 8) { sret = Fbyte::Tto_string(ret._fd); }
            else if(fsize == 4) { sret = Fbyte::Tto_string(ret._ff); }
            edt_float->setText(QString::fromStdString(sret));
        }
    };

    auto fn_show_D = [=](std::string sbyte,int size){
        bool is_unsigned = board_key->get_check_status(_E_UD_);
        std::string sret;
        super_var_t ret = fn_to_sint(sbyte,size);
        if(is_unsigned) { sret = Fbyte::Tto_string(ret._ut64); }
        else  { sret = Fbyte::Tto_string(ret._t64); }
        edt_integer->setText(QString::fromStdString(sret));
    };

    auto fn_show_HEX = [=](std::string sbyte,int size){
        bool is_2B = board_key->get_check_status(_E_2B_);
        bool is_8O = board_key->get_check_status(_E_8O_);
        bool is_10D = board_key->get_check_status(_E_10D_);
        bool is_16H = board_key->get_check_status(_E_16H_);

        if(is_2B)
        {
            edt_hex->setText(QString::fromStdString(sbyte));
        }
        else if(is_8O)
        {
            std::reverse(sbyte.begin(),sbyte.end());
            auto srcout = Fbyte::sbyte_soct(sbyte);

            std::reverse(srcout.begin(),srcout.end());
            edt_hex->setText(QString::fromStdString(srcout));
        }
        else if(is_10D)
        {
            edt_hex->setText(edt_integer->text());
        }
        else if(is_16H)
        {
            edt_hex->setText(QString::fromStdString(Fbyte::to_upper(Fbyte::sbyte_shex(sbyte))));
        }
    };

    auto fn_update_data = [=](){
        std::string sbyte = board_binary->get_binary_valid().toStdString();

        bool is_swap = board_key->get_check_status(_E_BW_);
        if(is_swap) { sbyte = Fbyte::sbyte_swap_endian(sbyte); }

        int size = fn_get_size();
        if(fn_is_focus(sp_focus_float) == false) { fn_show_F(sbyte,size); }
        if(fn_is_focus(sp_focus_integer) == false) { fn_show_D(sbyte,size); }
        if(fn_is_focus(sp_focus_hex) == false) { fn_show_HEX(sbyte,size); }
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
        int size = fn_get_size();
        QString txt = edt_calc->text();
        auto ret = Fcalc::parse_calc_ls(txt.toStdString());
        if(ret.is_valid())
        {
            super_var_t sret;
            if(Fcalc::is_float(ret))
            {
                if(size == 4) { sret._ff = Fbyte::Tfrom_string<float>(ret._value); }
                if(size == 8) { sret._fd = Fbyte::Tfrom_string<double>(ret._value); }
                board_binary->set_binary_valid(QString::fromStdString(fn_from_sfloat(sret,size)));
            }
            else 
            {
                sret._t64 = Fbyte::Tfrom_string<int64_t>(ret._value);
                board_binary->set_binary_valid(QString::fromStdString(fn_from_sint(sret,size)));
            }
        }
        else { board_binary->clear_data_ls(); }
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
        bool is_swap = board_key->get_check_status(_E_BW_);
        int size = fn_get_size();
        if(size == 4)
        {
            float val = Fbyte::Tfrom_string<float>(str.toStdString());
            if(is_swap) { val = Fbyte::Tto_swap_endian<float>(val); }

            std::string hex = Fbyte::Tmem_str<float>(val);
            std::string sbyte = Fbyte::to_strbyte(hex);
            board_binary->set_binary_valid(QString::fromStdString(sbyte));
        }
        if(size == 8)
        {
            double val = Fbyte::Tfrom_string<double>(str.toStdString());
            if(is_swap) { val = Fbyte::Tto_swap_endian<float>(val); }

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
                if(is_swap) { ret = Fbyte::Tto_swap_endian<uint8_t>(ret); }
                auto s = Fbyte::Tmem_str<uint8_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int8_t ret = str.toShort();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<int8_t>(ret); }
                auto s = Fbyte::Tmem_str<int8_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 2)
        {
            if(is_unsigned)
            {
                uint16_t ret = str.toUShort();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<uint16_t>(ret); }
                auto s = Fbyte::Tmem_str<uint16_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int16_t ret = str.toShort();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<int16_t>(ret); }
                auto s = Fbyte::Tmem_str<int16_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 4)
        {
            if(is_unsigned)
            {
                uint32_t ret = str.toUInt();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<int32_t>(ret); }
                auto s = Fbyte::Tmem_str<uint32_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int32_t ret = str.toInt();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<int32_t>(ret); }
                auto s = Fbyte::Tmem_str<int32_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 8)
        {
            if(is_unsigned)
            {
                uint64_t ret = str.toULongLong();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<uint64_t>(ret); }
                auto s = Fbyte::Tmem_str<uint64_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int64_t ret = str.toLongLong();
                if(is_swap) { ret = Fbyte::Tto_swap_endian<int64_t>(ret); }
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
            auto astr = str;
            if(astr.size() % 2 != 0) { astr.insert(0,'0'); }
            auto hex = Fbyte::sto_hex(astr.toStdString());

            auto sbyte = Fbyte::to_strbyte(hex);
            std::reverse(sbyte.begin(),sbyte.end());
            
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
        if(is_10D)
        {
            fn_edit_integer(edt_hex->text());
        }
        if(is_8O)
        {
            auto sbyte = Fbyte::soct_sbyte(str.toStdString());
            std::reverse(sbyte.begin(),sbyte.end());

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
            std::reverse(sbv.begin(),sbv.end());
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
            edt_calc->setText("");
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
