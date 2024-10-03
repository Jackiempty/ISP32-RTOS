set(srcs "bmp280.c")
idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "." REQUIRES bsp)