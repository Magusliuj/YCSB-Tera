

#include <string>
#include <vector>

namespace ycsbc {

class DB {
    public:
     typedef std::pair<std::string,std::string> KVPair;
     //
     //status.ok in ycsb
     static const int StatusOK = 0;
     static const int StatusErrorNoData = 1;
     static const int StatusErrorConflict =2;
     //
     //Initializes any state for accessing this DB
     virtual void Init(){}
     //
     //Clears any state for accessing this DB
     virtual void Close(){}
     //
     //Reads a record form the database
     //@param table The name of the table to read.
     //@param fields The list of fields to read, or NULL for all of them 
     //@param result A vector of field/value pairs for the result
     //@return Zero on success, or a non-zero error code/record-miss
     virtual int Read(const std::string &table, const std::string &key, 
                      const std::vector<std::string> *fields,
                      std::vector<KVPair> & result ) = 0;
    //
    //Perform a range scan for a set of records in the database 
    //Field/valus pairs from the result are stored in a vector
    //@param table The name of the table.
    //@param key The key of the first record to read.
    //@param record_count The number of records to read.
    //@param fields The list of fields to read, NULL for all of them.
    //@param result A vector of vector, where each vector contains field/value
    //       pairs for one record
    //@return Zero on success, or a non-zero error code/record-miss
    virtual int Scan(const std::string &table, const std::string &key,
                     int record_count, const std::vector<std::string> *fields,
                     std::vector<std::vector<KVPair>> &result) = 0;
    //
    //Updates a record in the database
    //Field/value pairs in the specified vector are written to the record, 
    // overwriting any existing values with the same field names.
    //@param table The name of the table.
    //@param key The key of the record to write.
    //@param values A vector of field/value pairs to update in the record.
    //@return Zero on success, a non-zero error code on error.
    virtual int Update(const std::string &table, const std::string &key,
                      std::vector<KVPair> &values) = 0;
    //
    //Insert a record into the database. 
    //Field/value pairs in the specified vector are written into the record.
    //@param table The name of the table.
    //@param key The key of the first record to read.
    //@param record_count The number of records to read.
    //@param fields The list of fields to read, or NULL for all of them.
    //@param result A vector of vector, 
    virtual int Insert(const std::string &table, const std::string &key,
                       std::vector<KVPair> &values) = 0;
    //
    //Deletes a record from the database.
    //
    //@param table The name of the table.
    //@param key The key of the record to delete.
    //@return Zero on success, a non-zero error code on error.
    virtual int Delete(const std::string &table, const std::string &key) = 0;

    virtual ~DB(){ }
};

}