cmake_minimum_required(VERSION 2.8.8)

project(jsonbench)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -std=gnu99 -pedantic -fvisibility=hidden")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3")
	set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS} -O3 -g")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++1y -pedantic -fvisibility=hidden")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O3 -g")
endif()

find_package(PkgConfig)

add_subdirectory(data)
add_subdirectory(ajson)
add_subdirectory(yajl)
add_subdirectory(rapidjson)

configure_file(run.py       run.py       COPYONLY)
configure_file(jsonbench.py jsonbench.py COPYONLY)
configure_file(jsonbench.rb jsonbench.rb COPYONLY)
configure_file(jsonbench.js jsonbench.js COPYONLY)

add_custom_target(jsonbench
	"${CMAKE_CURRENT_BINARY_DIR}/run.py"
	DEPENDS ajsonbench_number ajsonbench_integer ajsonbench_string yajlbench
	SOURCES jsonbench.py jsonbench.rb jsonbench.js)
