cmake_minimum_required(VERSION 3.16)
project(MarketDataFetcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(market_data src/main.cpp)
target_link_libraries(market_data PRIVATE CURL::libcurl)
