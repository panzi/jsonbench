find_path(RAPIDJSON_INCLUDE_DIR rapidjson/reader.h)

include_directories(${RAPIDJSON_INCLUDE_DIR})
add_executable(rapidjsonbench rapidjsonbench.cpp ../jsonbench.c)
