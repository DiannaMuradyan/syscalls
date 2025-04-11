set(CMAKE_C_STANDARD 11)

# If you have your own custom entry point (e.g., _start)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib")

# Build the executable
add_executable(task task.c)

# Optionally: copy file.txt into build dir
configure_file(file.txt file.txt COPYONLY)

