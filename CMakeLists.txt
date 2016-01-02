cmake_minimum_required(VERSION 2.6)
project(qmailarchiver)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(QMailArchiver_SRCS QMailArchiver.cpp main.cpp)

qt4_automoc(${QMailArchiver_SRCS})
add_executable(qmailarchiver ${QMailArchiver_SRCS})
target_link_libraries(qmailarchiver ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS qmailarchiver RUNTIME DESTINATION bin)
