#include "../public/Debug.hpp"

Engine::Error Engine::Debug::err = {NULL, NULL, 0};

int Engine::Debug::ThrowError(const char* desc, Engine_Macro macro, void* code) {
    if(macro.name != 0) {
        err = {desc, macro.name, macro.value};
    } else {
        err = {desc, NULL, code};
    }
    return DEBUG_SUCCESS;
}

int Engine::Debug::GetError() {
    if(err.description != NULL && err.macro != NULL) {
        std::cout<<err.description<<", "<<err.macro<<" ("<<err.code<<")"<<std::endl;
    } else if(err.description != NULL && err.macro == NULL) {
        std::cout<<err.description<<" ("<<err.code<<")"<<std::endl;
    } else {
        std::cout<<"Failed to get description of error!"<<std::endl;
        return DEBUG_FAILURE;
    }
    return DEBUG_SUCCESS;
}
