#include <QApplication>
#include <QWidget>

#include <iostream>

#include "window/main_window.h"
#include "Fbyte.h"
#include "Fcalc.h"
#include "Tvlog.h"

using namespace std;


void test_1()
{
    {
        float f = 5.5;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        float f = 24.5;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        float f = 123456.5;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        float f = 123456.123456;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        float f = 12.123456;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        long long f = 1024;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        long long f = 15;
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        long long f = 1024;
        f = Fbyte::Tto_swap_endian(f);
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
    {
        long long f = 15;
        f = Fbyte::Tto_swap_endian(f);
        std::string s = Fbyte::Tmem_str(f);
        auto sb = Fbyte::hto_sbyte(s);
        auto sh = Fbyte::hto_hex(s);
        std::cout<<sb<<std::endl;
        std::cout<<sh<<std::endl;
    }
}

void test_2()
{
    auto ret = Fcalc::parse_calc_ls("3+1+(4+10)+2.1+1.1");
    if(Fcalc::is_float(ret))
    {
        auto s1 = Fcalc::to_type_float(ret);
        vlogd($(s1));
    }
    else 
    {
        auto s1 = Fcalc::to_type_integer(ret);
        vlogd($(s1));
    }
}

void test_3()
{
    auto pf = Fbyte::find_flag_char("123asd.12asd",'.');
    vlogd($(pf.first) $(pf.second));
}

void test_4()
{
#if 1
    // 浮点测试
    {
        auto ret = Fcalc::parse_calc_ls("1+2");
        vlogd("3 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("1.1+2.2");
        vlogd("3.3 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
#endif


#if 1
    // 括号测试
    {
        auto ret = Fcalc::parse_calc_ls("4-(1+2)");
        vlogd("1 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("(3+4)-(1+2)");
        vlogd("4 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("-(3+4)-(1+2)");
        vlogd("-10 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("(-3+4)-(1+2)");
        vlogd("-2 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("-(-3+4)-(1+2)");
        vlogd("-4 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("+(-3+4)-(-1+2)");
        vlogd("0 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("(+3+4)-(1+2)");
        vlogd("4 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("+(+3+4)-(1+2)");
        vlogd("4 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("-(+3+4)-(1+2)");
        vlogd("-10 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
#endif

#if 1
    // 符号测试
    {
        auto ret = Fcalc::parse_calc_ls("1+2+3");
        vlogd("6 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("1+2-3");
        vlogd("0 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("11.1+2*2");
        vlogd("15.1 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("11.1*2*2");
        vlogd("44.4 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("25+35-10-5");
        vlogd("45 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("3*3-4/2");
        vlogd("7 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("27/3/3");
        vlogd("3 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("3*3*3");
        vlogd("27 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
#endif

#if 1
    // 组合测试
    {
        // 2-((3+3*4)/2+4-2*2)/(2.0+2)*(2*2)+(4-5)-(20.5+8)+(4.5*2)
        // 2-((3+12)/2+4-2*2)/(4.0)*(4)+(-1)-(28.5)+(9.0)
        // 2-(7.5+4-2*2)/(4.0)*(4)+(-1)-(28.5)+(9.0)
        // 2-(7.5)/(4.0)*(4)+(-1)-(28.5)+(9.0)
        // 2-(7.5)/(4.0)*(4)+(-1)-(28.5)+(9.0)
        // 2-7.5+(-1)-(28.5)+(9.0)
        // -6.5-(28.5)+(9.0)
        // -35+9
        // -26
        auto ret = Fcalc::parse_calc_ls("2-((3+3*4)/2.0+4-2*2)/(2.0+2)*(2*2)+(4-5)-(20.5+8)+(4.5*2)"); 
        vlogd("-26 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        // 1.0/((4.4*2-(2+2*(5+4)+(5-1+(4-2*(7.5*4)))))*(3+3))
        // 1.0/((8.8-(2+18+(5-1+(4-60))))*(6))
        // 1.0/(244.8)
        // 0.004
        auto ret = Fcalc::parse_calc_ls("1.0/((4.4*2-(2+2*(5+4)+(5-1+(4-2*(7.5*4)))))*(3+3))"); 
        vlogd("0.004 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        // 2.0*((4.4*2-(2+2*(5+4)+(5-1+(4-2*(7.5*4)))))*(3+3))
        // 2.0*((8.8-(2+18+(5-1+(4-60))))*(6))
        // 2.0*(244.8)
        // 489.6
        auto ret = Fcalc::parse_calc_ls("2.0*((4.4*2-(2+2*(5+4)+(5-1+(4-2*(7.5*4)))))*(3+3))"); 
        vlogd("489.6 : " << $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
#endif

#if 1
    // 非法测试
    {
        auto ret = Fcalc::parse_calc_ls("1 + 2"); 
        vlogd("null : " << $(ret.is_valid()) $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("((1+2)+3"); 
        vlogd("null : " << $(ret.is_valid()) $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("((1+2)+3()+2"); 
        vlogd("null : " << $(ret.is_valid()) $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("(2+2)(1-1)"); 
        vlogd("null : " << $(ret.is_valid()) $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("1+2"); 
        vlogd("can : " << $(ret.is_valid()) $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
    {
        auto ret = Fcalc::parse_calc_ls("+(+1-2)-(+1+2+3)+(-1-2-3)"); 
        vlogd("can : " << $(ret.is_valid()) $(Fcalc::to_type_integer(ret)) $(Fcalc::to_type_float(ret)));
    }
#endif

}



int run_main_app(int argc, char *argv[])
{
    QApplication a(argc,argv);

    main_window w;
    w.show();

    return a.exec();
}

int exit_main_app(int run_value)
{
    cout<<"exit run value : "<<run_value<<endl;
    return run_value;
}

int perse_arg(int argc, char *argv[])
{
    cout<<"perse_arg : "<<argc<<endl;
    for(int i=0;i<argc;i++)
    {
        cout<<"arg: "<<string(argv[i])<<endl;
    }
    return argc;
}

int main(int argc, char *argv[])
{
    Tvlogs::get()->set_level(vlevel4::e_info);

    vlogd("== begin ==");


#if 1
    test_4();
    return 0;
#endif

    perse_arg(argc,argv);

    int run_value = run_main_app(argc,argv);

    return exit_main_app(run_value);
}