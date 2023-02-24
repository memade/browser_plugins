project(browser_injector)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

set(SOURCES
${SOURCES_DIR}browser_injector.def
${SOURCES_DIR}dllmain.cpp
${SOURCES_DIR}export.cpp
${SOURCES_DIR}export.h
${SOURCES_DIR}stdafx.h
${SOURCES_DIR}stdafx.cpp
)

add_definitions(-DSHARED_API)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

MSVC_USE_CRT_OPTION(${PROJECT_NAME})

# 指定专用库头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
${SOURCES_DIR}
${CURRENT_SOLUTION_DIR}/include
${SOLUTION_ROOT_DIR}/3rdparty
${SOLUTION_ROOT_DIR}/include
${SOLUTION_ROOT_DIR}/3rdparty/spdlog/include
${SOLUTION_ROOT_DIR}/3rdparty/Detours-3.3.9/src
${SOLUTION_ROOT_DIR}/3rdparty/curlpp-0.8.1/include
${SOLUTION_ROOT_DIR}/3rdparty/curl-7.85.0/include
${SOLUTION_ROOT_DIR}/3rdparty/
${SOLUTION_ROOT_DIR}/3rdparty/wxWidgets-3.2.1/include
)

# 依赖库目录
target_link_directories(${PROJECT_NAME} PRIVATE
${SOLUTION_ROOT_DIR}/librarys/3rdparty/${CMAKE_VS_PLATFORM_NAME}
${SOLUTION_ROOT_DIR}/librarys/shared/${CMAKE_VS_PLATFORM_NAME}
${SOLUTION_ROOT_DIR}/librarys/openssl/3.1.0-beta1/${CMAKE_VS_PLATFORM_NAME}
${SOLUTION_ROOT_DIR}/librarys/wxwidgets/${CMAKE_VS_PLATFORM_NAME}
)

# MSVC 预编译头设置
MSVC_USE_PCH(${PROJECT_NAME} 
${SOURCES_DIR}stdafx.h 
${SOURCES_DIR}stdafx.cpp)





