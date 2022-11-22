#ifndef UTIL_STRING_UTILS_CPP
#define UTIL_STRING_UTILS_CPP

#include<string>
#include<algorithm>
#include<cctype>
#include<memory>
#include <stdexcept>

/**
 * @brief Make a string lower case
 * 
 * @param s is the string we want to make lower case
 * @return std::string the new string but lower case
 */
std::string to_lower(const std::string s) {
    std::string lowered = s;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lowered;
}

/**
 * @brief Format the contents of the format especifiers inside of the string format, with the contents especified in args
 * (like what the printf() function does, but in this case, it is returning the format inside of a string)
 * 
 * @param format is the string we want to format, with the format especifiers
 * @param args is the parameters we want to format inside the string format
 * @return std::string is the new string with the new formatted content
 */
template<typename ... Args>
std::string format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
    
    if( size_s <= 0 )
        throw std::runtime_error("Error during formatting."); 
    
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    
    return std::string( buf.get(), buf.get() + size - 1 );
}

#endif