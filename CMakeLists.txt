cmake_minimum_required(VERSION 3.10.0)
project(cryp VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenSSL REQUIRED)

add_executable(cryp main.cpp)

target_link_libraries(cryp OpenSSL::SSL OpenSSL::Crypto)

