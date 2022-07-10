project(PreProcess)

aux_source_directory(. DIR_PREPROCESS)

add_library(${PROJECT_NAME} ${DIR_PREPROCESS})


