#ifndef YCSB_C_BASIC_DB_H_
#define YCSB_C_BASIC_DB_H_

#include "core/db.h"

#include <iostream>
#include <string>
#include <mutex>
#include <core/properties.h>

using std::cout;
using std::endl;

namespace ycsbc {
    class BasicDB : public DB {
        public:
            void Init() {
                std::lock_guard<std::mutex> lock(mutex_);
                cout << "A new thread begins working." << endl;
            }

            
    }
}