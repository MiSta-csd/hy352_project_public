/*
    HY-352 2021-22
    Minos Stavrakakis - csd4120
*/

#include <stdio.h>
#include <iostream>
#include "MSGlang.h"

//using namespace std; std::

template <typename T>
T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

class myInt
{
private:
    int intVal = 0;

public:
    myInt()
    {
        this->intVal = 0;
    }
    myInt(int i)
    {
        this->intVal = i;
    }

    ~myInt()
    {
    }

    int Get_intVal() const
    {
        return this->intVal;
    }
    void Set_intVal(int i)
    {
        this->intVal = i;
    }

    myInt operator+(myInt& mi)
    {
        int a = this->intVal + mi.Get_intVal();
        return myInt(a);
    }
    myInt operator+(int i)
    {
        int a = this->intVal + i;
        return myInt(a);
    }

    myInt& operator,(int i)
    {
        // int a = this->intVal + i;
        // return myInt(a);

        this->intVal += i;
        return (*this);

        // myInt temp;
        // temp.intVal = i;
        // std::cout << "temp.intVal = " << temp.intVal <<nl;
        // return temp;
    }
    myInt& operator,(myInt& mi)
    {
        // int a = this->intVal + mi.Get_intVal();
        // return myInt(a);
        this->intVal += mi.Get_intVal();
        return (*this);
    }

    /* void operator,(myInt& mi)
        {
            this->intVal+=mi.Get_intVal();
        }
        void operator,(int i)
        {
            this->intVal+=i;
        } */

    myInt operator=(myInt& mi)
    {
        this->intVal = mi.Get_intVal();
        return (*this);
    }
    myInt operator=(int i)
    {
        this->intVal = i;
        return (*this);
    }

    friend std::ostream& operator<<(std::ostream& os, const myInt& mi)
    {
        os << mi.intVal;

        return os;
    }
};



template<class T> T Get_value(int i)
{
    if (i > 0)
    {
        return T;
    }
    else
    {
        return T;
    }
}

template <class T>
void tFunc(const T& msg)
{
    std::cout << "tFunc() prints: " << msg << nl << nl;
}






int main()
{

//     // let o1 = object [ key("st") = 7, key("xr") = true ];
//     // std::cout << "o1 = " << o1 << nl << nl;

//     // //(key("x") = o1);

//     // let oa = object [ values 1, "2", true, "Karvelas", lambda { std::cout << "This is a func^^!\n"; return none; } ];
//     // std::cout << "oa = " << oa << nl << nl;

//     // let oa2 = object [ call("Func()"), values 1, "2", true, "Karvelas", lambda { std::cout << "This is a func^^!\n"; return none; } ];
//     // std::cout << "oa2 = " << oa2 << nl << nl;

//     // let oa3 = object [ call("Papoutsi()"), key("x") = -1, key("y") = 2.00, key("z") = lambda {return none;}, 
//     //                     func("z2") { return none; }, key("al") = "Iaquinta" ];
//     // std::cout << "oa3 = " << oa3 << nl << nl;

//     // objValue ov1 = key("XXX");
//     // ov1 = o1;

//     // std::cout << "[ objValue ov1 ]"<< nl;
//     // std::cout << "type:\t"<< ov1.Get_type() << nl;
//     // std::cout << "key:\t" << ov1.Get_key() <<  nl;
//     // std::cout << "value:\t" << ov1 << nl << nl;

//     // let oa4 = object [ call("F2()"), key("alpha") = 92, key("beta") = false, key("v") = object [ values "Panthiras", 88, true, "Lakis" ] ];
//     // std::cout << "\noa4 = " << oa4 << nl << nl;

//     // oa4["x"] = 466;
//     // std::cout << "\noa4 = " << oa4 << nl << nl;



//     // std::map<std::string, objValue> umap2;
//     // std::string s1 = "Giagoulas";

//     // umap2["1"] = objValue(5);
//     // umap2["2"] = objValue("THalia");
//     // umap2["3"] = objValue();
//     // umap2["tasos"] = objValue(true);
//     // umap2["kwstas"] = objValue(3.14);
//     // umap2["34"] = objValue(s1);
//     // umap2["perdie"] = none;
//     // umap2.insert(std::make_pair("earth", objValue(7)));

//     // std::map<std::string, objValue> umap22;
//     // umap22["4"] = objValue("PERIERGO");
//     // //umap2 = umap22;   
//     // // Traversing an unordered map
//     // for (auto x : umap2){
//     //   std::cout << x.first << "\t\t ";
//     //   std::cout << x.second;
//     //   std::cout << std::endl;
//     // }

//     // oa4.Edit_valMap() = umap2;
//     // std::cout << "\noa4 = " << oa4 << nl << nl;

//     // std::string str3 = "Maria la del Bario Sol";
//     // oa4["2"] = str3;
//     // oa4["2"] = "GyftoMitros";
//     // std::cout << "\noa4 = " << oa4 << nl << nl;


//     // let o2 = object [ key("x") = o1 ];

//     // objValue ov1 = (key("x") = o1);
//     // std::cout << "[ ov1 ]"<< nl;
//     // std::cout << "type:\t"<< ov1.Get_type()<<nl;
//     // std::cout << (key("x") = o1) << nl;
//     // (key("x") = o1);
//     // let o3 = object;
//     // o3 = o1;

//     // std::cout << o3 << nl;


//     let printf_impl = object[ // 
//         func("printf") {
//             int i = 0;
//             for (auto& v : args_list) {
//                 std::cout << "val_" << i << "\t";
//                 std::cout << v << nl;
//                 ++i;
//             }
//             return none;
//         }
//     ];
//     std::cout << "\nprintf_impl = " << printf_impl << nl;;

//     let o3 = object[call("printf"), values 1, "2", true, -3.14];
//     std::cout << "\no3 = " << o3 << nl;

//     std::cout <<"\nprintf_impl << o3 result:\n";
//     printf_impl << o3;


//     let ot1 = object[ /* call("+"), */ key("x") = 5, key("y") = 13, func("zPapoutsi") {return none; }];
//     std::cout << "\not1 = " << ot1 << nl << nl;

//     // let ot18 = object[call("+"), ref(ot1)];
//     // std::cout << "\not18 = " << ot18 << nl << nl;


//     // std::cout << "ot1[\"x\"] = " << ot1["x"] << nl;

//     // let ot1_5 = object[func("+") {
//     //     std::cout << "ot1_5 method called!\n";
//     //     return none;
//     // }];
//     // std::cout << "\not1_5 = " << ot1_5 << nl << nl;

//     let ot2 = object[key("x") = -2, key("y") = 7,
//         func("+") {
//         return object[
//             key("x") = self(x) + arg(x),
//                 key("y") = self(y) + arg(y)
//         ];
//     }
//     ];

//     std::cout << "ot2 << ot1  =  " << (ot2 << object[call("+"), ref(ot1)]) << nl;
// /*     std::cout << "````````````````````````````````````````\n";
//     std::cout << "\n(_)_)IIIID ~.\n";
//     std::cout << "\nHow do you like ASCII dick!?\n"<<nl;
//     std::cout << "````````````````````````````````````````\n"; */

//     //objValue res = (ot2 << ot1);
//     //std::cout << "\nres = " << res << "  res type = " << res.Get_type() << nl;

//     // tFunc("JOJOJSJSSJSJS");

//     objValue ov13 = Get_value_from_user("x: ");
//     std::cout << "\nTesting input. \nInput type = " << ov13.Get_type() 
//                  << "\nInput value = " << ov13 << nl << nl;


//     objValue ov14 = objValue(7.2)++;
//     std::cout << "\nTesting objValues oveloads. \nInput type = " << ov14.Get_type() 
//                  << "\nInput value = " << ov14 << nl << nl;


//     // Testing evals now ^^
#define _cond_ "cond"
#define _success_ "success"
#define _failure_ "failure"

    let conn_impl = object [
        key("ip") = "127.0.0.1",
        key("port") = 3030,
        func("connect") {
            if(eval_cond(_cond_))
                eval(_success_)
            else
                eval(_failure_)
            return none;
        }
    ];
    let connection = object [
        call("connect"),
        key("ip") = "1.1.1.1",
        key("port") = 3030,
        func(_cond_) { return arg(port) == self(port); },
        func(_success_) {
            std::cout << arg(ip) << "connected to "
            << self(ip) << nl;
            return none;
        },
        func(_failure_) {
            std::cout << arg(ip) << "failed to connect to"
            << self(ip) << nl;
            return none;
        }
    ];

    conn_impl << connection;

#undef _cond_
#undef _success_ 
#undef _failure_ 


    let o1 = object [ key("x") = "Hello Katerina" ];

    let o2 = object [ key("a") = lambda { std::cout << arg(x) << nl; return 1 + 2 ; }, func("elenh") { return "lol"; } ];

    std::cout << o1 << nl;
    std::cout << o2 << nl;

    let o3 = object [ call("a"), key("o") = object [ key("x") = 2 ] ];
    std::cout << o3 << nl;

   

    objValue ov1 = o3["o"]["x"]["fdfd"];
    std::cout << "ov1 = " << ov1 << nl;


   return 0;
}