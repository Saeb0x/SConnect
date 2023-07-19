cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SConnect")

set(SOURCE_FILES_SERVER
    src/Client.cpp
    src/Server.cpp
    src/ServerTest.cpp
)

set(SOURCE_FILES_CLIENT
    src/Client.cpp
    src/Server.cpp
    src/ClientTest.cpp
)

add_executable (Server ${SOURCE_FILES_SERVER})
add_executable (Client ${SOURCE_FILES_CLIENT})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Server PROPERTY CXX_STANDARD 20)
  set_property(TARGET Client PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Server PRIVATE "include")
target_include_directories(Client PRIVATE "include")

# Set Asio include directory
# Replace <path_to_asio> with the path where you have Asio installed or downloaded on your machine.
set(ASIO_INCLUDE_DIR "<path_to_asio>")
target_include_directories(Server PRIVATE ${ASIO_INCLUDE_DIR})
target_include_directories(Client PRIVATE ${ASIO_INCLUDE_DIR})

# Optionally set the build type (Debug or Release) explicitly
# Uncomment and use the following line if needed:
# set(CMAKE_BUILD_TYPE "Debug")