cmake_minimum_required(VERSION 3.16)
# set app name
set(APP_NAME ImageSharingSystem)

# set path
set(EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(GLFW_PATH ${EXTERNAL_PATH}/glfw)
set(GLEW_PATH ${EXTERNAL_PATH}/glew)
set(SPOUT2_PATH ${EXTERNAL_PATH}/spout2)
set(GLM ${EXTERNAL_PATH}/glm)
set(STB ${EXTERNAL_PATH}/stb)

# set glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_INSTALL OFF CACHE BOOL " " FORCE)
set(GLFW_USE_CHDIR OFF CACHE BOOL " " FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL " " FORCE)
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

# specify version of compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set project
project(${APP_NAME})
# set visual studio startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${APP_NAME})
# set configuration
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "Configurations" FORCE)
# make executable app
add_executable(${APP_NAME})
# add source files
add_subdirectory(src)
# suppress generation of ZERO_CHECK project
set(CMAKE_SUPPRESS_REGENERATION ON)
# set additional include directories
target_include_directories(
    ${APP_NAME}
    PUBLIC
    ${GLEW_PATH}/include
    ${GLFW_PATH}/include
    ${SPOUT2_PATH}/SPOUTSDK/SpoutGL
    ${GLM}
    ${STB}
    ${CMAKE_CURRENT_SOURCE_DIR}/shader
)

# add glfw and glew project
add_subdirectory(${GLFW_PATH} ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(${GLEW_PATH}/build/cmake ${CMAKE_CURRENT_BINARY_DIR}/glew)
add_subdirectory(${SPOUT2_PATH}/SPOUTSDK/SpoutGL ${CMAKE_CURRENT_BINARY_DIR}/spout)
# find opengl
find_package(OpenGL REQUIRED)

# set additional link 
target_link_libraries(
    ${APP_NAME}
    ${OPENGL_LIBRARIES}
    glfw
    glew_s
    Spout_static
)

# add preprocessor def
if(SENDER)
    target_compile_definitions(${APP_NAME} PUBLIC SENDER)
else()
    target_compile_definitions(${APP_NAME} PUBLIC RECEIVER)
endif()