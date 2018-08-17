// //not used

// #include "teraclient.h"
// #include <cstring>
// using namespace std;

// namespace ycsbc{
 
//     int CreateTable(tera::Client* client){
    
//       //check if table exists
//      if(!client->IsTableExist("usertable", &error_code)){
//          //
//          //tera table descriptor setup
//          //table = read table
//          tera::TableDescriptor table_desc("usertable");
//          //
//          //tera LocalityGroup setup
//          tera::LocalityGroupDescriptor* lg_desc = table_desc.AddLocalityGroup("lg_1");
//          //lg_desc->SetStore(tera::kInFlash);
//          //
//          //tera ColumnFamily
//          tera::ColumnFamilyDescriptor* cf_t = table_desc.AddColumnFamily("cf_1","lg_1");
//          cf_t->setMaxVersions(5);
//      } else {
//         printf("Create table fail: %s\n", tera::strerr(error_code));
//     }
//     }
    
//     int CreateClient() {
//         tera::ErrorCode error_code;
//          if (client == NULL) {
//          //create a client by defualt values in system
//          //if(the number of client < the requested number of client) 
//          //wanna several ts
//          tera::Client* client = tera::Client::NewClient("./tera.flag", &error_code);
//          if (Client == NULL ){
//              printf("Create tera Client fail: %s\n", tera::strerr(error_code));
//              return 1;
//          }
//          CreateTable(client);
//     }


//     int TeraClient::Read(const std::string &table, const std::string &key,
//              const std::vector<std::string> *fields,
//              std::vector<KVPair> &result){
             
//              tera::ErrorCode errorcode_read;
//              tera::Table* teratable = client->OpenTable(table, &errorcode_read);
//              //Get values from tera
//              //qualifer = field?
//              teratable->Get(key, "cf_1", field, result, &errorcode_read);
             
//              return DB:StatusOK;
//              }

//     int TeraClient::Update(const string &table, const string &key,
//              vector<KVPair> &values){
             
//              tera::ErrorCode errorcode_update;
//              tera::Table* teratable = client->OpenTable(table, &errorcode_update);
//              //Put values in tera
//              teratable->Put(key, "cf_1", "qualifer1", value, &errorcode_update);

//              return DB:StatusOK;
//            }
    
    
    
    
//     //delete client
//     delete client; 
//     //tera configuration .......
    
    

//     int main(int argc, char* argv[]){
//          tera::ErrorCode error_code;
//          if (client == NULL) {
//          //create a client by defualt values in system
//          //if(the number of client < the requested number of client) 
//          //wanna several ts
//          tera::Client* client = tera::Client::NewClient("./tera.flag", &error_code);
//          if (Client == NULL ){
//              printf("Create tera Client fail: %s\n", tera::strerr(error_code));
//              return 1;
//          }
//          CreateTable(client);

//          tableName = "usertable";
//          key = "key1";
         
//          KVPair.first = "1";
//          KVPair.second = "2";
//          values.push_back(KVPair);

//          TeraClient::Update(&tableName, &key, &values);
//     }
//     }

// }