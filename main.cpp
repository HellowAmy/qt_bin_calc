#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfo>

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

void test_5()
{
    {
        auto ret = Fcalc::parse_calc_ls("1+2"); 
        if(ret.is_valid())
        {
            std::string smen;
            if(ret._is_integer)
            {
                auto val = Fcalc::to_type_integer(ret);
                val = Fbyte::Tto_endian_net(val);
                smen = Fbyte::Tmem_str(val);
            }
            else 
            {
                auto val = Fcalc::to_type_float(ret);
                val = Fbyte::Tto_endian_net(val);
                smen = Fbyte::Tmem_str(val);
            }
                    
            auto sb = Fbyte::hto_sbyte(smen);
            auto sh = Fbyte::hto_hex(smen);
            vlogd($(sb) $(sh) $(ret._value));
        }
    }

    {
        auto ret = Fcalc::parse_calc_ls("1.1+2.2"); 
        if(ret.is_valid())
        {
            std::string smen;
            if(ret._is_integer)
            {
                auto val = Fcalc::to_type_integer(ret);
                val = Fbyte::Tto_endian_net(val);
                smen = Fbyte::Tmem_str(val);
            }
            else 
            {
                auto val = Fcalc::to_type_float(ret);
                val = Fbyte::Tto_endian_net(val);
                smen = Fbyte::Tmem_str(val);
            }
                    
            auto sb = Fbyte::hto_sbyte(smen);
            auto sh = Fbyte::hto_hex(smen);
            vlogd($(sb) $(sh) $(ret._value) $(Fbyte::to_upper(sh)));

            auto hex = Fbyte::sto_hex(sh);
            auto val = Fbyte::Tmem_str<double>(hex);
            val = Fbyte::Tto_endian_net(val);
            vlogd($(val));
        }
    }

}

// 从0-20转-72~12
double VolToNetType(int val)
{
    double dval = val;
    dval *= 4;
    dval -= 72;
    return dval;
}

// 从-72~12转0-20
int VolToShowType(double val)
{
    int dval = val;
    dval += 72;
    dval /= 4; 
    return dval;
}


void test_6()
{   
    {
        auto s1 = VolToNetType(0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToNetType(1);
        vlogd($(s1));
    }
    {
        auto s1 = VolToNetType(4);
        vlogd($(s1));
    }
    {
        auto s1 = VolToNetType(10);
        vlogd($(s1));
    }
    {
        auto s1 = VolToNetType(19);
        vlogd($(s1));
    }
    {
        auto s1 = VolToNetType(20);
        vlogd($(s1));
    }
    {
        auto s1 = VolToNetType(21);
        vlogd($(s1));
    }

    {
        auto s1 = VolToShowType(-72.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(-70.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(-68.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(-64.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(-60.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(-55.2);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(-30.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(8.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(10.0);
        vlogd($(s1));
    }
    {
        auto s1 = VolToShowType(12.0);
        vlogd($(s1));
    }
}

void test_7()
{
    {
        auto c = Fbyte::sbyte_char("00001111");
        auto s = Fbyte::cto_shex(c);
        vlogd($(c) $(s));
    }
    {
        auto c = Fbyte::sbyte_char("01000001");
        auto s = Fbyte::cto_shex(c);
        vlogd($(c) $(s));
    }
    {
        auto c = Fbyte::sbyte_shex("01000001010000010000111100001111");
        vlogd($(c));
    }
    {
        auto c = Fbyte::sbyte_shex("1111000101000001000011110000111101000001010000010000111100001111");
        vlogd($(c));
    }

}

void test_8()
{
    {
        auto c = Fbyte::sbyte_soct("111001111");
        vlogd($(c));
    }
    {
        auto c = Fbyte::sbyte_soct("1110011111");
        vlogd($(c));
    }
    {
        auto c = Fbyte::soct_sbyte("717");
        vlogd($(c));
    }
    {
        auto c = Fbyte::soct_sbyte("1717");
        vlogd($(c));
    }
}

// 读取指定目录下的所有样式表
QString read_file_qss(QString path)
{
    QString style;
    QDir dir(path);
    auto ls = dir.entryList();
    for(auto &a:ls)
    {
        QFileInfo info(path + a);
        if(info.isFile() && info.suffix() == "qss")
        {
            QFile fs(info.absoluteFilePath());
            if(fs.open(QIODevice::ReadOnly))
            {
                style += fs.readAll();
                fs.close();
            }
        }
    }
    return style;
}

int run_main_app(int argc, char *argv[])
{
    QApplication a(argc,argv);

    auto sstyle = read_file_qss("../config/style/default/");
    qApp->setStyleSheet(sstyle);
    vlogd($Q(sstyle));

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


#if 0
    test_8();
    return 0;
#endif

    perse_arg(argc,argv);

    int run_value = run_main_app(argc,argv);

    return exit_main_app(run_value);
}