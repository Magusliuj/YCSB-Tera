#ifndef YCSB_C_CORE_WORKLOAD_H_
#define YCSB_C_CORE_WORKLOAD_H_

#include <vector>
#include <string>
#include "db.h"
#include "properties.h"
#include "generator.h"
//#include "discrete_generator.h"
#include "counter_generator.h"
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

        //
        //The name of the property for the distribution of request keys.
        //Options are "uniform", "zipfian" and "latest".
        //
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
        virtual std::string NextSequenceKey();
        virtual std::string NextTable() { return table_names_; }

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

            std::string table_name_;  //default is usertable in coreworkload.cc
            int field_count_;   //default is 10 in coreworkload.cc
            bool read_all_fields_;   
            bool write_all_fields_;
            Generator<uint64_t> *field_len_generator_; //NULL can be uniform or ..usually is const
            Generator<uint64_t> *key_generator_;     //Countergenerator 
            DiscreteGenerator<Operation> op_chooser_;//choose the transaction operation randomly
                                                     //not complete
            Generator<uint64_t> *key_chooser_;     //NULL can be uniform or .. usually is uniform 
            Generator<uint64_t> *field_chooser_;    //Uniform
            Generator<uint64_t> *scan_len_chooser_;    
            CounterGenerator insert_key_sequence_;   //Countergenerator start constructor with 3 
            bool ordered_inserts_;    //hashed or not
                                      //default is not hashed(true)
            size_t record_count_;  // stored in properties files, usually 100000
    };

    inline std::string CoreWorkload::NextSequenceKey() {
        uint64_t key_num = key_generator_->Next();
        return BuildKeyName(key_num);
    }

    inline std::string CoreWorkload::BuildKeyName(uint64_t key_num) {
        if(!ordered_inserts_) {
            key_num = utils::Hash(key_num);
        }
        return std::string("user").append(std::to_string(key_num));
    }

} //ycsbc

#endif // YCSB_C_CORE_WORKLOAD_H_