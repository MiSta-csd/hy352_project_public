/*
    HY-352 2021-22
    Minos Stavrakakis - csd4120
*/

#ifndef MSGLANG_H
#define MSGLANG_H

#define _CRT_SECURE_NO_WARNINGS

// #include "myObject.h"
// #include "objValue.h"

#include <iostream>
#include "string.h"
#include <ostream>
#include <assert.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>

// Predeclare Class
class myObject;
class valueGen;
class objValue;
// objValue enums
enum valType // If I have time will change it to enum class
{
    NONE = 0,
    INTEGER = 1,
    DOUBLE = 2,
    STRING = 3,
    BOOL = 4,
    FUNCTION = 5,
    OBJECT = 6,
    CALL = 7,    /* helps with call("printf") */
    DUMMY = 8,
    USER_UNDEFINED = 9  /* pretty much equals KEY */
};

std::ostream& operator<<(std::ostream& out, const valType value) {
    std::string s;
#define ENUM_TO_STR(p) case(p): s = #p; break;
    switch (value) {
        ENUM_TO_STR(NONE);
        ENUM_TO_STR(INTEGER);
        ENUM_TO_STR(DOUBLE);
        ENUM_TO_STR(STRING);
        ENUM_TO_STR(BOOL);
        ENUM_TO_STR(FUNCTION);
        ENUM_TO_STR(OBJECT);
        ENUM_TO_STR(CALL);
        ENUM_TO_STR(DUMMY);
    default: s = "UNDEFINED VALUE"; break;
    }
#undef ENUM_TO_STR

    return out << s;
}

enum keyType
{
    KEY = 66,
    CALL_ID = 67
};

//  Predecleration
std::vector<objValue> MapToVec(const std::map<std::string, objValue>& m);



//  #DEFINITIONS!
#define nl std::endl
#define let auto // used to be myObject
#define none objValue() // May have to remove semicolon // EDIT:I did removed it
#define values objValue(DUMMY, true),
#define object myObject()
#define key(name) objValue(KEY, name)
#define call(name) objValue(CALL_ID, name)
#define strfy(x) #x
/*  ~~~~ Always have to precede lambda definition ~~~~ */
#define self(name) receiver[strfy(name)]    // 2 different ways
#define arg(name) sender[#name]             // to do the same thing ^^
/*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define lambda objValue() = [](myObject& receiver, myObject& sender)
#define func(name) key(name) = lambda
/*  ~~~~~~ Always comes after lambda definition ~~~~~~ */
#define args_list MapToVec(sender.Get_valMap()) // TODO Remains to be checked! // Might have to change . to ->
/*  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define input(name) Get_value_from_user(name)
#define ref(name) &##name
#define eval(name) sender << (object [ call(name), ref(receiver) ]); // A tropos
// #define eval(name) sender << (receiver.Set_callFunc(name)) // B tropos
#define eval_cond(name) (sender << (object [ call(name), ref(receiver) ])).Get_boolVal()
// #define eval_cond(name) (sender << receiver).Get_boolVal()
//Typedefs
typedef std::function<objValue(myObject&, myObject&)> myFunc;





// objValue CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class objValue
{
private:

    enum valType type;
    int intVal;
    double doubleVal;
    std::string stringVal;  // Also used to store CALL_F_ID
    bool boolVal;
    myObject* objVal = nullptr;
    myFunc funcVal; /* myFunc typedefed in the begging of file */
    std::string key;

public:

    // Constructors
    // generic ctor
    objValue();
    // ``````````````````````````````````````````````````
    // Lots of trickery in these ctors !
    //  when keyType=KEY it sets objValue.key
    //  when keyType=CALL_ID it sets callId into stringVal
    objValue(enum keyType kT, char* cptr);
    // 2nd call ctor // arg = std::string
    objValue(enum keyType kT, std::string s);
    // DUMMY ctor
    objValue(enum valType t, bool b); // bool added to distinguish between int_ctor and this
    // ``````````````````````````````````````````````````
    // Copy ctor
    objValue(const objValue& ov);
    // int ctor
    objValue(const int& i);
    // double ctor
    objValue(const double& d);
    // bool ctor
    objValue(const bool& b);
    // string ctor
    objValue(const std::string& s);
    // !Tricky! const char [] ctor
    objValue(const char* s);
    // !More Trickery! single char ctor // If true to exercise guidelines never to be used!
    objValue(const char& s);
    // myObj ctor 
    objValue(const myObject& o);
    // myfunction ctor
    objValue(const myFunc& f);

    // myObj dtor
    ~objValue();



    // SETTERS | GETTERS

    std::string Get_CALL_F_ID() const; // This function is useless Get_stringVal does the same though fname should help w code clarity

    enum valType Get_type() const;
    void Set_type(const enum valType& t);

    int Get_intVal() const;
    void Set_intVal(const int& i);

    double Get_doubleVal() const;
    void Set_doubleVal(const double& d);

    std::string Get_stringVal() const;
    void Set_stringVal(const std::string& s);
    void Set_stringVal(const char* cptr);
    
    bool Get_boolVal() const;
    void Set_boolVal(const bool& b);


    myObject* Get_objVal() const;
    void Set_objVal(const myObject*& o);// Had to be implemented after myObject class def  // would have wanted to take const & arg but do not know how //UPDATE: Nevermind that ;)

    std::string Get_key() const;
    void Set_key(const char* cptr);
    void Set_key(const std::string& s);

    myFunc Get_method() const;
    void Set_method(const myFunc& f);

    // Operator Oveloads
    friend std::ostream& operator<<(std::ostream& os, const objValue& ov);

    objValue& operator=(const objValue& ov);
    objValue& operator=(const int& i);
    objValue& operator=(const double& d);
    objValue& operator=(const bool& b);
    objValue& operator=(const char* cptr);
    objValue& operator=(const std::string& s);
    objValue& operator=(const myObject& o);
    objValue& operator=(const myFunc& f);
    // for turnin call -> objVal -> valueGen
    valueGen operator,(const valueGen& vg); // TODO check if works properly after objValue,objValue overload
    valueGen operator,(const objValue& ov);
    valueGen operator,(const int& i);
    valueGen operator,(const double& d);
    valueGen operator,(const bool& b);
    valueGen operator,(const char* c);
    valueGen operator,(const std::string& s);
    valueGen operator,(const myFunc& f);
    valueGen operator,(const myObject& o);
    valueGen operator,(myObject* o);

    objValue& operator[](const char* cptr);

    // fdf
    // Some overloads on the spot (Time is pressing..)
    objValue operator+(const objValue& ov);
    objValue operator+(const int& i);  ///  objval + 23        55 + objVal
    objValue operator+(const double& d);
    objValue operator+(const float& d);
    objValue operator+(const std::string& s);
    objValue operator-(const objValue& ov);
    objValue operator-(const int& i);
    objValue operator-(const double& d);
    objValue operator-(const float& d);
    objValue operator*(const objValue& ov);
    objValue operator*(const int& i);
    objValue operator*(const double& d);
    objValue operator*(const float& d);
    objValue operator==(const objValue& ov);
    objValue operator==(const int& i);
    objValue operator==(const double& d);
    objValue operator==(const float& d);
    objValue operator==(const bool& b);
    objValue operator&&(const bool& b);
    objValue operator&&(const objValue& ov);
    objValue operator||(const bool& b);
    objValue operator||(const objValue& ov);
    objValue operator==(const std::string& s);
    objValue operator!=(const objValue& ov);
    objValue operator!=(const int& i);
    objValue operator!=(const double& d);
    objValue operator!=(const float& d);
    objValue operator!=(const bool& b);
    objValue operator!=(const std::string& s);
    objValue operator/(const objValue& ov);
    objValue operator/(const int& i);
    objValue operator/(const double& d);
    objValue operator/(const float& d);
    objValue operator%(const objValue& ov);
    objValue operator%(const int& i);
    objValue& operator++();
    objValue  operator++(int);
    //objValue operator++(double); // Does not work
    //
    // friend std types overloads
    friend objValue operator+(const int& i, const objValue& ov);
    friend objValue operator+(const double& d, const objValue& ov);
    friend objValue operator+(const float& d, const objValue& ov);
    friend objValue operator-(const int& i, const objValue& ov);
    friend objValue operator-(const double& d, const objValue& ov);
    friend objValue operator-(const float& d, const objValue& ov);
    friend objValue operator*(const int& i, const objValue& ov);
    friend objValue operator*(const double& d, const objValue& ov);
    friend objValue operator*(const float& d, const objValue& ov);
    friend objValue operator==(const int& i, const objValue& ov);
    friend objValue operator==(const double& d, const objValue& ov);
    friend objValue operator==(const float& d, const objValue& ov);
    friend objValue operator==(const bool& b, const objValue& ov);
    friend objValue operator&&(const bool& b, const objValue& ov);
    friend objValue operator||(const bool& b, const objValue& ov);
    friend objValue operator==(const std::string& s, const objValue& ov);
    friend objValue operator!=(const int& i, const objValue& ov);
    friend objValue operator!=(const double& d, const objValue& ov);
    friend objValue operator!=(const float& d, const objValue& ov);
    friend objValue operator!=(const bool& b, const objValue& ov);
    friend objValue operator!=(const std::string& s, const objValue& ov);
    friend objValue operator/(const int& i, const objValue& ov);
    friend objValue operator/(const double& d, const objValue& ov);
    friend objValue operator/(const float& d, const objValue& ov);
    friend objValue operator%(const int& i, const objValue& ov);

};




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




// myObject CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class myObject
{
private:
    /* data */
    std::string callFuncId; //if(callFuncId.empty()){ do stuff } // As it is declared, it is emprty
    std::map<std::string, objValue> valMap;
    int value_id_counter = 0;
    myObject* targetObj = nullptr;
    /* std::vector<std::string> keyVec; */  // NOT NEEDED, MAP STORES KEY VALUES BY DEFAULT

public:
    // CTORS / DTORS ~~~~~~~~~~~~~~~~~~~~~~~~~~
    myObject();
    myObject(const myObject& o);
    myObject(std::vector<objValue> v); // Not needed except for testing now
    myObject(const valueGen& vg);

    ~myObject();

    // SETTERS / GETTERS ~~~~~~~~~~~~~~~~~~~~~~
    void Set_callFunc(const std::string& s);
    void Set_callFunc(const char* cptr);
    std::string Get_callFuncId() const;

    int Get_value_id_counter() const;

    std::map<std::string, objValue> Get_valMap() const; // TODO Change definition: Now return type = reference and removed const
    std::map<std::string, objValue>& Edit_valMap();

    myObject* Get_targetObj() const;
    /* std::vector<std::string>& GetSet_keyVec(); */ // NOT NEEDED, MAP STORES KEY VALUES BY DEFAULT

    // OPERATOR OVERLOADS ~~~~~~~~~~~~~~~~~~~~~
    friend std::ostream& operator<<(std::ostream& os, const myObject& o)
    {
        os << "object [ ";
        /* ~~~~~~ This is for testing purposes, can be skipped ~~~~~~ */
        if (!(o.Get_callFuncId().empty()))
        {
            os << "CALLING(" << "\""
                << o.Get_callFuncId() << "\")" << " | ";
        }
        /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        std::string separator; // sperator non-initialization: Such a cool trick to print ^^
        for (auto x : o.Get_valMap()) {

            os << separator << "\"" << x.first << "\"" << ":";
            os << x.second;
            //os << " , ";
            separator = " , ";
        }
        os << " ]";
        return os;
    }
    myObject& operator=(const myObject& o);
    myObject& operator[](const valueGen& vg);
    myObject& operator[](const objValue& ov);
    objValue& operator[](const char* cptr);
    objValue& operator[](const std::string s);
    objValue operator<<(myObject& sender)// koko
    {
        objValue tmp;
        std::string callID = sender.Get_callFuncId();
        myFunc f;

        if (this->valMap.find(callID) == this->valMap.end())
        {
            // not found
            std::cout << "MESSAGE FAIL: receiver doesn't have a member method with requested call ID.\n";
        }
        else
        {
            // found
            if (this->valMap[callID].Get_type() == FUNCTION)
            {
                f = this->valMap[callID].Get_method(); // Miesha Tate
                tmp = f(*this, sender);
            }
            else
            {
                std::cout << "MESSAGE FAIL: Given call ID does not correspond to a method member.\n";
            }

        }
        return tmp;
    }
};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     Values Generator Class
class valueGen
{
    // private:
    //     std::vector<objValue> valVector;

public:
    std::vector<objValue> valVector; // public so it can be accessible
    // CTORs / DTORs
    valueGen()
    {
        ;
    }
    valueGen(const valueGen& vg) // not const because of GetSet_valVector
    {
        // append to vector
        //this->valVector.insert(this->valVector.end(),vg.GetSet_valVector().begin(), vg.GetSet_valVector().end());
        // Turned to be useless :P

        this->valVector = vg.valVector;
    }
    ~valueGen() {
        this->valVector.clear();            // Those 2 lines seem 
        this->valVector.shrink_to_fit();    // to be unneseccary
    }

    /*         std::vector<objValue>& GetSet_valVector()   // this equals to vg.valvector in essence
            {                                           // !!! Might be dangerous !!!
                return this->valVector;
            } */

            // Operator Overloads
            //
    valueGen& operator=(const valueGen& vg)
    {
        this->valVector = vg.valVector;
        return (*this);
    }

    // COMMA OVERLOADS!
    // comma , int
    valueGen& operator, (const int& i)
    {
        objValue ov = objValue(i);
        this->valVector.push_back(ov);
        return (*this);
    }
    // comma , double
    valueGen& operator, (const double& d)
    {
        objValue ov = objValue(d);
        this->valVector.push_back(ov);
        return (*this);
    }
    // comma , bool
    valueGen& operator, (const bool& b)
    {
        objValue ov = objValue(b);
        this->valVector.push_back(ov);
        return (*this);
    }
    // comma , string
    valueGen& operator, (const std::string& s)
    {
        objValue ov = objValue(s);
        this->valVector.push_back(ov);
        return (*this);
    }
    // comma , char*
    valueGen& operator, (const char* s)
    {
        objValue ov = objValue(s);      // gets handled by objval(char *) ctor 
        this->valVector.push_back(ov);
        return (*this);
    }
    // comma , char ..because morons exist..
    valueGen& operator, (const char& s)
    {
        objValue ov = objValue(s);      // gets handled by objval(char) ctor 
        this->valVector.push_back(ov);
        return (*this);
    }
    valueGen& operator, (objValue aris) // So as 'none' can be used as obj init value
    {
        objValue ov = aris; // Handles only none type ftm // NOT! Now handles everything
        this->valVector.push_back(ov);
        return (*this);
    }
    // NO valueGen& operator, (myFunc f ) because if follow correct programm syntax myFunc is always going to be 'attached' to an objValue

};







// objVal function implementations ~~~~~~~~~~~~~~~~~
// CTOR / DTOR
//
// generic ctor : creates NONE
objValue::objValue()
{
    this->Set_type(NONE);
}
// ``````````````````````````````````````````````````
// Lots of trickery in these ctors !
//  when keyType=KEY it sets objValue.key
//  when keyType=CALL_ID it sets callId into stringVal
objValue::objValue(enum keyType kT, char* cptr)
{
   std::string s(cptr);
    switch (kT)
    {
    case KEY:
        this->key = s;
        this->type = USER_UNDEFINED;
        break;
    case CALL_ID:
        this->stringVal = s;
        this->type = CALL;
        break;
    default:
        std::cout << "\nERROR: objValue(key, cptr) ctor failed!"
            << std::endl;
        break;
    }
}
// 2nd call ctor // just to be sure
objValue::objValue(enum keyType kT, std::string s)
{
    switch (kT)
    {
    case KEY:
        this->key = s;
        this->type = USER_UNDEFINED;
        break;
    case CALL_ID:
        this->stringVal = s;
        this->type = CALL;
        break;
    default:
        std::cout << "\nERROR: objValue(key, str) ctor failed!"
            << std::endl;
        break;
    }
}
// DUMMY ctor
objValue::objValue(enum valType t, bool b) // bool added to distinguish between int_ctor and this
{
    if ((t == DUMMY) && (b == true))
    {
        this->type = DUMMY;
    }
    else
    {
        std::cout << "ERROR: DUMMY ctor failed!\n";
    }
}
// myObj ctor // Not in use anymore
/* objValue::objValue(myObject o)
{
    this->objVal = new myObject(o);
    this->Set_type(OBJECT);
} */
// COPY ctor
objValue::objValue(const objValue& ov)
{
    this->type = ov.Get_type();
    this->key = ov.Get_key();
    switch (ov.type)
    {
    case NONE:
        break;

    case INTEGER:
        this->intVal = ov.intVal;
        break;

    case DOUBLE:
        this->doubleVal = ov.doubleVal;
        break;

    case STRING:
        this->stringVal = ov.stringVal;
        break;

    case BOOL:
        this->boolVal = ov.boolVal;
        break;

    case FUNCTION:
        this->funcVal = ov.funcVal;
        break;

    case OBJECT:
        this->objVal = new myObject(*ov.objVal); // Seems to be working
        break;

    case CALL:
        // std::cout << "\n objValue::objValue(const objValue& ov): I shouldn't be here..\n";
        this->stringVal = ov.stringVal;
        // std::cout << "I copied the call_ID to stringVal nevertheless\n";
        break;

    case DUMMY:
        // std::cout << "\n objValue::objValue(const objValue& ov): I shouldn't be here..\n";
        break;

    default:
        this->key = ov.Get_key(); // USER UNDEFINED = key
        break;
    }

}
// int ctor
objValue::objValue(const int& i)
{
    this->intVal = i;
    this->type = INTEGER;
}
// double ctor
objValue::objValue(const double& d)
{
    this->doubleVal = d;
    this->type = DOUBLE;
}
// bool ctor
objValue::objValue(const bool& b)
{
    this->Set_boolVal(b);
    this->Set_type(BOOL);
}
// string ctor
objValue::objValue(const std::string& s)
{
    this->stringVal = s;
    this->type = STRING;
}
// !Tricky! const char [] ctor
objValue::objValue(const char* s)
{
    std::string str(s);
    this->stringVal = str;
    this->type = STRING;
}
// !More Trickery! single char ctor // If true to exercise guidelines never to be used!
objValue::objValue(const char& s)
{
    std::string str(1, s);
    this->stringVal = str;
    this->type = STRING;
}
// function ctor
objValue::objValue(const myFunc& f)
{
    this->funcVal = f;
    this->Set_type(FUNCTION);
}
// myObj ctor 
objValue::objValue(const myObject& o)
{
    this->objVal = new myObject(o);
    this->type = OBJECT;
}
// DTOR
objValue::~objValue()
{
    if (this->objVal != nullptr)
    {
        delete this->objVal;
        //this->objVal->~myObject(); //HAD this but delete handles it
        //this->objVal = nullptr;
    }
}

// 
// Setters / Getters
std::string objValue::Get_CALL_F_ID() const // This function is useless Get_stringVal does the same though fname should help w code clarity
{
    return this->stringVal;
}
enum valType objValue::Get_type() const
{
    return this->type;
}
void objValue::Set_type(const enum valType& t)
{
    this->type = t;
}

int objValue::Get_intVal() const
{
    return this->intVal;
}
void objValue::Set_intVal(const int& i)
{
    this->intVal = i;
}

double objValue::Get_doubleVal() const
{
    return this->doubleVal;
}
void objValue::Set_doubleVal(const double& d)
{
    this->doubleVal = d;
}

std::string objValue::Get_stringVal() const
{
    return this->stringVal;
}
void objValue::Set_stringVal(const std::string& s)
{
    this->stringVal = s;
}
void objValue::Set_stringVal(const char* cptr)
{
    std::string s(cptr);
    this->stringVal = s;
}
bool objValue::Get_boolVal() const
{
    return this->boolVal;
}
void objValue::Set_boolVal(const bool& b)
{
    this->boolVal = b;
}

myObject* objValue::Get_objVal() const
{
    return this->objVal;
}
void objValue::Set_objVal(const myObject*& o) // would have wanted to take const & arg but do not know how //UPDATE: Nevermind that ;)
{
    if (this->Get_objVal() != nullptr)
    {
        delete this->objVal;
    }
    assert(o);
    this->objVal = new myObject(*o);
}

std::string objValue::Get_key() const
{
    return this->key;
}
void objValue::Set_key(const char* cptr)
{
    std::string s(cptr);
    this->key = s;
}
void objValue::Set_key(const std::string& s)
{
    this->key = s;
}
myFunc objValue::Get_method() const
{
    return this->funcVal;
}
void objValue::Set_method(const myFunc& f)
{
    this->funcVal = f;
}

//
// operator Overloads
std::ostream& operator<<(std::ostream& os, const objValue& ov)
{
    switch (ov.Get_type())
    {
    case NONE:
        os << "NO VALUE";
        break;
    case INTEGER:
        os << ov.Get_intVal();
        break;
    case DOUBLE:
        os << ov.Get_doubleVal();
        break;
    case STRING:
        os << "\"" << ov.Get_stringVal() << "\"";
        break;
    case BOOL:
        ov.Get_boolVal() ? os << "true" : os << "false";
        break;
    case FUNCTION:
        os << "method";
        break;
    case OBJECT:
        os << (*ov.Get_objVal()); //"I am an Object!";
        break;
    case CALL:
        os << ov.Get_stringVal();
        break;
    case DUMMY:
        os << "DUMMY";
        break;
    default:
        os << "UNDEFINED VALUE";
        break;
    }
    return os;
}

objValue& objValue::operator=(const objValue& ov)
{
    if ((this->type == OBJECT) && (this->objVal != nullptr))
    {
        delete this->objVal;
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */

    this->type = ov.Get_type();
    switch (ov.type)
    {
    case NONE:
        break;

    case INTEGER:
        this->intVal = ov.intVal;
        break;

    case DOUBLE:
        this->doubleVal = ov.doubleVal;
        break;

    case STRING:
        this->stringVal = ov.stringVal;
        break;

    case BOOL:
        this->boolVal = ov.boolVal;
        break;

    case FUNCTION:
        this->funcVal = ov.funcVal;
        break;

    case OBJECT:
        this->objVal = new myObject(*ov.objVal); // Seems to be working
        break;

    case CALL:
        std::cout << "\n objValue objValue::operator=(const objValue& ov): I shouldn't be here..\n";
        this->stringVal = ov.stringVal;
        break;

    case DUMMY:
        std::cout << "\n objValue objValue::operator=(const objValue& ov): I shouldn't be here..\n";
        break;

    default:
        // this->key = ov.Get_key(); // USER UNDEFINED = key // this line seems to fuck up things
        break;
    }

    return (*this);
}

objValue& objValue::operator=(const int& i)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */
    this->type = INTEGER;
    this->intVal = i;
    return (*this);
}

objValue& objValue::operator=(const double& d)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */
    this->type = DOUBLE;
    this->doubleVal = d;
    return (*this);
}

objValue& objValue::operator=(const bool& b)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */
    this->type = BOOL;
    this->boolVal = b;
    return (*this);
}

objValue& objValue::operator=(const char* cptr)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        this->objVal = nullptr;
    }
    std::string s(cptr);
    this->type = STRING;
    this->stringVal = s;
    return (*this);
}

objValue& objValue::operator=(const std::string& s)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */
    this->type = STRING;
    this->stringVal = s;
    return (*this);
}

objValue& objValue::operator=(const myObject& o)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        // this->objVal->~myObject(); // Deprecated
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */
    this->type = OBJECT; // Superfluous but whatever..
    this->objVal = new myObject(o);
    //return (*this);
    return (*this);
}

objValue& objValue::operator=(const myFunc& f)
{
    if (this->type == OBJECT) {
        delete this->objVal;
        this->objVal = nullptr;
    } /* MAY have to address type = FUNCTION to prevent mem leaks */
    this->type = FUNCTION;
    this->funcVal = f;
    return (*this);
}

// This shouldn't be needed after objVal,objVal overload !
valueGen objValue::operator,(const valueGen& vg) // TODO check if working after objValue,objValue overload 
{
    valueGen tmpVg = valueGen(vg);
    tmpVg.valVector.push_back(*this);
    return tmpVg;
}

valueGen objValue::operator,(const objValue& ov)
{
    valueGen tmpVg = valueGen();
    if ((this->type == CALL) && (ov.Get_type() == DUMMY))
    {
        tmpVg.valVector.push_back(*this);
    }
    else if ((this->type == CALL) && (ov.Get_type() != DUMMY) && (ov.Get_type() != CALL))
    {
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
    }
    else if ((this->type == DUMMY) && (ov.Get_type() != DUMMY) && (ov.Get_type() != CALL))
    {
        tmpVg.valVector.push_back(ov);
    }
    else if (((this->type != DUMMY) && (this->type != CALL)) &&
        ((ov.Get_type() != DUMMY) && (ov.Get_type() != CALL)))
        // Case where objValue,objValue => valGen
    {
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
    }
    else { std::cout << "ERROR: @ objValue::operator,() : Undefined Scenario!\n"; }
    return tmpVg;
}

valueGen objValue::operator,(const int& i)
{
    //std::cout << "\nEntered valueGen objValue::operator,(int i)\n";// For testing
    objValue ov = objValue(i);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;
}

valueGen objValue::operator,(const double& d)
{
    objValue ov = objValue(d);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;;
}

valueGen objValue::operator,(const bool& b)
{
    objValue ov = objValue(b);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;
}

valueGen objValue::operator,(const char* c)
{
    objValue ov = objValue(c);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;
}

valueGen objValue::operator,(const std::string& s)
{
    objValue ov = objValue(s);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;
}
valueGen objValue::operator,(const myFunc& f)
{
    objValue ov = objValue(f);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;
}

valueGen objValue::operator,(const myObject& o)
{
    objValue ov = objValue(o);
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;

    case DUMMY:
        tmpVg.valVector.push_back(ov);
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        tmpVg.valVector.push_back(ov);
        break;
    }

    return tmpVg;
}

valueGen objValue::operator,(myObject* o)
{
    //objValue ov = *o;
    
    valueGen tmpVg = valueGen();

    switch (this->type)
    {
    case CALL:
        tmpVg.valVector.push_back(*this);
        for (auto& h : (*o).Get_valMap())
        {
            objValue ov;
            ov.Set_key(h.first);
            ov = h.second;
            tmpVg.valVector.push_back(ov);
        }
        break;

    case DUMMY:
        for (auto& h : (*o).Get_valMap())
        {
            objValue ov;
            ov.Set_key(h.first);
            ov = h.second;
            tmpVg.valVector.push_back(ov);
        }
        break;

    default: // legit objVal,legit objVal
        tmpVg.valVector.push_back(*this);
        for (auto& h : (*o).Get_valMap())
        {
            objValue ov;
            ov.Set_key(h.first);
            ov = h.second;
            tmpVg.valVector.push_back(ov);
        }
        break;
    }

    return tmpVg;
}

objValue& objValue::operator[](const char* cptr)
{
    // objValue ovTmp = new none;
    std::string s(cptr);
    if(this->type == OBJECT)
        return this->objVal->Edit_valMap()[s];
    else{
        std::cout << "ERROR: Invalid/Non-existent key value." << std::endl;
        return *this;
    }
}

// More Operator Overloads^^
objValue objValue::operator+(const objValue& ov)
{
    objValue res = none;
    if (this->type == INTEGER)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->intVal + ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->intVal + ov.Get_doubleVal());
        }
    }
    else if (this->type == DOUBLE)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->doubleVal + ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->doubleVal + ov.Get_doubleVal());
        }
    }
    else if (this->type == STRING && ov.Get_type() == STRING)
    {
        res = (this->stringVal + ov.Get_stringVal());
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator+(const int& i)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal + i);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal + i);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator+(const double& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal + d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal + d);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator+(const float& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal + d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal + d);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator+(const std::string& s)
{
    objValue res;
    if (this->type == STRING)
    {
        res = (this->stringVal + s);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator-(const objValue& ov)
{
    objValue res = none;
    if (this->type == INTEGER)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->intVal - ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->intVal - ov.Get_doubleVal());
        }
    }
    else if (this->type == DOUBLE)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->doubleVal - ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->doubleVal - ov.Get_doubleVal());
        }
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator-(const int& i)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal - i);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal - i);
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator-(const double& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal - d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal - d);
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator-(const float& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal - d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal - d);
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator*(const objValue& ov)
{
    objValue res = none;
    if (this->type == INTEGER)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->intVal * ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->intVal * ov.Get_doubleVal());
        }
    }
    else if (this->type == DOUBLE)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->doubleVal * ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->doubleVal * ov.Get_doubleVal());
        }
    }
    else
    {
        std::cout << "ERROR: operator* not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator*(const int& i)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal * i);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal * i);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator*(const double& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal * d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal * d);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator*(const float& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal * d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal * d);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator==(const objValue& ov)
{
    objValue res = false;
    if (this->type == ov.Get_type())
    {
        switch (type)
        {
        case NONE:
            break;
        case INTEGER:
            res = (this->intVal == ov.intVal);
            break;
        case DOUBLE:
            res = (this->doubleVal == ov.doubleVal);
            break;
        case STRING:
            res = (this->stringVal == ov.stringVal);
            break;
        case BOOL:
            res = (this->boolVal = ov.boolVal);
            break;
            /* case FUNCTION:
                this->funcVal = ov.funcVal;
                break;
            case OBJECT:
                this->objVal = new myObject(*ov.objVal); // Seems to be working
                break;
            case CALL:
                // std::cout << "\n objValue::objValue(const objValue& ov): I shouldn't be here..\n";
                this->stringVal = ov.stringVal;
                // std::cout << "I copied the call_ID to stringVal nevertheless\n";
                break;
            case DUMMY:
                // std::cout << "\n objValue::objValue(const objValue& ov): I shouldn't be here..\n";
                break; */
        default:
            std::cout << "ERROR: operator== not defined for given types!\n";
            break;
        }
    }
    return res;
}

objValue objValue::operator==(const int& i)
{
    objValue res = false;
    if (this->type == INTEGER)
    {
        res = (this->intVal == i);
    }
    return res;
}

objValue objValue::operator==(const double& d)
{
    objValue res = false;
    if (this->type == DOUBLE)
    {
        res = (this->doubleVal == d);
    }
    return res;
}

objValue objValue::operator==(const float& d)
{
    objValue res = false;
    if (this->type == DOUBLE)
    {
        res = (this->doubleVal == d);
    }
    return res;
}

objValue objValue::operator==(const bool& b)
{
    objValue res = false;
    if (this->type == BOOL)
    {
        res = (this->boolVal == b);
    }
    return res;
}

objValue objValue::operator&&(const bool& b)
{
    objValue res = false;
    if (this->type == BOOL)
    {
        res = (this->boolVal && b);
    }
    return res;
}

objValue objValue::operator&&(const objValue& ov)
{
    objValue tmp;
    if ((this->type == BOOL) && (ov.Get_type() == BOOL))
    {
        tmp = (this->boolVal && ov.Get_boolVal());
    }
    else
        tmp = false;
    return tmp;
}

objValue objValue::operator||(const bool& b)
{
    objValue res = false;
    if (this->type == BOOL)
    {
        res = (this->boolVal || b);
    }
    return res;
}
// Following might need logic revision
objValue objValue::operator||(const objValue& ov)
{
    objValue tmp;
    if ((this->type == BOOL) && (ov.Get_type() == BOOL))
    {
        tmp = (this->boolVal || ov.Get_boolVal());
    }
    else
        tmp = false;
    return tmp;
}

objValue objValue::operator==(const std::string& s)
{
    objValue tmp;
    if (this->type == STRING)
    {
        tmp = (this->stringVal == s);
    }
    else
        tmp = false;
    return tmp;
}

objValue objValue::operator!=(const objValue& ov)
{
    objValue res = false;
    if (this->type != ov.Get_type())
    {
        switch (type)
        {
        case NONE:
            break;
        case INTEGER:
            res = (this->intVal != ov.intVal);
            break;
        case DOUBLE:
            res = (this->doubleVal != ov.doubleVal);
            break;
        case STRING:
            res = (this->stringVal != ov.stringVal);
            break;
        case BOOL:
            res = (this->boolVal != ov.boolVal);
            break;
            /* case FUNCTION:
                this->funcVal = ov.funcVal;
                break;
            case OBJECT:
                this->objVal = new myObject(*ov.objVal); // Seems to be working
                break;
            case CALL:
                // std::cout << "\n objValue::objValue(const objValue& ov): I shouldn't be here..\n";
                this->stringVal = ov.stringVal;
                // std::cout << "I copied the call_ID to stringVal nevertheless\n";
                break;
            case DUMMY:
                // std::cout << "\n objValue::objValue(const objValue& ov): I shouldn't be here..\n";
                break; */
        default:
            std::cout << "ERROR: operator!= not defined for given types. Aborted.\n";
            break;
        }
    }
    return res;
}

objValue objValue::operator!=(const int& i)
{
    objValue res = false;
    if (this->type == INTEGER)
    {
        res = (this->intVal != i);
    }
    return res;
}

objValue objValue::operator!=(const double& d)
{
    objValue res = false;
    if (this->type == DOUBLE)
    {
        res = (this->doubleVal != d);
    }
    return res;
}

objValue objValue::operator!=(const float& d)
{
    objValue res = false;
    if (this->type == DOUBLE)
    {
        res = (this->doubleVal != d);
    }
    return res;
}

objValue objValue::operator!=(const bool& b)
{
    objValue res = false;
    if (this->type == BOOL)
    {
        res = (this->boolVal != b);
    }
    return res;
}

objValue objValue::operator!=(const std::string& s)
{
    objValue res = false;
    if (this->type == STRING)
    {
        res = (this->stringVal != s);
    }
        return res;
}

objValue objValue::operator/(const objValue& ov)
{
    objValue res = none;
    if (this->type == INTEGER)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->intVal / ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->intVal / ov.Get_doubleVal());
        }
    }
    else if (this->type == DOUBLE)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->doubleVal / ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            res = (this->doubleVal / ov.Get_doubleVal());
        }
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue objValue::operator/(const int& i)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal / i);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal / i);
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;

}

objValue objValue::operator/(const double& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal / d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal / d);
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;

}

objValue objValue::operator/(const float& d)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal / d);
    }
    else if (this->type == DOUBLE)
    {
        res = (this->doubleVal / d);
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;

}

objValue objValue::operator%(const objValue& ov)
{
    objValue res = none;
    if (this->type == INTEGER)
    {
        if (ov.Get_type() == INTEGER)
        {
            res = (this->intVal % ov.Get_intVal());
        }
        else if (ov.Get_type() == DOUBLE)
        {
            std::cout << "ERROR: operator% not defined for given types. Aborted.\n";
        }
    }
    else
    {
        std::cout << "ERROR: operator% not defined for given types. Aborted.\n";

    }
    return res;
}

objValue objValue::operator%(const int& i)
{
    objValue res = 0;
    if (this->type == INTEGER)
    {
        res = (this->intVal % i);
    }
    else
    {
        std::cout << "ERROR: operator% not defined for given types. Aborted.\n";
    }
    return res;
}

objValue& objValue::operator++()
{
    switch (this->type)
    {
    case INTEGER:
        ++this->intVal;
        break;

    case DOUBLE:
        ++this->doubleVal;
        break;

    default:
        std::cout << "ERROR: operator++ not defined for given type. Aborted.\n";
        break;
    }
    return (*this);
}

objValue objValue::operator++(int)
{
    objValue tmp = (*this);
    int i = tmp.Get_intVal();
    double d = tmp.Get_doubleVal();
    switch (tmp.Get_type())
    {
    case INTEGER:
        tmp.Set_intVal(++i);
        break;
    case DOUBLE:
        tmp.Set_doubleVal(++d);
        break;
    default:
        std::cout << "ERROR: operator++ not defined for given type. Aborted.\n";
        break;
    }
    return tmp;
}

//
// friend std types overloads
objValue operator+(const int& i, const objValue& ov)
{
    objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (ov.Get_intVal() + i);
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() + i);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator+(const double& d, const objValue& ov)
{
    objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (ov.Get_intVal() + d);
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() + d);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator+(const float& d, const objValue& ov)
{
    objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (ov.Get_intVal() + d);
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() + d);
    }
    else
    {
        std::cout << "ERROR: operator+ not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator-(const int& i, const objValue& ov)
{
        objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (i - ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (i - ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator-(const double& d, const objValue& ov)
{
    objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (d - ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (d - ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator-(const float& d, const objValue& ov)
{
    objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (d - ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (d - ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator*(const int& i, const objValue& ov)
{
        objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (i * ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (i * ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator*(const double& d, const objValue& ov)
{
        objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (d * ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (d * ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator*(const float& d, const objValue& ov)
{
        objValue res = objValue(); // initialize as 'none'
    if (ov.Get_type() == INTEGER)
    {
        res = (d * ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (d * ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator- not defined for given types. Aborted.\n";
    }
    return res;
}

objValue operator==(const int& i, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == INTEGER)
    {
        res = (ov.Get_intVal() == i);
    }
    return res;
}

objValue operator==(const double& d, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() == d);
    }
    return res;
}

objValue operator==(const float& d, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() == d);
    }
    return res;
}

objValue operator==(const bool& b, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == BOOL)
    {
        res = (ov.Get_boolVal() == b);
    }
    return res;
}

objValue operator&&(const bool& b, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == BOOL)
    {
        res = (ov.Get_boolVal() && b);
    }
    return res;
}

objValue operator||(const bool& b, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == BOOL)
    {
        res = (ov.Get_boolVal() || b);
    }
    return res;
}
objValue operator==(const std::string& s, const objValue& ov)
{
    objValue tmp;
    if (ov.Get_type() == STRING)
    {
        tmp = (ov.Get_stringVal() == s);
    }
    else
        tmp = false;
    return tmp;
}

objValue operator!=(const int& i, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == INTEGER)
    {
        res = (ov.Get_intVal() != i);
    }
    return res;
}

objValue operator!=(const double& d, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() != d);
    }
    return res;
}

objValue operator!=(const float& d, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == DOUBLE)
    {
        res = (ov.Get_doubleVal() != d);
    }
    return res;
}

objValue operator!=(const bool& b, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == BOOL)
    {
        res = (ov.Get_boolVal() != b);
    }
    return res;
}

objValue operator!=(const std::string& s, const objValue& ov)
{
    objValue res = false;
    if (ov.Get_type() == STRING)
    {
        res = (ov.Get_stringVal() != s);
    }
        return res;
}

objValue operator/(const int& i, const objValue& ov)
{
    objValue res = 0;
    if (ov.Get_type() == INTEGER)
    {
        res = (i / ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (i / ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;

}

objValue operator/(const double& d, const objValue& ov)
{
    objValue res = 0;
    if (ov.Get_type() == INTEGER)
    {
        res = (d / ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (d / ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;

}

objValue operator/(const float& d, const objValue& ov)
{
    objValue res = 0;
    if (ov.Get_type() == INTEGER)
    {
        res = (d / ov.Get_intVal());
    }
    else if (ov.Get_type() == DOUBLE)
    {
        res = (d / ov.Get_doubleVal());
    }
    else
    {
        std::cout << "ERROR: operator/ not defined for given types. Aborted.\n";
    }
    return res;

}

objValue operator%(const int& i, const objValue& ov)
{
    objValue res = 0;
    if (ov.Get_type() == INTEGER)
    {
        res = (i % ov.Get_intVal());
    }
    else
    {
        std::cout << "ERROR: operator% not defined for given types. Aborted.\n";
    }
    return res;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~









// myObject function implementations ~~~~~~~~~~~~~~~
//   CTOR \ DTOR
myObject::myObject()
{

}
// copy CTOR
myObject::myObject(const myObject& o)
{
    this->callFuncId = o.Get_callFuncId();
    this->valMap = o.Get_valMap();
    this->value_id_counter = o.Get_value_id_counter();
    this->targetObj = o.Get_targetObj();
}

myObject::myObject(std::vector<objValue> v) // for testing purposes // ALSO DEPRECATED, CANNOT BE USED W KEYS
{
    for (auto i : v)
    {
        this->valMap.insert(std::make_pair(std::to_string(this->value_id_counter), i));
        this->value_id_counter++;
    }
}

myObject::myObject(const valueGen& vg)
{
    std::vector<objValue> tmpVec = vg.valVector;
    /* //BEGIN TEST
    int i = 0;
    for(auto x : tmpVec){
        std::cout << "#" << i;
        std::cout << "\tKey = " << x.Get_key();
        std::cout << "\tType = " << x.Get_type();
        std::cout << "\tValue = " << x << nl;
        ++i;
    }
    //END TEST */
    for (auto v : tmpVec)
    {
        if (v.Get_type() == CALL)    // It used to check only first vector elem
        {                           // now checks every element
            this->callFuncId = v.Get_stringVal();
        }
        else
        {
            std::string key = v.Get_key();
            if (!key.empty())
            {
                this->valMap.insert(std::make_pair(key, v));
            }
            else
            {
                this->valMap.insert(std::make_pair(std::to_string(this->value_id_counter), v));
                this->value_id_counter++;
            }
        }
    }
}

myObject::~myObject()   // The following lines costed me 2 days of debugging..
{
    //for (auto x : this->valMap) {
    //    x.second.~objValue();
    //}
}


/* myObject : Setters / Getters */
std::string myObject::Get_callFuncId() const
{
    return this->callFuncId;
}

void myObject::Set_callFunc(const std::string& s)
{
    this->callFuncId = s;
}
void myObject::Set_callFunc(const char* cptr)
{
    std::string s(cptr);
    this->callFuncId = s;
}

int myObject::Get_value_id_counter() const
{
    return this->value_id_counter;
}

std::map<std::string, objValue> myObject::Get_valMap() const
{
    return this->valMap;
}

myObject* myObject::Get_targetObj() const
{
    return this->targetObj;
}

std::map<std::string, objValue>& myObject::Edit_valMap()
{
    return this->valMap;
}


// myObject : operator Overloads 
myObject& myObject::operator=(const myObject& o)
{
    if (!(o.Get_callFuncId().empty()))
    {
        this->callFuncId = o.Get_callFuncId();
    }
    else
    {
        this->callFuncId.clear();
    }
    this->valMap = o.Get_valMap();
    return (*this);
}
myObject& myObject::operator[](const valueGen& vg)
{
    this->valMap.clear();
    std::vector<objValue> tmpVec = vg.valVector;
    /* //BEGIN TEST
    int i = 0;
    for(auto x : tmpVec){
        std::cout << "#" << i;
        std::cout << "\tKey = " << x.Get_key();
        std::cout << "\tType = " << x.Get_type();
        std::cout << "\tValue = " << x << nl;
        ++i;
    }
    //END TEST */
    std::string key;
    for (auto v : tmpVec)
    {
        if (v.Get_type() == CALL)    // It used to check only first vector elem
        {                           // now checks every element
            this->callFuncId = v.Get_stringVal();
        }
        else
        {
            key = v.Get_key();
            if (!key.empty())
            {
                this->valMap.insert(std::make_pair(key, v));
            }
            else
            {
                this->valMap.insert(std::make_pair(std::to_string(this->value_id_counter), v));
                this->value_id_counter++;
            }
        }
    }
    return (*this);
}

myObject& myObject::operator[](const objValue& ov)
{
    this->valMap.clear();   // Probably unnecessary..

    /* if(ov.Get_type() == CALL)    // It used to check only first vector elem
        {                           // now checks every element
            this->callFuncId = ov.Get_stringVal();
        }
        else */     // Choose not to handle the 'object [ call("printf") ]' case
        // {
    std::string key = ov.Get_key();
    // objValue tmpOv = ov;
    // objValue tmpOv(*ov.Get_objVal()); // will try this later .. hope not :#
    // objValue tmpOv(ov); //<-- THIS! was working last time!
    // all the above are unnecessary..
    if (!key.empty())
    {
        this->valMap.insert(std::make_pair(key, ov));
        //this->valMap[key] = tmpOv; // That's the peasant way to do it, pff.. :[
    }
    else
    {
        this->valMap.insert(std::make_pair(std::to_string(this->value_id_counter), ov));
        // this->valMap[std::to_string(this->value_id_counter)] = tmpOv;
        this->value_id_counter++;
    }
    // }
    return (*this);
}

objValue& myObject::operator[](const char* cptr)
{
    std::string s(cptr);
    return this->Edit_valMap()[s];
}
objValue& myObject::operator[](const std::string s)
{
    return this->Edit_valMap()[s];
}


///////////////////////////////////////////////////////////////////////////////
//          FUNCTIONS   SPACE
//template <class T>
// objValue Get_value_from_user(const M& msg)
// objValue Get_value_from_user(const char* msg)
// {
//     objValue tmpOV;
//     std::cout << "\n" << msg;
//     T taf;
//     std::cin >> T;
//     //std::cout << "\nTaf = " << taf << nl<<nl;
//     objValue tmpOV = taf;
//     return tmpOV;
// }
// All credit to Ayush Gupta@https://www.tutorialspoint.com/program-to-find-out-the-data-type-of-user-input-in-cplusplus
objValue Get_value_from_user(const char* msg)
{
    char input[50] = "";
    double temp;
    int intVal;
    char stringVal[50] = "";
    double val = 1e-12; // must correlate sh to input size ([50])??
    std::cout << msg;
    objValue ov;
    fgets(input, 100, stdin);
    // To remove newline
    // remove returns an iterator to the element that follows the last element not removed.
    *std::remove(input, input + strlen(input), '\n') = '\0';

    if (sscanf(input, "%lf", &temp) == 1)   // successfully read double. (returns the number of variables filled)
    {
        intVal = (int)temp;
        if (fabs(temp - intVal) / temp > val)
        {
            // std::cout << "The input is a floating point\n";
            double d = strtod(input, NULL);
            ov = d;
        }
        else
        {
            //  std::cout << "The input is an integer\n";
            int i = atoi(input);
            ov = i;
        }
    }
    else if (sscanf(input, "%s", stringVal) == 1)
    {
        if (strcmp(input, "true") == 0)
        {
            // std::cout << "The input is boolean\n";
            bool b = true;
            ov = b;
        }
        else if (strcmp(input, "false") == 0)
        {
            // std::cout << "The input is boolean\n";
            bool b = false;
            ov = b;
        }
        else
        {
            // std::cout << "The input is a string\n";
            ov = input;
        }
    }
    else
    {
        std::cout << "ERROR: input not recognized!\n";
        //ov = input;
    }
    return ov;
}

std::vector<objValue> MapToVec(const std::map<std::string, objValue>& m)
{
    std::vector<objValue> v;
    // for (auto it = m.begin(); it != m.end(); ++it) {
    for (auto& p : m) {
        objValue tmp = p.second;
        v.push_back(tmp);
    }
    return v;
}


/**
* Special NAMESPACE defs
*/

// ~~~~~~~~~~~~~ namespace OBJVALUES ~~~~~~~~~~~~~

// namespace OBJVALUES {

// }



#endif /*  MSGLANG_H  */