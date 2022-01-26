set(SOURCES
    main.cpp
    Tokenizer.cpp
    tokens/Token.cpp
    Assembler.cpp
    ../general.cpp
    ExpressionEvaluator.cpp)

list(TRANSFORM SOURCES PREPEND assembler/)

add_executable(assembler ${SOURCES})
