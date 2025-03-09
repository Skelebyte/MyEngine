#ifndef MACROTOOLS_HPP
#define MACROTOOLS_HPP

/**
 * @param name The name of the macro, in a C style string.
 * @param value The expanded version of the macro, what its value actually is.
 */
struct Engine_Macro {
    const char* name;
    void* value;
};

// Convert macro to string, by creating an `Engine_Macro` type.
#define GET_MACRO(macro) Engine_Macro {#macro, (void*)macro}

#endif // MACROTOOLS_HPP