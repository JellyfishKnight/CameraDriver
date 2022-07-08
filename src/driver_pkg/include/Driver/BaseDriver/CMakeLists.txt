project(BaseDriver)

aux_source_directory(. DIR_BASEDRIVER)

add_library(${PROJECT_NAME} ${DIR_BASEDRIVER})
