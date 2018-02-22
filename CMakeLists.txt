cmake_minimum_required(VERSION 2.6)
project(BridgeKeeper)

include_directories(protocol)

add_subdirectory(controller)
add_subdirectory(lightpole)
add_subdirectory(remote)
add_subdirectory(motorfb)