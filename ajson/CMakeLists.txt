pkg_check_modules(AJSON REQUIRED ajson)

include_directories(${AJSON_INCLUDE_DIRS})

add_executable(ajsonbench_number ajsonbench.c ../jsonbench.c)
set_target_properties(ajsonbench_number PROPERTIES COMPILE_DEFINITIONS FLAGS=AJSON_FLAGS_NONE)
target_link_libraries(ajsonbench_number ${AJSON_STATIC_LIBRARIES})

add_executable(ajsonbench_integer ajsonbench.c ../jsonbench.c)
set_target_properties(ajsonbench_integer PROPERTIES COMPILE_DEFINITIONS FLAGS=AJSON_FLAG_INTEGER)
target_link_libraries(ajsonbench_integer ${AJSON_STATIC_LIBRARIES})

add_executable(ajsonbench_string ajsonbench.c ../jsonbench.c)
set_target_properties(ajsonbench_string PROPERTIES COMPILE_DEFINITIONS FLAGS=AJSON_FLAG_NUMBER_AS_STRING)
target_link_libraries(ajsonbench_string ${AJSON_STATIC_LIBRARIES})

add_executable(ajsonbench_components ajsonbench.c ../jsonbench.c)
set_target_properties(ajsonbench_components PROPERTIES COMPILE_DEFINITIONS FLAGS=AJSON_FLAG_NUMBER_COMPONENTS)
target_link_libraries(ajsonbench_components ${AJSON_STATIC_LIBRARIES})
