set(srcs "main.c" "include/sensors.c" "include/comm.c")
set(incs "." "include")
idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" REQUIRES driver fatfs sensors storage lora WHOLE_ARCHIVE)