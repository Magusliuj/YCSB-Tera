#ifndef YCSB_C_TERA_CLIENT_H_
#define YCSB_C_TERA_CLIENT_H_

#include <iostream>
#include <string>
#include "tera.h" //not complete


namespace ycsbc {

class TeraClient {
    public: 
        TeraClient();
        ~TeraClient();

    private:
        tera::ErrorCode error_code;
        tera::Client* client;
};

inline TeraClient::TeraClient() {
    //tera::ErrorCode error_code;
    //create a client by defualt values in system
    //if(the number of client < the requested number of client) 
    //wanna several ts
    client = tera::Client::NewClient("./tera.flag", &error_code); //not complete 
    if (client == NULL) {
        printf("Create tera Client fail: %s\n", tera::strerr(error_code));
        exit(-1); //not complete
        }
    
}

inline TeraClient::~TeraClient() {
    delete client; //not complete
}
    

}//ycsbc


#endif //YCSB_C_TERA_CLIENT_H_