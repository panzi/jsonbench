file(GLOB filenames *.json)

configure_file(jsonpp.py jsonpp.py COPYONLY)

foreach(filename ${filenames})
	get_filename_component(targetname ${filename} NAME_WE)
	get_filename_component(filename ${filename} NAME)

	configure_file(${filename} ${filename} COPYONLY)

	add_custom_target(${targetname}_pretty.json ALL
		"${CMAKE_CURRENT_BINARY_DIR}/jsonpp.py" "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
			> "${CMAKE_CURRENT_BINARY_DIR}/${targetname}_pretty.json"
		SOURCES jsonpp.py ${filename})
endforeach()
