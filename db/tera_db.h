#ifndef YCSB_C_TERA_DB_H_
#define YCSB_C_TERA_DB_H_

#include "core/db.h"

#include <iostream>
#include <string>
#include "core/properties.h"
#include "tera.h" //not complete 
#include "tera_client.h" //not complete

using std::cout;
using std::endl;

namespace ycsbc {

class TeraDB : public DB {
    public:
        //TeraDB(){} //not complete

        int Read(const std::string &table, const std::string &key,
                 const std::vector<std::string> *fields, std::vector<KVPair> &result){   
                     throw "Read: function not implemented! ";
                 } //not complete

        int Scan(const std::string &table, const std::string &key,
                 int len, const std::vector<std::string> *fields,
                 std::vector<std::vector<KVPair>> &result) {
                     throw "Scan: function not implemented!";
                 } //not complete

        int Update(const std::string &table, const std::string &key,
                    std::vector<KVPair> &values);

        int Insert(const std::string &table, const std::string &key,
                    std::vector<KVPair> &values) {
                        return Update(table, key, values);
                    } 
        
        int Delete(const std::string &table, const std::string &key,
                    std::vector<KVPair> &values){
                        throw "Delete: function not implemented!"; 
                    } //not complete
        //~TeraDB();

    private:
        TeraClient tera_; //not complete
};

}//ycsbc

#endif //YCSB_C_TERA_DB_H