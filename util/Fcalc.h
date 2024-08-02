
#ifndef FCALC_H
#define FCALC_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <cctype>
#include <functional>


#include "Tvlog.h"
#include "Fbyte.h"

using namespace std;


typedef std::string sstr;
typedef const std::string & cstr;


struct calc_object_t
{
    calc_object_t() { }

    calc_object_t(bool is_integer,bool is_float,bool is_symbol,sstr value) 
        : _is_integer(is_integer),_is_float(is_float),_is_symbol(is_symbol),_value(value) { }
    
    void set_int(cstr s)
    {
        _is_integer = true;
        _value = s;
    }
    void set_float(cstr s)
    {
        _is_float = true;
        _value = s;
    }

    void set_symbol(cstr s)
    {
        _is_symbol = true;
        _value = s;
    } 

    bool is_valid()
    {
        if(_is_integer || _is_float || _is_symbol) 
        { 
            return true; 
        }
        return false;
    }

    bool _is_integer = false;
    bool _is_float = false;
    bool _is_symbol = false;
    sstr _value;
};

typedef calc_object_t calc_t;
typedef const calc_object_t & ccalc_t;


struct Tcalc_result_template
{
    static calc_t calc_formula(ccalc_t a,ccalc_t b) { return {}; } 
    static std::string get_symbol() { return {}; } 
    static int get_level() { return {}; } 
};
struct Tcalc_result_add : public Tcalc_result_template
{
    typedef calc_object_t calc_t;
    typedef const calc_object_t & ccalc_t;

    static calc_t calc_formula(ccalc_t a,ccalc_t b)
    {
        calc_object_t ret;
        if(a._is_float || b._is_float)
        {
            double va = Fbyte::Tfrom_string<double>(a._value);
            double vb = Fbyte::Tfrom_string<double>(b._value);
            double vs = va + vb;
            ret.set_float(Fbyte::Tto_string(vs));
        }
        else 
        {
            int64_t va = Fbyte::Tfrom_string<int64_t>(a._value);
            int64_t vb = Fbyte::Tfrom_string<int64_t>(b._value);
            int64_t vs = va + vb;
            ret.set_int(Fbyte::Tto_string(vs));
        }
        return ret;
    }   
    static std::string get_symbol()
    {
        return "+";
    }
    static int get_level()
    {
        return 1;
    }
};
struct Tcalc_result_sub : public Tcalc_result_template
{
    typedef calc_object_t calc_t;
    typedef const calc_object_t & ccalc_t;

    static calc_t calc_formula(ccalc_t a,ccalc_t b)
    {
        calc_object_t ret;
        if(a._is_float || b._is_float)
        {
            double va = Fbyte::Tfrom_string<double>(a._value);
            double vb = Fbyte::Tfrom_string<double>(b._value);
            double vs = va - vb;
            ret.set_float(Fbyte::Tto_string(vs));
        }
        else 
        {
            int64_t va = Fbyte::Tfrom_string<int64_t>(a._value);
            int64_t vb = Fbyte::Tfrom_string<int64_t>(b._value);
            int64_t vs = va - vb;
            ret.set_int(Fbyte::Tto_string(vs));
        }
        return ret;
    }   
    static std::string get_symbol()
    {
        return "-";
    }
    static int get_level()
    {
        return 1;
    }
};
struct Tcalc_result_mult : public Tcalc_result_template
{
    typedef calc_object_t calc_t;
    typedef const calc_object_t & ccalc_t;

    static calc_t calc_formula(ccalc_t a,ccalc_t b)
    {
        calc_object_t ret;
        if(a._is_float || b._is_float)
        {
            double va = Fbyte::Tfrom_string<double>(a._value);
            double vb = Fbyte::Tfrom_string<double>(b._value);
            double vs = va * vb;
            ret.set_float(Fbyte::Tto_string(vs));
        }
        else 
        {
            int64_t va = Fbyte::Tfrom_string<int64_t>(a._value);
            int64_t vb = Fbyte::Tfrom_string<int64_t>(b._value);
            int64_t vs = va * vb;
            ret.set_int(Fbyte::Tto_string(vs));
        }
        return ret;
    }   
    static std::string get_symbol()
    {
        return "*";
    }
    static int get_level()
    {
        return 2;
    }
};
struct Tcalc_result_divi : public Tcalc_result_template
{
    typedef calc_object_t calc_t;
    typedef const calc_object_t & ccalc_t;

    static calc_t calc_formula(ccalc_t a,ccalc_t b)
    {
        calc_object_t ret;
        if(a._is_float || b._is_float)
        {
            double va = Fbyte::Tfrom_string<double>(a._value);
            double vb = Fbyte::Tfrom_string<double>(b._value);
            double vs = va / vb;
            ret.set_float(Fbyte::Tto_string(vs));
        }
        else 
        {
            int64_t va = Fbyte::Tfrom_string<int64_t>(a._value);
            int64_t vb = Fbyte::Tfrom_string<int64_t>(b._value);
            int64_t vs = va / vb;
            ret.set_int(Fbyte::Tto_string(vs));
        }
        return ret;
    }   
    static std::string get_symbol()
    {
        return "/";
    }
    static int get_level()
    {
        return 2;
    }
};




struct Tcalc_result_base
{
    struct Tcala_t
    {
        using Tcb = function<calc_object_t(const calc_object_t &,const calc_object_t &)>;

        Tcala_t(int level,Tcb cb) : _level(level),_calc_cb(cb) { }

        int _level;
        Tcb _calc_cb;
    };

    Tcalc_result_base()
    {
        {
            _mp_opt_cb.emplace(calc_t(false,false,true,Tcalc_result_add::get_symbol())._value,
                Tcala_t(Tcalc_result_add::get_level(), 
                    [](ccalc_t a,ccalc_t b) -> calc_object_t {
                        return Tcalc_result_add::calc_formula(a,b);
                    }
                ));
            _mp_opt_cb.emplace(calc_t(false,false,true,Tcalc_result_sub::get_symbol())._value,
                Tcala_t(Tcalc_result_sub::get_level(), 
                    [](ccalc_t a,ccalc_t b) -> calc_object_t {
                        return Tcalc_result_sub::calc_formula(a,b);
                    }
                ));
            _mp_opt_cb.emplace(calc_t(false,false,true,Tcalc_result_mult::get_symbol())._value,
                Tcala_t(Tcalc_result_mult::get_level(), 
                    [](ccalc_t a,ccalc_t b) -> calc_object_t {
                        return Tcalc_result_mult::calc_formula(a,b);
                    }
                ));
            _mp_opt_cb.emplace(calc_t(false,false,true,Tcalc_result_divi::get_symbol())._value,
                Tcala_t(Tcalc_result_divi::get_level(), 
                    [](ccalc_t a,ccalc_t b) -> calc_object_t {
                        return Tcalc_result_divi::calc_formula(a,b);
                    }
                ));
        }
    }

    calc_t calc_formula(ccalc_t a,ccalc_t b,ccalc_t op)
    {
        auto it = _mp_opt_cb.find(op._value);
        if(it != _mp_opt_cb.end())
        {
            return it->second._calc_cb(a,b);
        }
        return calc_t();
    }

    int calc_level(cstr op1,cstr op2)
    {   
        auto it1 = _mp_opt_cb.find(op1);
        auto it2 = _mp_opt_cb.find(op2);
        if(it1 != _mp_opt_cb.end() && it2 != _mp_opt_cb.end())
        {
            int level1 = it1->second._level;
            int level2 = it2->second._level;
            return level1 - level2;
        }
        return 0;
    }

    std::map<sstr,Tcala_t> _mp_opt_cb;
};


template<typename T>
struct Tcalc_stack
{
    bool calc_opt()
    {
        if(_nums.size() < 2)
        {
            return false;
        }
        if(_symbols.size() == 0)
        {
            return false;
        }
        calc_object_t b = _nums.top();
        _nums.pop();

        calc_object_t a = _nums.top();
        _nums.pop();

        calc_object_t op = _symbols.top();
        _symbols.pop();

        calc_object_t ret = _calc.calc_formula(a,b,op);
        _nums.push(ret);
        // vlogd($(a._value) $(op._value) $(b._value) $(ret._value));
        return true;
    }

    calc_object_t get_result()
    {
        return _nums.top();
    }

    bool verify_valid()
    {
        if(_symbols.empty() == false)
        {
            return false;
        }
        if(_nums.size() != 1)
        {
            return false;
        }
        return true;
    }

    stack<calc_object_t> _nums;
    stack<calc_object_t> _symbols;
    T _calc;
};

struct Fcalc
{
    static calc_object_t parse_calc_ls(cstr s)
    {
        Tcalc_stack<Tcalc_result_base> scalc;

        for(size_t i=0;i<s.size();i++)
        {
            char c = s[i];
            if(c == '(')
            {
                scalc._symbols.push(calc_object_t(false,false,true,{c}));
            }
            else if(c == ')')
            {
                while (scalc._symbols.empty() == false && scalc._symbols.top()._value != "(")
                {
                    bool ok = scalc.calc_opt();
                    if(ok == false)
                    {
                        break;
                    }
                }
                scalc._symbols.pop();
            }
            else if(Fbyte::is_hex_digit(c))
            {
                char dot = '.';
                size_t go = i;
                sstr snum;
                while (go < s.size() && (Fbyte::is_hex_digit(s[go]) || s[go] == dot)) 
                {
                    snum.push_back(s[go]);
                    go++;
                }
                i = go - 1;
                auto pf = Fbyte::find_flag_char(snum,dot);
                if(pf.first)
                {
                    scalc._nums.push(calc_object_t(false,true,false,{snum}));
                }
                else 
                {
                    scalc._nums.push(calc_object_t(true,false,false,{snum}));
                }
            }
            else 
            {
                if(i > 0 && s[i-1] == '(')
                {
                    scalc._nums.push(calc_object_t(true,false,false,{"0"}));
                }
                else if(i == 0 && s[i] == '-')
                {
                    scalc._nums.push(calc_object_t(true,false,false,{"0"}));
                }
                else if(i == 0 && s[i] == '+')
                {
                    scalc._nums.push(calc_object_t(true,false,false,{"0"}));
                }

                while (scalc._symbols.empty() == false && scalc._symbols.top()._value != "(") 
                {
                    auto val = scalc._symbols.top()._value;
                    if(scalc._calc.calc_level(val,{c}) >= 0)
                    {
                        bool ok = scalc.calc_opt();
                        if(ok == false) { break; }
                    }
                    else { break; }
                }
                scalc._symbols.push(calc_object_t(false,false,true,{c}));
            }

        }
        
        while (scalc._symbols.empty() == false)
        {
            bool ok = scalc.calc_opt();
            if(ok == false) { break; }
        }

        if(scalc.verify_valid())
        {
            return scalc.get_result();
        }
        return calc_t();
    }

    static bool is_float(ccalc_t c)
    {
        if(c._is_float)
        {
            return true;
        }
        return false;
    }

    static double to_type_float(ccalc_t c)
    {  
        return Fbyte::Tfrom_string<double>(c._value);
    }

    static int64_t to_type_integer(ccalc_t c)
    {
        return Fbyte::Tfrom_string<int64_t>(c._value);
    }
};
#endif // FCALC_H