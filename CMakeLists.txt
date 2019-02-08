cmake_minimum_required(VERSION 3.5)

# =============
# == PROJECT ==
# =============
project(libC VERSION 0.0.0 LANGUAGES CXX)

set(LIBNAME C)

# ===========
# == FILES ==
# ===========

set( SOURCE_FILES
    C.cpp
)

set( PUBLIC_INCLUDE_FILES
    C.h
)

set( PRIVATE_INCLUDE_FILES

)

# ===========================
# == EXTERNAL DEPENDENCIES ==
# ===========================
include(dependencies.cmake)

# ======================
# == BUILD DIRECTIVES ==
# ======================
#
#Define the project target
#
add_library(
    ${LIBNAME} STATIC
    ${SOURCE_FILES}
    ${PUBLIC_INCLUDE_FILES}
    ${PRIVATE_INCLUDE_FILES}
)

#
# CFLAGS & CXXFLAGS
#
target_compile_options(
    ${LIBNAME} PRIVATE
    -Wall -Wextra -fmessage-length=0
    $<$<CONFIG:DEBUG>:-O0 -ggdb>
    $<$<CONFIG:RELEASE>:-O3 -ggdb>
)

#
# Tell we need to use C++11
#
set_property(
    TARGET ${LIBNAME}
    PROPERTY CXX_STANDARD 11
)

#
# -D
#
target_compile_definitions(
    ${LIBNAME} PRIVATE
    $<$<CONFIG:DEBUG>:DEBUG=1>
    $<$<CONFIG:RELEASE>:NDEBUG=1>
)

#
# -I
#
target_include_directories(
    ${LIBNAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

#
# -l
#
target_link_libraries(
    ${LIBNAME} PUBLIC
    B
)

# ==================
# == UNIT TESTING ==
# ==================
add_executable(
    UnitTest_${LIBNAME}
    ${SOURCE_FILES}
    ${PUBLIC_INCLUDE_FILES}
    ${PRIVATE_INCLUDE_FILES}
    gtest.cpp
)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

target_include_directories(
    UnitTest_${LIBNAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
    UnitTest_${LIBNAME}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${LIBNAME}
)

# ========================
# == INSTALL DIRECTIVES ==
# ========================

install(TARGETS ${LIBNAME} EXPORT ${PROJECT_NAME} DESTINATION lib)
install(EXPORT  ${PROJECT_NAME}                   DESTINATION cmake)
install(FILES   ${PROJECT_NAME}Config.cmake       DESTINATION cmake)
install(FILES   dependencies.cmake                DESTINATION cmake RENAME ${PROJECT_NAME}.dependencies.cmake)
install(FILES   ${PUBLIC_INCLUDE_FILES}           DESTINATION include/${PROJECT_NAME})
