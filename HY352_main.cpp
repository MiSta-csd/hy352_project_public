/*
    HY-352 2021-22
    Minos Stavrakakis - csd4120
    Omiros Athanasakis - csd3906
*/

#include <stdio.h>
#include <iostream>
#include "MSGlang.h"



int main()
{

    let printf_impl = object[ // 
        func("printf") {
            int i = 0;
            for (auto& v : args_list) {
                std::cout << "val_" << i << "\t";
                std::cout << v << nl;
                ++i;
            }
            return none;
        }
    ];

    let o3 = object[call("printf"), values 1, "2", true, -3.14];
    myObject* optr = &o3;

    printf_impl["printf"].Get_method()(printf_impl, o3);



    objValue v1 = 7;
    objValue v2 = 33;

    std::cout << "\nv1 + v2 = " << v1 + v2 << nl;

    let ot1 = object[ /* call("+"), */ key("x") = 5, key("y") = 13, func("zpeos") {return none; }];
    std::cout << "\not1 = " << ot1 << nl << nl;

    let ot18 = object[call("+"), ref(ot1)];
    std::cout << "\not18 = " << ot18 << nl << nl;


    std::cout << "ot1[\"x\"] = " << ot1["x"] << nl;

    let ot1_5 = object[func("+") {
        std::cout << "ot1_5 method called!\n";
        return none;
    }];
    std::cout << "\not1_5 = " << ot1_5 << nl << nl;

    ot1_5["Pep"] = 17;
    std::cout << "\not1_5 = " << ot1_5 << nl << nl;


    let ot2 = object[key("x") = -2, key("y") = 7,
        func("+") {
        return object[
            key("x") = self(x) + arg(x),
                key("y") = self(y) + arg(y)
        ];
    }
    ];
    



    // Testing evals now ^^
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

     let connection = object[
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


    return 0;
}