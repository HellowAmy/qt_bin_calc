
#ifndef TESTP1_H
#define TESTP1_H


#include <QDateTime>
#include <QListWidget>



#include <iostream>

#include "Fbyte.h"
#include "Fcalc.h"
#include "Tvlog.h"


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
    // auto ret = Fcalc::parse_calc_ls("3+1+(4+10)+2.1+1.1");
    // if(Fcalc::is_float(ret))
    // {
    //     auto s1 = Fcalc::to_type_float(ret);
    //     vlogd($(s1));
    // }
    // else 
    // {
    //     auto s1 = Fcalc::to_type_integer(ret);
    //     vlogd($(s1));
    // }
}

void test_3()
{
    auto pf = Fbyte::find_flag_char("123asd.12asd",'.');
    vlogd($(pf.first) $(pf.second));
}

void test_4()
{
#if 0
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


#if 0
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

#if 0
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

#if 0
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

#if 0
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
#if 0
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
#endif
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




void test_9()
{
    union ccudata
    {
        int64_t _t64;
        int32_t _t32;
        int16_t _t16;
        int8_t _t8;
        uint64_t _ut64;
        uint32_t _ut32;
        uint16_t _ut16;
        uint8_t _ut8;
    };

    {
        ccudata tr;
        tr._t64 = 255;

        auto vt64   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t64));
        auto vt32   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t32));
        auto vt16   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t16));
        auto vt8    = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t8));
        auto vut64  = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut64));
        auto vut32  = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut32));
        auto vut16  = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut16));
        auto vut8   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut8));

        vlogd($(tr._t64) $(tr._t32) $(tr._t16) $((short)tr._t8) $(tr._ut64) $(tr._ut32) $(tr._ut16) $((unsigned short)tr._ut8));
        vlogd($(vt64) $(vt32) $(vt16) $(vt8));
        vlogd($(vut64) $(vut32) $(vut16) $(vut8));

        int64_t rv64 = Fbyte::Tmem_str<int64_t>(Fbyte::sbyte_hex(vt64));
        int64_t rv32 = Fbyte::Tmem_str<int32_t>(Fbyte::sbyte_hex(vt32));
        int64_t rv16 = Fbyte::Tmem_str<int16_t>(Fbyte::sbyte_hex(vt16));
        int64_t rv8  = Fbyte::Tmem_str<int8_t> (Fbyte::sbyte_hex(vt8));
        uint64_t ruv64   = Fbyte::Tmem_str<uint64_t>(Fbyte::sbyte_hex(vut64));
        uint64_t ruv32   = Fbyte::Tmem_str<uint32_t>(Fbyte::sbyte_hex(vut32));
        uint64_t ruv16   = Fbyte::Tmem_str<uint16_t>(Fbyte::sbyte_hex(vut16));
        uint64_t ruv8    = Fbyte::Tmem_str<uint8_t>(Fbyte::sbyte_hex(vut8));
        vlogd($(rv64) $(rv32) $(rv16) $(rv8) $(ruv64) $(ruv32) $(ruv16) $(ruv8) );
    }
    {
        ccudata tr;
        tr._t64 = 1970324954416903;
//0000011100000000000000000000000000000000000000000000000000000000
//0000000000000000000000000000000000000000000000000000000000000111
//0000000000000111000000000000000000000111000000000000011100000111
//0000000000000111000000000000000000000111000000000000011100000111
        auto vt64   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t64));
        auto vt32   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t32));
        auto vt16   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t16));
        auto vt8    = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._t8));
        auto vut64  = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut64));
        auto vut32  = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut32));
        auto vut16  = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut16));
        auto vut8   = Fbyte::to_strbyte(Fbyte::Tmem_str(tr._ut8));

        vlogd($(tr._t64) $(tr._t32) $(tr._t16) $((short)tr._t8) $(tr._ut64) $(tr._ut32) $(tr._ut16) $((unsigned short)tr._ut8));
        vlogd($(vt64) $(vt32) $(vt16) $(vt8));
        vlogd($(vut64) $(vut32) $(vut16) $(vut8));

        auto wvt64 = Fbyte::sbyte_swap_endian(vt64);
        auto wvt32 = Fbyte::sbyte_swap_endian(vt32);
        auto wvt16 = Fbyte::sbyte_swap_endian(vt16);
        auto wvt8 = Fbyte::sbyte_swap_endian(vt8);
        auto wuvt64 = Fbyte::sbyte_swap_endian(vut64);
        auto wuvt32 = Fbyte::sbyte_swap_endian(vut32);
        auto wuvt16 = Fbyte::sbyte_swap_endian(vut16);
        auto wuvt8 = Fbyte::sbyte_swap_endian( vut8);

        vlogd($(wvt64) $(wvt32) $(wvt16) $(wvt8));
        vlogd($(wuvt64) $(wuvt32) $(wuvt16) $(wuvt8));


        int64_t rv64 = Fbyte::Tmem_str<int64_t>(Fbyte::sbyte_hex(vt64));
        int64_t rv32 = Fbyte::Tmem_str<int32_t>(Fbyte::sbyte_hex(vt32));
        int64_t rv16 = Fbyte::Tmem_str<int16_t>(Fbyte::sbyte_hex(vt16));
        int64_t rv8  = Fbyte::Tmem_str<int8_t> (Fbyte::sbyte_hex(vt8));
        uint64_t ruv64   = Fbyte::Tmem_str<uint64_t>(Fbyte::sbyte_hex(vut64));
        uint64_t ruv32   = Fbyte::Tmem_str<uint32_t>(Fbyte::sbyte_hex(vut32));
        uint64_t ruv16   = Fbyte::Tmem_str<uint16_t>(Fbyte::sbyte_hex(vut16));
        uint64_t ruv8    = Fbyte::Tmem_str<uint8_t>(Fbyte::sbyte_hex(vut8));
        vlogd($(rv64) $(rv32) $(rv16) $(rv8) $(ruv64) $(ruv32) $(ruv16) $(ruv8) );
    }

    {
        int64_t val = 123456789;
        auto byte = Fbyte::Tmem_str<int64_t>(val);
        auto hex = Fbyte::hto_hex(byte);

        int16_t val16 = Fbyte::Tmem_str<int16_t>(byte);
        uint16_t uval16 = Fbyte::Tmem_str<uint16_t>(byte);
        int64_t val64 = Fbyte::Tmem_str<int64_t>(byte);
        uint64_t uval64 = Fbyte::Tmem_str<uint64_t>(byte);
        auto shex = Fbyte::to_strbyte(byte);
        vlogd($(hex) $(val16) $(val64)  $(uval16) $(uval64) $(val) $(shex));
    }
    {
        int64_t val = 8;
        auto byte = Fbyte::Tmem_str<int64_t>(val);
        
        val = Fbyte::Tto_swap_endian<int64_t>(val);
        auto rebyte = Fbyte::Tmem_str<int64_t>(val);

        int16_t wval16 = Fbyte::Tmem_str<int16_t>(rebyte);
        int64_t wval64 = Fbyte::Tmem_str<int64_t>(rebyte);
        int16_t val16 = Fbyte::Tmem_str<int16_t>(byte);
        int64_t val64 = Fbyte::Tmem_str<int64_t>(byte);

        vlogd($(val) $(byte) $(rebyte) $(val16) $(val64) $(wval16) $(wval64));
    }
    {
        int16_t val = 8;
        auto byte = Fbyte::Tmem_str<int16_t>(val);
        
        val = Fbyte::Tto_swap_endian<int16_t>(val);
        auto rebyte = Fbyte::Tmem_str<int16_t>(val);

        int16_t wval16 = Fbyte::Tmem_str<int16_t>(rebyte);
        int64_t wval64 = Fbyte::Tmem_str<int64_t>(rebyte);
        int16_t val16 = Fbyte::Tmem_str<int16_t>(byte);
        int64_t val64 = Fbyte::Tmem_str<int64_t>(byte);

        vlogd($(val) $(byte) $(rebyte) $(val16) $(val64) $(wval16) $(wval64));
    }


    {
        int16_t val = 10;
        auto byte = Fbyte::Tmem_str(val);
        auto hex = Fbyte::hto_hex(byte);

        int16_t val16 = Fbyte::Tmem_str<int16_t>(byte);
        int64_t val64 = Fbyte::Tmem_str<int64_t>(byte);

        vlogd($(hex) $(val16) $(val64) $(val));
    }

}

void test_10()
{
    {
        auto s = Fbyte::coct_sbyte('0');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('1');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('2');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('3');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('4');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('5');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('6');
        vlogd($(s));
    }
    {
        auto s = Fbyte::coct_sbyte('7');
        vlogd($(s));
    }

    {
        auto s = Fbyte::soct_sbyte("777");
        vlogd($(s) $(s.size()));
    }
    {
        auto s = Fbyte::soct_sbyte("717");
        vlogd($(s) $(s.size()));
    }
    {
        auto sbyte = Fbyte::soct_sbyte("1234577777777777777712");
        vlogd($(sbyte) $(sbyte.size()));

        std::reverse(sbyte.begin(),sbyte.end());

        std::string sbv;
        sbv.resize(64);
        std::fill(sbv.begin(),sbv.end(),'0');

        for(int i=0;i<sbv.size() && i<sbyte.size();i++)
        {
            sbv[i] = sbyte[i];
        }
        std::reverse(sbv.begin(),sbv.end());
        vlogd($(sbv));
    }

}


void test_11()
{
    {
        auto s = Fbyte::shex_sint("0f");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("f");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("f0");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("ff");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("f1");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("88");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("188");
        vlogd($(s) );
    }
    {
        auto s = Fbyte::shex_sint("2fc");
        vlogd($(s) );
    }
}

void test_12()
{
    auto i1 = QDateTime::currentSecsSinceEpoch();
    auto i2 = QDateTime::currentMSecsSinceEpoch();
    vlogd($(i1) $(i2));

    auto d1 = QDateTime::fromSecsSinceEpoch(i1).toString(Qt::ISODate);
    auto d2 = QDateTime::fromMSecsSinceEpoch(i2).toString(Qt::ISODate);
    vlogd($Q(d1) $Q(d2));

    // 1730786241
    // 2024-11-05T13:57:21
}

void test_13()
{
    QListWidget *tab = new QListWidget;
    tab->resize(500,500);
    tab->addItem("123");
    tab->addItem("123==asd\nasd\nasdaw\nawasd\nasd");
    tab->addItem("123==asd\nasd\nasdaw\nawasd\nasd");
    tab->addItem("123");

    QListWidgetItem *iy = new QListWidgetItem;
    iy->setText("==pp==123==asd\nasd\nasda22222222222222222222222222222222222222222223333333333333333333333333w\nawasd\nasd");
    iy->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    tab->addItem(iy);
    tab->show();

}



#endif // TESTP1_H
