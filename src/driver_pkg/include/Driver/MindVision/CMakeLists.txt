project(MindVision)

aux_source_directory(. DIR_MINDVISION)

add_library(${PROJECT_NAME} ${DIR_MINDVISION})

link_directories(./lib)
link_libraries(MVSDK)
