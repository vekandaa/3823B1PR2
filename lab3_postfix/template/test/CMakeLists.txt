set(target postfix_test)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../include/postfix.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
