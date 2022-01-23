set(SOURCES
    main.cpp
    ../general.cpp
    Memory.cpp
    instructions.cpp)

list(TRANSFORM SOURCES PREPEND VM/)

add_executable(VM ${SOURCES})
