set(srcs "main.c" "include/sensors.c" "include/storage.c")
set(incs "." "include")
idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" REQUIRES driver fatfs sensors WHOLE_ARCHIVE)