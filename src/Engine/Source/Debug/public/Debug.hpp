#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include "../../MacroTools.hpp"

#define DEBUG_SUCCESS 0;
#define DEBUG_FAILURE 1;


namespace Engine {
    typedef struct Error {
        const char* description;
        const char* macro;
        void* code;
    } Error;
    class Debug {
        public:
        static int ThrowError(const char* desc, Engine_Macro macro = {NULL}, void* code = NULL);
        static int GetError();

        public:
        static Error err;

    };
    enum ErrorType {
        SUCCESS = 0,
        FAILURE = 1,
        WARNING = 2,

    };
}

#endif // DEBUG_HPP