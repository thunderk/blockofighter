project(blockofighter)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

if(NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif(NOT SDL_FOUND)

if(NOT SDLIMAGE_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif(NOT SDLIMAGE_FOUND)

include_directories(
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
)
target_link_libraries(blockofighter
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    SDLmain
    GL
    GLU
)
