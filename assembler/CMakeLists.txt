set(SOURCES
    main.cpp
    Tokenizer.cpp
    tokens/Token.cpp
    Assembler.cpp
    ../general.cpp Macro.h)

list(TRANSFORM SOURCES PREPEND assembler/)

add_executable(assembler ${SOURCES})
