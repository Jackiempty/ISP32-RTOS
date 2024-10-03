set(srcs "main.c" "include/sensors.c")
set(incs "." "include")
idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "${incs}")