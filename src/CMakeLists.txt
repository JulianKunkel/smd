set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# ESDM Utils and Database Library

add_library(smd SHARED smd-core.c)
#target_link_libraries(smd ${GLIB_LDFLAGS} ${JANSSON_LDFLAGS})
install(TARGETS smd LIBRARY DESTINATION lib)
