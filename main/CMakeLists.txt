set(srcs "main.c" "include/sensors.c" "include/comm.c" "include/fsm.c" "include/recv.c")
set(incs "." "include")
idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}" REQUIRES driver fatfs sensors storage lora slave WHOLE_ARCHIVE)