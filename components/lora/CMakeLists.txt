set(component_srcs "LoraSx1262.c")

idf_component_register(SRCS "${component_srcs}" PRIV_REQUIRES driver bsp INCLUDE_DIRS ".")
