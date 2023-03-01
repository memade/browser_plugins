cmake_minimum_required(VERSION 3.25.1)

project(chromium_plugin)

set(CMAKE_CXX_STANDARD 23)
# 添加预定义宏
add_definitions(-DUNICODE -D_UNICODE)

set(PLATFORM "x86")
if (CMAKE_CL_64)
set(PLATFORM x64)
else(CMAKE_CL_64)
set(PLATFORM x86)
endif(CMAKE_CL_64)

# 设置默认编译类型
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "info" FORCE)

set(SOLUTION_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

set(CURRENT_SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#cmake modules path
set(GLOBAL_CMAKE_MODULES_PATH ${SOLUTION_ROOT_DIR}/cmake/modules/)

LIST(APPEND CMAKE_MODULE_PATH ${GLOBAL_CMAKE_MODULES_PATH})
include(msvc_methods)
include(OutputPathConfig)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

OutputPathConfig("bin" "bin" "lib")
add_subdirectory(${CURRENT_SOLUTION_DIR}/src/manager/)
add_subdirectory(${CURRENT_SOLUTION_DIR}/src/manager_site/)
#set_target_properties(win PROPERTIES FOLDER "shared")

add_subdirectory(${CURRENT_SOLUTION_DIR}/src/browser_injector/)
set_target_properties(browser_injector PROPERTIES FOLDER "components")

add_subdirectory(${CURRENT_SOLUTION_DIR}/src/browser_hook/)
set_target_properties(browser_hook PROPERTIES FOLDER "components")

add_subdirectory(${CURRENT_SOLUTION_DIR}/src/main/)
set_target_properties(main PROPERTIES FOLDER "plugins")

add_subdirectory(${CURRENT_SOLUTION_DIR}/src/plugin_win/)
set_target_properties(plugin_win PROPERTIES FOLDER "plugins")

add_subdirectory(${CURRENT_SOLUTION_DIR}/src/plugin_hook/)
set_target_properties(plugin_hook PROPERTIES FOLDER "plugins")

add_subdirectory(${CURRENT_SOLUTION_DIR}/tests/test_browser_plugin_hook/)
#set_target_properties(test_browser_plugin_hook PROPERTIES FOLDER "tests")
OutputPathConfig("")

MSVC_SET_STARTUP_PROJECT(test_browser_plugin_hook
${CURRENT_SOLUTION_DIR}/tests/test_browser_plugin_hook/)

