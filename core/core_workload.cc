#include "core_workload.h"
#include "uniform_generator.h"
//not complete
#include <string>

using ycsbc::CoreWorkload;
using std::string;

//init value
const string CoreWorkload::TABLENAME_PROPERTY = "table";
const string CoreWorkload::TABLENAME_DEFAULT = "usertable"; 
// like a value pair, the table is the key and usertable is the name 

//init value
const string CoreWorkload::FIELD_COUNT_PROPERTY = "fieldcount";
const string CoreWorkload::FIELD_COUNT_DEFAULT = "10";

//GetFieldGenerator init value
const string CoreWorkload::FIELD_LENGTH_DISTRIBUTION_PROPERTY = "field_len_dist";
const string CoreWorkload::FIELD_LENGTH_DISTRIBUTION_DEFAULT = "constant";

//GetFieldGenerator init value
const string CoreWorkload::FIELD_LENGTH_PROPERTY = "fieldlength";
const string CoreWorkload::FIELD_LENGTH_DEFAULT = "100";

// //init value
// const string CoreWorkload::READ_PROPORTION_PROPERTY = "readproportion";
// const string CoreWorkload::READ_PROPORTION_DEFAULT = "0.95"

// //init value
// const string CoreWorkload::UPDATE_PROPORTION_PROPERTY = "updateproportion";
// const string CoreWorkload::UPDATE_PROPORTION_DEFAULT = "0.05";

// //init value
// const string CoreWorkload::INSERT_PROPORTION_PROPERTY = "insertproportion";
// const string CoreWorkload::INSERT_PROPORTION_DEFAULT = "0.0";

// //init value
// const string CoreWorkload::SCAN_PROPORTION_PROPERTY = "scanproportion";
// const string CoreWorkload::SCAN_PROPORTION_DEFAULT = "0.0";

// //init value
// const string CoreWorkload::READMODIFYWRITE_PROPORTION_PROPERTY = "readmodifywriteproportion";
// const string CoreWorkload::READMODIFYWRITE_PROPORTION_DEFAULT = "0.0";

//init value
const string CoreWorkload::RECORD_COUNT_PROPERTY = "recordcount"; 
//store in properties files with the key as recordcount

//init value
const string CoreWorkload::OPERATION_COUNT_PROPERTY = "operationcount";
//store in properties files with the key as operationcount

//init value
const string CoreWorkload::REQUEST_DISTRIBUTION_PROPERTY = "requestdistribution";
const string CoreWorkload::REQUEST_DISTRIBUTION_DEFAULT = "uniform";

//init value
const string CoreWorkload::INSERT_ORDER_PROPERTY = "insertorder";
const string CoreWorkload::INSERT_ORDER_DEFAULT = ""; //not hashed

//init value
const string CoreWorkload::INSERT_START_PROPERTY = "insertstart";
const string CoreWorkload::INSERT_START_DEFAULT = "0";


//first method to load in coreworkload.h
void CoreWorkload::Init(const utils::Properties &p) {
    table_name_ = p.GetProperty(TABLENAME_PROPERTY, TABLENAME_DEFAULT); //call properties

    field_count_ = std::stoi(p.GetProperty(FIELD_COUNT_PROPERTY,
                                           FIELD_COUNT_DEFAULT));  //default
    field_len_generator_ = GetFieldLenGenerator(p); //new a generator object

    // double read_proportion = std::stod(p.GetProperty(READ_PROPORTION_PROPERTY,
    //                                                  READ_PROPORTION_DEFAULT)); //not complete
    // double update_proportion = std::stod(p.GetProperty(UPDATE_PROPORTION_PROPERTY,
    //                                                    UPDATE_PROPORTION_DEFAULT)); //not complete
    // double insert_proportion = std::stod(p.GetProperty(INSERT_PROPORTION_PROPERTY,
    //                                                    INSERT_PROPORTION_DEFAULT));//not complete
    // double scan_proportion = std::stod(p.GetProperty(SCAN_PROPORTION_PROPERTY,
    //                                                  SCAN_PROPORTION_DEFAULT));//not complete
    // double readmodifywrite = std::stod(p.GetProperty(
    //        READMODIFYWRITE_PROPORTION_PROPERTY, READMODIFYWRITE_PROPORTION_DEFAULT));
    
    record_count_ = std::stoi(p.GetProperty(RECORD_COUNT_PROPERTY));
    std::string request_dist = p.GetProperty(REQUEST_DISTRIBUTION_PROPERTY,
                                             REQUEST_DISTRIBUTION_DEFAULT);
    // int max_scan_len = std::stoi(p.GetProperty(MAX_SCAN_LENGTH_PROPERTY,
    //                                            MAX_SCAN_LENGTH_DEFAULT));
    // std::string scan_len_dist = p.GetProperty(SCAN_LENGTH_DISTRIBUTION_PROPERTY,
    //                                           SCAN_LENGTH_DISTRIBUTION_P);
    int insert_start = std::stoi(p.GetProperty(INSERT_START_PROPERTY,
                                               INSERT_START_DEFAULT));
    // read_all_fields_ = utils::StrToBool(p.GetProperty(READ_ALL_FIELDS_PROPERTY,
    //                                                   READ_ALL_FIELDS_DEFAULT));
    // wirte_all_fields_ = utils:StrToBool(p.GetProperty(WRITE_ALL_FIELDS_PROPERTY,
    //                                                   WRITE_ALL_FIELDS_DEFAULT));
    
    if(p.GetProperty(INSERT_ORDER_PROPERTY, INSERT_ORDER_DEFAULT) == "hashed") {
        ordered_inserts_ = false;
    } else {
        ordered_inserts_ = true;   //default is true
    }

    key_generator_ = new CounterGenerator(insert_start); // insert_start = 0 in coreworkload.cc

    insert_key_sequence_.Set(record_count_); //reset the start at record_count_ = 100000 in properties files

    if (request_dist == "uniform") {
        key_chooser_ = new UniformGenerator(0, record_count_ - 1);  //key iterator from 0-record_count
    } else {
        throw utils::Exception("Unknown request distribution: " + request_dist);
    }

    field_chooser_ = new UniformGenerator(0, field_count_ -1); //field iterator from 0-field_count
}

ycsbc::Generator<uint64_t> *CoreWorkload::GetFieldLenGenerator(
     const utils::Properties &p) {   
     // the return value is a uint64_t with properties object as a parameter 
    string field_len_dist = p.GetProperty(FIELD_LENGTH_DISTRIBUTION_PROPERTY,
                                          FIELD_LENGTH_DISTRIBUTION_DEFAULT);
    int field_len = std::stoi(p.GetProperty(FIELD_LENGTH_PROPERTY,
                                            FIELD_LENGTH_DEFAULT));
    if(field_len_dist == "constant") {
        return new ConstGenerator(field_len);
    } else if(field_len_dist == "uniform") {  //not complete
        return new UniformGenerator(1, field_len);
    } else if(field_len_dist == "zipfain") {
        return new ZipfianGenerator(1, field_len);//not complete
    } else {
        throw utils::Exception("Unknown field length distribution: " + 
            field_len_dist);
    }
     }