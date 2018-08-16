#include "tera_db.h"

#include <cstring>

using namespace std;

namespace ycsbc {

    // int TeraClient::Read(const std::string &table, const std::string &key,
    //          const std::vector<std::string> *fields,
    //          std::vector<KVPair> &result){
             
    //          tera::ErrorCode errorcode_read;
    //          tera::Table* teratable = client->OpenTable(table, &errorcode_read);
    //          //Get values from tera
    //          //qualifer = field?
    //          teratable->Get(key, "cf_1", field, result, &errorcode_read);
             
    //          return DB:StatusOK;
    //          }


    int TeraDB::Update(const string &table, const string &key,
                       vector<KVPair> &values) {

                        tera::ErrorCode errorcode_update;
                        tera::Table* teratable = client->OpenTable(table, &errorcode_update);
                        //Put values in tera
                        teratable->Put(key, "cf_1", "qualifer1", value, &errorcode_update); // 
                        return DB::StatusOK;
                        }
}//ycsbc