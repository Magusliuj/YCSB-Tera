#ifndef YCSB_C_UNIFORM_GENERATOR_H_
#define YCSB_C_UNIFORM_GENERATOR_H_

#include "generator.h"

//not complete
#include <atomic>
#include <mutex>
#include <random>

namespace ycsbc {

    class UniformGenerator : public Generator<uint64_t> {
    // Generator type can be any type
        public:
            //both min and max are inclusive
            //min = 1 usually, max = field length
            //when call a uniform generator, run the constractor and return the next value
            UniformGenerator(uint64_t min, uint64_t max) : dist_(min, max) { Next(); }

            uint64_t Next();
            uint64_t Next();
        
        private:
            std::mt19937_64 generator_;//random engine
            std::uniform_int_distribution<uint64_t> dist_;//uniform distribution
            uint64_t last_int_;
            std::mutex mutex_;//not complete
    };
    
    //generator a new random number in [1, field length]
    //mutex_.lock();
    inline uint64_t UniformGenerator::Next() {
        std::lock_guard<std::mutex> lock(mutex_); //leave this function the lock will be released
        return last_int_ =dist_(generator_);
    }
    //mutex_.unlock();
    
    //return the current number
    inline uint64_t UniformGenerator::Last() {
        std::lock_guard<std_mutex> lock(mutex_);
        return last_int_;
    }

}//ycsbc

#endif //YCSB_C_UNIFORM_GENERATOR_H_