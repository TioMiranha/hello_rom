idf_component_register(SRCS "main.c"
    INCLUDE_DIRS "."
)

target_link_options(${COMPONENT_LIB} PRIVATE "-T${CMAKE_CURRENT_SOURCE_DIR}/hello_rom.ld")
