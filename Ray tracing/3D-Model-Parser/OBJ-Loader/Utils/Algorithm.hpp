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
    /**
     *  Helper function for parsing files. Check if string starts with given prefix.
     *  @param string The string you want to check the prefex against
     *  @param prefix The prefix you want to match the string with.
     *  @return True if the sting match prefix, false otherwise.
     *
     */
    bool startsWith(std::string const& string,std::string const& prefix){
        if(string.find(prefix) == 0)
            return true;
        return false;
    }
    
    /**
     *  Helper function for parsing files. split line on char.
     *  @param string The string you want split.
     *  @param c    The char you want to split against.
     *  @return std::vector<std::string> a vector with all splits.
     *
     */
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
