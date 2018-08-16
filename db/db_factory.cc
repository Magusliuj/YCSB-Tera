#include "db/db_factory.h"

#include "db/db_factory.h"

#include <string>
#include "db/basic_db.h"
#include "db/tera_db.h"
//not complete

using namespace std;
using ycsbc::DB;
using ycsbc::DBFactory;

DB* DBFactory::CreateDB(utils::Properties &props) {
    if (props["dbname"] == "basic" ) {
        return new BasicDB;
    } else if (props["dbname"] == "tera") {
        return new TeraDB;
    } else return NULL;
}