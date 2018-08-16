#ifndef YCSB_C_PROPERTIES_H_
#define YCSB_C_PROPERTIES_H_

#include <string>
#include <map>
#include <fstream>
#include <cassert>
#include "utils.h"
// not complete

namespace utils {

    //like java java.properties.class
    //use this object to generate all the information needed in the object
    class Properties {
        public:
            std::string GetProperty(const std::string &key, 
                const std::string &default_value = std::string()) const;
            
            const std::string &operator[](const std::string &key) const;
            const std::map<std::string, std::string> &properties() const;
            
            void SetProperty(const std::string &key, const std::string &value);
            bool Load(std::ifstream &input);
        private:
            std::map<std::string, std::string> properties_;    
    };
    //Read the proporties from file else if file didn't mention use the default one in the coreworkload.cc
    //Use map to store properties with key
      
     inline std::string Properties::GetProperty(const std::string &key, 
           const std::string &default_value) const {
               std::map<std::string, std::string>::const_iterator it = properties_.find(key);
               if (properties_.end() == it) {
                   return default_value;
               } else return it->second;
           }
    
     inline const std::string &Properties::operator[](const std::string &key) const {
         return properties_.at(key);
     }

     inline const std::map<std::string, std::string> &Properties::properties() const {
         return properties_;
     }

     inline void Properties::SetProperty(const std::string &key,
                                         const std::string &value) {
         properties_[key] = value;                                    
     }
    
     // read from file 
     inline bool Properties::Load(std::ifstream &input) {
         if (!input.is_open()) throw utils:Exception("File not open!");

         while (!input.eof() && !input.bad()) {
             std::string line;
             std::getline(input, line);
             if (line[0] == '#') continue;  // if the head is # ignore this line
             size_t pos = line.find_first_of('='); // int size_t
             SetProperty(Trim(line.substr(0,pos), Trim(line.substr(pos + 1))));
         }
         return true;
     }

     
}//utils

#endif
