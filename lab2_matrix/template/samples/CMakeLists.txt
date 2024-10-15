file(GLOB hdrs "*.h*" "../include/*.h")
file(GLOB srcs "*.cpp")

add_executable(matrix ${srcs} ${hdrs})