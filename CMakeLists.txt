# /****************************************************************************
# * Mail Archiver - A solution to store and manage offline e-mail files.      *
# * Copyright (C) 2015-2016 Carlos Nihelton <carlosnsoliveira@gmail.com>      *
# *                                                                           *
# *   This is a free software; you can redistribute it and/or                 *
# *   modify it under the terms of the GNU Library General Public             *
# *   License as published by the Free Software Foundation; either            *
# *   version 2 of the License, or (at your option) any later version.        *
# *                                                                           *
# *   This software  is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
# *   GNU Library General Public License for more details.                    *
# *                                                                           *
# *   You should have received a copy of the GNU Library General Public       *
# *   License along with this library; see the file COPYING.LIB. If not,      *
# *   write to the Free Software Foundation, Inc., 59 Temple Place,           *
# *   Suite 330, Boston, MA  02111-1307, USA                                  *
# *                                                                           *
# ****************************************************************************/

cmake_minimum_required(VERSION 3.4)
project(MailArchiver)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Boost 1.50 COMPONENTS iostreams serialization REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(ENABLE_PROFILING "Enables/disables profiling data generation" OFF)

if(ENABLE_PROFILING)
    if (CMAKE_CXX_COMPILER MATCHES "Clang" or CMAKE_CXX_COMPILER MATCHES "GCC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    endif()
endif ()
    

include_directories(${Qt5Widgets_INCLUDES} ${Qt5Sql_INCLUDES} ${CMAKE_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/3rd/pole" "${PROJECT_SOURCE_DIR}/3rd/md5-cc")
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "-Wall ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

qt5_add_resources(MailQRC "${PROJECT_SOURCE_DIR}/res/MailArchiverWidget.qrc")

file(GLOB MailArchiver_SRCS "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/3rd/*/*.cpp" "${PROJECT_SOURCE_DIR}/3rd/*/*.cc" "${CMAKE_BINARY_DIR}/build/*.cpp")
    
add_executable(MailArchiver ${MailArchiver_SRCS} ${MailQRC})
target_compile_features(MailArchiver PRIVATE cxx_nullptr cxx_range_for)
target_link_libraries(MailArchiver ${Qt5Widgets_LIBRARIES} ${Qt5Sql_LIBRARIES} ${Boost_LIBRARIES} pthread)
set_property(TARGET MailArchiver PROPERTY CXX_STANDARD 14)

install(TARGETS MailArchiver RUNTIME DESTINATION bin)
