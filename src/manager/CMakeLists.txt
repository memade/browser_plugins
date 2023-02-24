project(manager)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

set(SOURCES
${SOURCES_DIR}local.h
${SOURCES_DIR}local.cpp
${SOURCES_DIR}global.h
${SOURCES_DIR}global.cpp
${SOURCES_DIR}stdafx.h
${SOURCES_DIR}stdafx.cpp
${SOURCES_DIR}main.cpp
${SOURCES_DIR}config.cpp
${SOURCES_DIR}config.h
${SOURCES_DIR}setup.cpp
${SOURCES_DIR}setup.h
${SOURCES_DIR}ui_components.h
${SOURCES_DIR}ui_components.cpp
${SOURCES_DIR}ui_app.cpp
${SOURCES_DIR}ui_app.h
${SOURCES_DIR}ui_frame.cpp
${SOURCES_DIR}ui_frame.h
${SOURCES_DIR}ui_onmessage.cpp
${SOURCES_DIR}manager.rc
${SOURCES_DIR}resource.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

MSVC_SET_LINK_FLAG_WINDOWS(${PROJECT_NAME})

MSVC_RUNTIME_LIBRARY_SET_MT(${PROJECT_NAME})
#[[
if(ENABLE_MSVC_CRT_MT_${MAIN_PROJECT_NAME_UPPER})
 MSVC_RUNTIME_LIBRARY_SET_MT(${PROJECT_NAME})
endif(ENABLE_MSVC_CRT_MT_${MAIN_PROJECT_NAME_UPPER})
]]
# 指定专用库头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
${SOURCES_DIR}
${CURRENT_SOLUTION_DIR}/include
${SOLUTION_ROOT_DIR}/3rdparty
${SOLUTION_ROOT_DIR}/include
${SOLUTION_ROOT_DIR}/3rdparty/spdlog/include
${SOLUTION_ROOT_DIR}/3rdparty/curlpp-0.8.1/include
${SOLUTION_ROOT_DIR}/3rdparty/curl-7.85.0/include
${SOLUTION_ROOT_DIR}/3rdparty/wxWidgets-3.2.1/include
${SOLUTION_ROOT_DIR}/3rdparty/NIM_Duilib_Framework
${SOLUTION_ROOT_DIR}/3rdparty/NIM_Duilib_Framework/base
)

# 依赖库目录
target_link_directories(${PROJECT_NAME} PRIVATE
${SOLUTION_ROOT_DIR}/3rdparty/NIM_Duilib_Framework/compile
${SOLUTION_ROOT_DIR}/librarys/3rdparty/${CMAKE_VS_PLATFORM_NAME}
${SOLUTION_ROOT_DIR}/librarys/shared/${CMAKE_VS_PLATFORM_NAME}
${SOLUTION_ROOT_DIR}/librarys/openssl/3.1.0-beta1/${CMAKE_VS_PLATFORM_NAME}
${SOLUTION_ROOT_DIR}/librarys/wxwidgets/${CMAKE_VS_PLATFORM_NAME}
)

MSVC_USE_PCH(${PROJECT_NAME} ${SOURCES_DIR}stdafx.h ${SOURCES_DIR}stdafx.cpp)




