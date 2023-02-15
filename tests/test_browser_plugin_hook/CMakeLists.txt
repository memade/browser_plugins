project(test_browser_plugin_hook)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

set(SOURCES
${SOURCES_DIR}main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

MSVC_SET_LINK_FLAG_CONSOLE(${PROJECT_NAME})

MSVC_USE_CRT_OPTION(${PROJECT_NAME})

# 指定专用库头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
${SOURCES_DIR}
${CURRENT_SOLUTION_DIR}/include
${SOLUTION_ROOT_DIR}/3rdparty
${SOLUTION_ROOT_DIR}/include
${SOLUTION_ROOT_DIR}/3rdparty/spdlog/include
${SOLUTION_ROOT_DIR}/3rdparty/curlpp-0.8.1/include
${SOLUTION_ROOT_DIR}/3rdparty/curl-7.85.0/include
)

# 依赖库目录
target_link_directories(${PROJECT_NAME} PRIVATE
${SOLUTION_ROOT_DIR}/librarys/3rdparty/$(Platform)
${SOLUTION_ROOT_DIR}/librarys/shared/$(Platform)
${SOLUTION_ROOT_DIR}/librarys/openssl/3.1.0-beta1/$(Platform)
)

# MSVC 预编译头设置
#[[
MSVC_USE_PCH(${PROJECT_NAME} 
${SOURCES_DIR}stdafx.h 
${SOURCES_DIR}stdafx.cpp)
]]





