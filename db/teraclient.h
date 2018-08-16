#ifndef YCSB_C_TERA_DB_H_
#define YCSB_C_TERA_EB_H_

#include "core/db.h"

#include <string>
#include <iostream>
#include "core/properties.h"
#include "tera.h" //not complete

using std::cout;
using std::endl;

namespace ycsbc{

class TeraClient : public DB {
    public: 
    int CreateTable (tera::Client* client); //not complete 
    int CreateClient (); //not complete 
    int Read(const std::string &table, const std::string &key,
             const std::vector<std::string> *fields,
             std::vector<KVPair> &result);
    
    int Update(const std::string &table, const std::string &key,
               std::vector<KVPair> &result)

    int Insert(const std::string &table, const std::string &key,
               std::vector<KVPair> &values){
      return Update(table, key, values);      
    }   
    

    private:

    std::string tableName;
    std::string columnFamily;
    std::string qualifer;
    std::string key;
    std::vector<KVPair> values;         
};

} //ycsbc

#endif //YCSB_C_TERA_DB_H_