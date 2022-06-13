set(PROJECT_NAME  Application)
set(PROJECT_INDEX 500)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SOURCE_FILES
Matrix.cpp
Vector.cpp
main.cpp
)

set(HEADER_FILES

Matrix.h
Vector.h

)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${HEADER_FILES})
