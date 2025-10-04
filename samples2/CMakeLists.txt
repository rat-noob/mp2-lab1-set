set(target road)

file(GLOB sources "*.cpp")

add_executable(${target} ${sources})
target_link_libraries(${target} ${MP2_LIBRARY})