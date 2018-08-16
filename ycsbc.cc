#include "core/utils.h"
#include "core/client.h"
#include "core/core_workload.h"
#include "db/db_factory.h"
#include <cstring>
#include <string>
#include <iostream>
//not complete

using namespace std;
void UsageMessage(const char *command);
string ParseCommandLine(int argc, const char *argv[], utils::Properties &props);

int main(const int argc, const char *argv[]) {
    utils::Properties props;
    string file_name = ParseCommandLine(argc, argv, props);

    ycsbc::DB *db = ycsbc::DBFactory::CreateDB(props); //
    if(!db) {
       cout << "Unknown database name " << props["dbname"] << endl;
       exit(0); //continue
    }

    ycsbc::CoreWorkload wl; // coreworkload constructor 
                            // field_count_(0), read_all_fields_(false), read_all_fields_(false),
                            //  field_len_generator_(NULL), key_generator_(NULL), key_chooser_(NULL),
                            //  field_chooser_(NULL), scan_len_chooser_(NULL), insert_key_sequence_(3),
                            //  ordered_inserts_(true), record_count_(0)
    wl.Init(props); //load generator

    const int num_threads = stoi(props.GetProperty); //single thread by default

    // Loads data
    

}

string ParseCommandLine(int argc, const char *argv[], utils::Properties &props) {
    int argindex = 1;
    string filename;
    while (argindex < argc && StrStartWith(argv[argindex], "-")) {
        if (strcmp(argv[argindex], "-db") == 0) {
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("dbname", argv[argindex]);
            argindex++; // the dbname should be input in this step
                        // tera 
                        // basic is not complete
        } else if (strcmp(argv[argindex], "-P") == 0) {
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            filename.assign(argv[argindex]); // put the 
            ifstream input(argv[argindex]);
            try {
                props.Load(input);
            } catch (const string &message) {
                cout << message << endl;
                exit(0);
            }
            input.close();
            argindex++;
        } else if (strcmp(argv[argindex], "-threads") == 0) {
            argindex++;
            if (argindex >= argc) {
                UsageMessage(argv[0]);
                exit(0);
            }
            props.SetProperty("threadcount", argv[argindex]);
            argindex++;
        } else {
            cout << "Unknown option '" << argv[argindex] << "'" << endl;
            exit(0);
        }
    }
    
    if (argindex == 1 || argindex != argc) {
        UsageMessage(argv[0]);
        exit(0);
    }

    return filename;

}

void UsageMessage(const char *command) {
    cout << "Usage: " << command << " [options]" << endl;
    cout << "Options:" << endl;
    cout << " -thread n: execute using n threads (default: 1)!!!!this function is not developed!!!!" << endl;
    cout << " -db dbname: specify the name of the DB to use (default: basic/tera)" << endl;
    cout << " -P propertyfile: load properties from the given file. Multiple fils can" << endl;
    cout << "                   be specified, and will be processes in the order specified" << endl;
}

//check if the string start with certain "?", return true or false
inline bool StrStartWith(const char *str, const char *pre) {
    return strncmp(str, pre, strlen(pre)) == 0; // compare 
}