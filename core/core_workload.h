#ifndef YCSB_C_CORE_WORKLOAD_H_
#define YCSB_C_CORE_WORKLOAD_H_

#include <vector>
#include <string>
#include "db.h"
#include "properties.h"
#include "generator.h"
//#include "discrete_generator.h"
//#include "counter_generator.h"
#include "utils.h"


namespace ycsdc {
    
    //
    enum Operation {
        INSERT,
        READ,
        UPDATE,
        SCAN,
        READMODIFYWRITE
    };

    class CoreWorkload {
        public:
        //
        // The name of the database table to run queris against.
        //
        static const std::string TABLENAME_PROPERTY;
        static const std::string TABLENAME_DEFAULT;

        //
        // The name of the property for the number of fields in a record.
        // store in property
        static const std::string FIELD_COUNT_PROPERTY;
        static const std::string FIELD_COUNT_DEFAULT;
        
        //
        // The name of the property for the field length distribution.
        // Options are "uniform", "zipfian" (favoring short records), and "constant".
        // store in property
        static const std::string FIELD_LENGTH_DISTRIBUTION_PROPERTY;
        static const std::string FIELD_LENGTH_DISTRIBUTION_DEFAULT;
        
        //
        // The name of the property for the length of a field in bytes
        //
        static const std::string FIELD_LENGTH_PROPERTY;
        static const std::string FIELD_LENGTH_DEFAULT;
        //
        // The name of the property for deciding whether to read one field (false)
        // or all fields (true) of a record.
        //
        static const std::string READ_ALL_FIELDS_PROPERTY;
        static const std::string READ_ALL_FIELDS_DEFAULT;
        
        //not complete for the values....
        static const std::string REQUEST_DISTRIBUTION_PROPERTY;
        static const std::string REQUEST_DISTRIBUTION_DEFAULT;
        
        static const std::string INSERT_ORDER_PROPERTY;
        static const std::string INSERT_ORDER_DEFAULT;

        static const std::string INSERT_START_PROPERTY;
        static const std::string INSERT_START_DEFAULT;
        
        static const std::string RECORD_COUNT_PROPERTY;
        static const std::string OPERATION_COUNT_PROPERTY;
        
        // Initialize the scenario.
        // Called once, in the main client thread, before any operations are started.
        // properties class is in utils namespace
        virtual void Init(const utils::Properties &p);
        
        virtual void BuildValues(std::vector<ycsbc::DB::KVPair> &values);
        virtual void BuildUpdate(std::vector<ycsbc::DB::KVPair> &update);
        virtual std::string NextTable() { return table_name_; } // this is a simple method,
                                                               //the table name is loaded with properties method
                                                               //and the value is defined in coreworkload.h and is stored in coreworkload.cc
        CoreWorkload() : field_count_(0), read_all_fields_(false), write_all_fields_(false),
                         field_len_generator_(NULL), key_generator_(NULL), key_chooser_(NULL),
                         field_chooser_(NULL), scan_len_chooser_(NULL), insert_key_sequence_(3),
                         ordered_inserts_(true), record_count_(0) {

                         }
        
        virtual ~CoreWorkload() {
            if (field_len_generator_) delete field_len_generator_;
            if (key_generator_) delete key_generator_;
            if (key_chooser_) delete key_chooser_;
            if (field_chooser_) delete field_chooser_;
            if (scan_len_chooser_) delete scan_len_chooser_;
        }

        protected:
            static Generator<uint64_t> *GetFieldLenGenerator(const utils:Properties &p);
            std::string BuildKeyName(uint64_t key_num); 

            std::string table_name_;  //default is usertable
            int field_count_;   //default is 10
            bool read_all_fields_;   
            bool write_all_fields_;
            Generator<uint64_t> *field_len_generator_;
            Generator<uint64_t> *key_generator_;     //can be countergenerator or other generator
            DiscreteGenerator<Operation> op_chooser_;//choose the transaction operation randomly
            Generator<uint64_t> *key_chooser_;
            Generator<uint64_t> *field_chooser_;
            Generator<uint64_t> *scan_len_chooser_;
            CounterGenerator insert_key_sequence_;   //start constructor with 3
            bool ordered_inserts_;
            size_t record_count_;
    };

} //ycsbc

#endif // YCSB_C_CORE_WORKLOAD_H_