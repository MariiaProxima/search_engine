# CMakeList.txt: проект CMake для search_engine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

#option(search_engine "Build unit tests" ON)

#if(search_engine)
#    enable_testing()
#    add_subdirectory("test")
#endif()

ADD_SUBDIRECTORY (gtest-1.6.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("search_engine")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (search_engine "search_engine.cpp" "search_engine.h" "test.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET search_engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
set(gtest_disable_pthreads on)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(nlohmann_json_DIR "C:/SkillboxTasks/final_project/search_engine/nlohmann_json")

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest) 

enable_testing()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)


FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)

#add_executable(search_engine search_engine.cpp)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)