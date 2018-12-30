
# Generic tests, that only require libsmd
file(GLOB TESTFILES "${CMAKE_CURRENT_SOURCE_DIR}" "*.c")
foreach(TESTFILE ${TESTFILES})
  if(IS_DIRECTORY ${TESTFILE} )
    #message(STATUS ${TESTFILE})
  else()
    get_filename_component(TESTNAME_C ${TESTFILE} NAME)
    STRING(REGEX REPLACE ".c$" "" TESTNAME ${TESTNAME_C})

	# Build, link and add as test
    add_executable(${TESTNAME} ${TESTFILE} util/test_util.c)
   	target_link_libraries(${TESTNAME} smd ${MPI_LIBRARIES} -lrt)
    #target_include_directories(${TESTNAME} SYSTEM PRIVATE ${CMAKE_BINARY_DIR})

    add_test(${TESTNAME} ./${TESTNAME})
  endif()
endforeach()
