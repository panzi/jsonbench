pkg_check_modules(YAJL REQUIRED yajl)

include_directories(${YAJL_INCLUDE_DIRS})
add_executable(yajlbench yajlbench.c ../jsonbench.c)
target_link_libraries(yajlbench ${YAJL_STATIC_LIBRARIES})
