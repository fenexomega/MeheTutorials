project(movingInAWorld)
cmake_minimum_required(VERSION 2.8)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(FreeImage REQUIRED)

INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR} ${FREEIMAGE_INCLUDE_DIR})


aux_source_directory(src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
                ${GLUT_LIBRARIES}
                ${FREEIMAGE_LIBRARY}
                ${OPENGL_LIBRARY})
