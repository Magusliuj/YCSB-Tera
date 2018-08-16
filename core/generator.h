#ifndef YCSB_C_GENERATOR_H_
#define YCSB_C_GENERATOR_H_

#include <cstdint>
#include <string>
namespace ycsbc {

template <typename Value> //all type of values can use these methods in class Value
class Generator {
    public:
        virtual Value Next() = 0; 
        virtual Value Last() = 0;
        virtual ~Generator() { } 
};

} //ycsbc

#endif //YCSB_C_GENERATOR_H_