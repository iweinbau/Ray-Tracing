//
//  Algorithm.hpp
//  OBJ-Loader
//
//  Created by Iwein Bau on 21/02/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#ifndef Algorithm_h
#define Algorithm_h

#include <iostream>
#include <string>
#include <sstream>

namespace algorithm {
    bool startsWith(std::string const& string,std::string const& prefix){
        if(string.find(prefix) == 0)
            return true;
        return false;
    }
    
    std::vector<std::string> split(std::string const& string,const char c = ' '){
        std::string segment;
        std::stringstream ss(string);
        std::vector<std::string> split;
        while(std::getline(ss, segment,c))
        {
            split.push_back(segment);
        }
        return split;
    }
}

#endif /* Algorithm_h */
