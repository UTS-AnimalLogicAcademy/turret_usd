set(DIRS
    ar
)

foreach(d ${DIRS})
    add_subdirectory(${d})
endforeach()

