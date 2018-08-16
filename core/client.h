#ifndef YCSB_C_CLIENT_H_
#define YCSB_C_CLIENT_H_ 

#include <string>
#include "db.h"
#include "core_workload.h"
#include "utils.h"
// not complete

namespace ycsbc{

    class Client{
        public:
            Client(DB &db, CoreWorkload &wl) ： db_(db), workload_(wl){ }

            virtual bool DoInsert(); // load data into the database
            virtual bool DoTransaction(); //do some transactions

            virtual ~Client() { }
        
        protected:

            virtual int TransactionRead();
            virtual int TransactionReadModifyWrite();
            virtual int TransactionScan();
            virtual int TransactionUpdate();
            virtual int TransactionInsert();

            DB &db_;
            CoreWorkload &workload_;
            //
         };

         inline bool Client::DoInsert() {
             std::string key = workload_.NextSequenceKey(); // call workload to generate key
             std::vector<DB::KVPair> pairs;
             workload_.BuildValues(pairs);  // call workload to generate the content of the pairs
             return (db_.Insert(workload_.NextTable(), key, pairs) == DB::StatusOK); //call tera api
         }

         inline bool Client::DoTransaction() {
             int status = -1;
             switch (workload_.NextOperation()){
                 case READ:
                     status = TransactionRead();
                     break;
                 case UPDATE:
                     status = TransactionUpdate();
                     break;
                 case INSERT:
                     status = TransactionInsert();
                     break;
                 case SCAN:
                     status = TransactionScan();
                     break;
                 default:
                    throw utils::Exception("Operation request is not recognized"); // call utils
             }
             assert(status >= 0); //the following will not be execute unless status >= 0
             return (status == DB::StatusOK);
         }

} //ycsbc

#endif //YCSB_C_CLIENT_H_