cmake_minimum_required(VERSION 2.8)

SET(CMAKE_SYSTEM_NAME Linux)

AUX_SOURCE_DIRECTORY(. RTU_SRC)

ADD_LIBRARY(gate STATIC ${RTU_SRC})
ADD_EXECUTABLE(gateway ${RTU_SRC})

LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)

TARGET_LINK_LIBRARIES(gateway
                      PocoUtil
                      PocoXML
                      PocoNet
                      PocoFoundation
                      PocoDataSQLite)
