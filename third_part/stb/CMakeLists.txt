
add_library(stb STATIC  src/stb.c include/stb/stb_image.h)

target_include_directories(stb PUBLIC include)
