

#include "easy_string.hpp"

namespace dsj {

    bool StringUtils::endsWith(const std::string& s, const std::string& suffix)
    {
        return s.rfind(suffix) == (s.size()-suffix.size());
    }

    bool StringUtils::startsWith(const std::string& s, const std::string& prefix)
    {
        if ( s.length() < prefix.length() )
        {
            return false;
        }
        std::string front = s.substr(0,prefix.length());
        if ( front == prefix)
        {
            return true;
        }
        return false;
    }
    bool StringUtils::contains(const std::string& s, const std::string& key)
    {
        auto found = s.rfind(key);
        bool ret = ( found != std::string::npos );
        return ret;
    }
    std::string StringUtils::replaceAllSubstrings( std::string src, std::string const& target, std::string const& repl)
    {
        // handle error situations/trivial cases
        
        if (target.length() == 0)
        {
            // searching for a match to the empty string will result in
            //  an infinite loop
            //  it might make sense to throw an exception for this case
            return src;
        }
        
        if (src.length() == 0)
        {
            return src;  // nothing to match against
        }
        
        size_t idx = 0;
        
        for (;;)
        {
            idx = src.find( target, idx);
            if (idx == easy_string::npos)  break;
            
            src.replace( idx, target.length(), repl);
            idx += repl.length();
        }
        
        return src;
    }
    
    void StringUtils::split(std::vector<std::string> &result, std::string str, char delim )
    {
        std::string tmp;
        std::string::iterator i;
        result.clear();
        
        for(i = str.begin(); i <= str.end(); ++i)
        {
            if((const char)*i != delim  && i != str.end())
            {
                tmp += *i;
            }
            else
            {
                if ( !tmp.empty() ) {
                    result.push_back(tmp);
                }
                tmp = "";
            }
        }
    }

    std::string StringUtils::trim(std::string s)
    {
        char const *str = s.c_str();
        // Trim leading non-letters
        while(! StringUtils::isWhiteSpaceChar(*str))
        {
            str++;
        }
        // Trim trailing non-letters
        char const * end =(char const *) (str + s.length() - 1);
        while(end > str && !StringUtils::isWhiteSpaceChar(*end))
        {
            end--;
        }
        
        return std::string(str, end+1);
    }
    
    bool StringUtils::isWhiteSpaceChar(const char c)
    {
        bool ret = false;
        if (c==' ' || c=='\n' || c=='\t')
        {
            ret = true;
        }
        return ret;
    }
}
