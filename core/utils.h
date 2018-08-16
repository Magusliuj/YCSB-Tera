#ifndef YCSB_C_UTILS_H_
#define YCSB_C_UTILS_H_


#include <exception>
#include <cstdint>
#include <algorithm>
#include <random>

namespace utils {
    
    const uint64_t kFNVOffsetBasis64 = 0xCBF29CE484222325;
    const uint64_t kFNVPrime64 = 1099511628211;
    
    //
    // produces more "random" hashses than String.hashCode
    // @param val The value to hash
    // @return The hash value
    //
    inline uint64_t FNVHash64(uint64_t val) {
        //from http://en.wikipedia.org/wiki/Fowler_Noll_Vo_hash
        uint64_t hash = kFNVOffsetBasis64;

        for (int i = 0; i < 8; i++) {
            uint64_t octet = val & 0x00ff;
            val = val >> 8;

            hash = hash ^ octet;
            hash = hash * kFNVPrime64;
            //hash = hash ^ octet
        }
        return hash;
    }

    inline uint64_t Hash(uint64_t val) { return FNVHash64(val); }  // call Hash method to hash..
 
    
    //throw exception for client.h
    //not implement in the original file
    class Exception : public std::exception {
        public:
         Exception(const std::string &message) : message_(message) { }
         const char* what() const noexcept {
             return message_.c_str();
         }
         private:
           std::string message_;
    };
    
    //call by the properties.h 
    //Trim the string remove " " from end and head
    //The method is in stackoverflow
    //may cause some problems because the c++ version; hava another method to 
    inline std::string Trim(const std::string &str) {
        auto front = std::find_if_not(str.begin(), str.end(), [](int c){ return std::issapce(c); });
        return std::string(front, std::find_if_not(str.rbegin(), std::string::const_reverse_iterator(front),
                    [](int c){ return std::issapce(c);}).base());
    }
    
} // utils

#endif // YCSB_C_UTILS_H_