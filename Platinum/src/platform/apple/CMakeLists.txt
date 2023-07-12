target_sources(Platinum PRIVATE MetalWindow.mm MetalWindow.h MetalRenderer.mm MetalRenderer.h)

#find_library(METAL Metal REQUIRED)
#find_library(APPKIT AppKit REQUIRED)
#find_library(FOUNDATION Foundation REQUIRED)
#find_library(QUARTZCORE QuartzCore REQUIRED)

target_include_directories(Platinum PRIVATE dependencies/metal-cpp)
target_link_libraries(Platinum PRIVATE
        "-framework Metal"
        "-framework AppKit"
        "-framework Foundation"
        "-framework QuartzCore")

add_subdirectory(shaders)
