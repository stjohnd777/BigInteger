#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace dsj {
    
    class StringUtils{
        
    public:
        /**
         End with suffix
         */
        static bool endsWith(const std::string& s, const std::string& suffix);
        /**
         Start with suffix
         */
        static bool startsWith(const std::string& s, const std::string& suffix);
        /**
         String s contains key
         */
        static bool contains(const std::string& s, const std::string& key);
        /**
         Replace all instances of target with repl in src
         */
        static std::string replaceAllSubstrings( std::string src, std::string const& target, std::string const& repl);
        /**
         Split
         */
        static void split(std::vector<std::string> &result, std::string str, char delim ) ;
        /**
         Trim
         */
        static std::string trim(std::string s);
        /**
         Is white space
         */
        static bool isWhiteSpaceChar(const char c);
    };

    class easy_string : public std::string {
    public:
        /*
        /// Returns the string representation of the boolean argument.
        static string	ToString(bool b);
        // Returns the string representation of the char argument.
        static string	ToString(char c);
        // Returns the string representation of the char array argument.
        static string	ToString(char[] data);
        /// Returns the string representation of a specific subarray of the char array argument.
        static string	ToString(char[] data, int offset, int count);
        /// Returns the string representation of the double argument.
        static string	ToString(double d);
        /// Returns the string representation of the float argument.
        static string	ToString(float f);
        /// Returns the string representation of the int argument.
        static string	ToString(int i);
        // Returns the string representation of the long argument.
        static string	ToString(long l);
         */

        easy_string (std::string s) : std::string(s)  {

        }

        bool endsWith(  const std::string& suffix){
            return StringUtils::endsWith(*this,suffix);
        }
        /**
         Start with suffix
         */
        bool startsWith(  const std::string& suffix){
            return StringUtils::startsWith(*this,suffix);
        }
        /**
         String s contains key
         */
        bool contains(  const std::string& key){
            return StringUtils::contains(*this,key);
        }


        ///  Returns the index within this string of the first occurrence of the specified charac
        int	indexOf(int ch) {
            return 0;
        }
        // Returns the index within this string of the first occurrence of the specified character, starting the search at the specified index.
        int	indexOf(int ch, int fromIndex){
            return this->find(ch,0);
        }
        //  Returns the index within this string of the first occurrence of the specified substring.
        int	indexOf(std::string str){
            return this->find(str,0);
        }
        ///
        int	indexOf(std::string str, int fromIndex) {
            return this->find(str,fromIndex);
        }

        int	next(std::string str, bool reset) {
            static int last = 0;
            if ( reset) last = 0;
            last = this->find(str,last);
            if ( last == std::string::npos){
                last = 0;
            }
            return last;
        }

        /**
         Replace all instances of target with repl in src
         */
        //std::string
        easy_string replaceAllSubstrings(   std::string const& target, std::string const& repl){
            return StringUtils::replaceAllSubstrings(*this,target,repl);
        }

        // Returns a string resulting from replacing all occurrences of oldChar
        // in this string with newChar.
        easy_string	replace(char oldChar, char newChar) {
            return *this;
        }

        //  Replaces each substring of this string that matches the literal
        //  target sequence with the specified literal replacement sequence.
        easy_string	replace(std::string target, std::string replacement) {
            return *this;
        }

        // TODO
        void invokeAt(char c, std::function< void (std::string::iterator pos,int index) > lambda) {
            auto it = std::begin(*this);
            for(int index = 0;it !=std::end(*this);it++){
                if ( *it == c){
                    lambda(it,index);
                }
                index++;
            }
        }

        void invokeAt(std::string part, std::function< void (std::string::iterator pos,int index) > lambda) {

            int index = this->find(part);

        }

        /**
         Split
         */
        std::vector<std::string> split(  char delim  ){
            std::vector<std::string> result;
            StringUtils::split(result, *this,delim);
            return result;
        }

        easy_string substring(int beginIndex, int endIndex){
            auto sub = this->substr(beginIndex,endIndex);
            return easy_string(sub);
        }

        char* toCharArray() {
            char * ptr = &(*this)[0];
            return ptr;
        }

        easy_string toUpperCase(){
            std::transform(this->begin(), this->end(),this->begin(), ::toupper);
            return *this;
        }

        easy_string toLowerCase(){
            std::transform(this->begin(), this->end(),this->begin(), ::tolower);
            return *this;
        }

        /**
         * Returns a string whose value is this string, with all leading and trailing space removed,
         * where space is defined as any character whose codepoint is less than or equal to 'U+0020'
         * (the space character).
         * @param s
         * @return
         */
        easy_string trim(std::string s){
            return StringUtils::trim(*this);
        }

    };

}

