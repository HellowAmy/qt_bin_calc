
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

    auto fn_update_data = [=](){
        std::string sbyte = board_binary->get_binary_valid().toStdString();
        int bsize = board_key->to_bit_size(board_key->get_bt_group()) / 8;
        std::string shex = Fbyte::sbyte_shex(sbyte);
        {
            std::string shexup = Fbyte::to_upper(shex);
            std::string fshex = Fbyte::format_str(shexup,"",4);

            if(fn_is_focus(sp_focus_hex) == false)
            {
                edt_hex->setText(QString::fromStdString(fshex));
            }
        }
        {
            
            bool is_unsigned = board_key->get_check_status(_E_UD_);
            bool is_float = board_key->get_check_status(_E_FF_);
            bool is_double = board_key->get_check_status(_E_FD_);
            std::string ret_integer;
            std::string ret_float;
            std::string hex = Fbyte::sto_hex(shex);
            if(bsize == 1)
            {
                ret_integer = Fbyte::Thto_mem_str<int8_t,uint8_t>(hex,is_unsigned);
            }
            else if(bsize == 2)
            {
                ret_integer = Fbyte::Thto_mem_str<int16_t,uint16_t>(hex,is_unsigned);
            }
            else if(bsize == 4)
            {
                ret_integer = Fbyte::Thto_mem_str<int32_t,uint32_t>(hex,is_unsigned);
                if(is_float)
                {
                    ret_float = Fbyte::Thto_mem_str<float,float>(hex,is_unsigned);
                }
            }
            else if(bsize == 8)
            {
                ret_integer = Fbyte::Thto_mem_str<int64_t,uint64_t>(hex,is_unsigned);
                if(is_float)
                {
                    ret_float = Fbyte::Thto_mem_str<float,float>(hex,is_unsigned);
                }
                else if(is_double)
                {
                    ret_float = Fbyte::Thto_mem_str<double,double>(hex,is_unsigned);
                }
            }

            if(fn_is_focus(sp_focus_float) == false)
            {
                edt_float->setText(QString::fromStdString(ret_float));
            }
            if(fn_is_focus(sp_focus_integer) == false)
            {
                edt_integer->setText(QString::fromStdString(ret_integer));
            }
        }



        vlogd($(bsize));
        // if()

        // Fbyte::Tmem_str<>();

    };

    auto fn_to_2B = [=](){

    };

    auto fn_to_8O = [=](){
        
    };

    auto fn_to_10D = [=](){
        
    };

    auto fn_to_16H = [=](){
        
    };

    auto fn_to_FF = [=](){
        
    };

    auto fn_to_FD = [=](){
        
    };

    auto fn_to_UD = [=](bool check){
        
    };

    auto fn_to_BW = [=](bool check){
        
    };

    auto fn_to_MVL = [=](){
        
    };

    auto fn_to_MVR = [=](){
        
    };

    auto fn_append_calc = [=](const QString &symbol){
        
    };

    auto fn_calc_formula = [=](){
        
    };

    auto fn_calc_clear = [=](){
        
    };

    auto fn_calc_delete = [=](){
        
    };

    auto fn_edit_float = [=](const QString &str){

    };

    auto fn_edit_integer = [=](const QString &str){
        bool is_unsigned = board_key->get_check_status(_E_UD_);
        int bsize = board_key->to_bit_size(board_key->get_bt_group()) / 8;

        std::string ret_integer;
        if(bsize == 1)
        {
            if(is_unsigned)
            {
                uint8_t ret = str.toUShort();
                auto s = Fbyte::Tmem_str<uint8_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int8_t ret = str.toShort();
                auto s = Fbyte::Tmem_str<int8_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 2)
        {
            if(is_unsigned)
            {
                uint16_t ret = str.toUShort();
                auto s = Fbyte::Tmem_str<uint16_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int16_t ret = str.toShort();
                auto s = Fbyte::Tmem_str<int16_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 4)
        {
            if(is_unsigned)
            {
                uint32_t ret = str.toUInt();
                auto s = Fbyte::Tmem_str<uint32_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int32_t ret = str.toInt();
                auto s = Fbyte::Tmem_str<int32_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }
        else if(bsize == 8)
        {
            if(is_unsigned)
            {
                uint64_t ret = str.toULongLong();
                auto s = Fbyte::Tmem_str<uint64_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
            else 
            {
                int64_t ret = str.toLongLong();
                auto s = Fbyte::Tmem_str<int64_t>(ret);
                ret_integer = Fbyte::hto_sbyte(s);
            }
        }

        board_binary->set_binary_valid(QString::fromStdString(ret_integer));
        fn_update_data();
    };

    auto fn_edit_hex = [=](const QString &str){
        
    };

    auto fn_edit_calc = [=](const QString &str){
        
    };

    connect(edt_float,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_float);
    });
    connect(edt_integer,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_integer);

        fn_edit_integer(str);
    });
    connect(edt_hex,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_hex);
    });
    connect(edt_calc,&input_edit::textEdited,[=](const QString &str){
        vlogd($Q(str));
        fn_switch_focus(sp_focus_calc);
    });

    connect(board_binary,&input_but_lay::sn_click_pos,[=](int pos,bool val){
        vlogd($(pos) $(val));
        fn_switch_focus(sp_focus_binary);

        fn_update_data();
    });

    connect(board_key,&wid_input::sn_check_enable,[=](const QString &symbol,bool check){
        vlogd($Q(symbol) $(check));
        fn_switch_focus(sp_focus_key);

        if(symbol == _E_UD_) { fn_to_UD(check); }
        else if(symbol == _E_BW_) { fn_to_BW(check); }
    });
    connect(board_key,&wid_input::sn_check_group,[=](const QString &symbol){
        vlogd($Q(symbol));
        fn_switch_focus(sp_focus_key);

        if(board_key->is_bt_symbol(symbol))
        {
            board_binary->set_bit_size(board_key->to_bit_size(symbol));
        }

        if(board_key->is_base_symbol(symbol))
        {
            if(symbol == _E_2B_) { fn_to_2B(); }
            else if(symbol == _E_8O_) { fn_to_8O(); }
            else if(symbol == _E_10D_) { fn_to_10D(); }
            else if(symbol == _E_16H_) { fn_to_16H(); }
        }
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
        else if(symbol == _E_FF_) { fn_to_FF(); }
        else if(symbol == _E_FD_) { fn_to_FD(); }
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
