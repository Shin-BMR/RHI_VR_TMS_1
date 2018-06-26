
set(header_include
)

# grouping
source_group("include" FILES ${header_include})

set(module_headers
    ${header_include}
)

set(source_src
    "${PROJECT_SOURCE_DIR}/src/example_application.cpp"
    "${PROJECT_SOURCE_DIR}/src/example_application.h"
    "${PROJECT_SOURCE_DIR}/src/examples.h"
)

set(source_src_examples
    "${PROJECT_SOURCE_DIR}/src/examples/example_spatialTouch.cpp"
    "${PROJECT_SOURCE_DIR}/src/examples/setup_event.cpp"
)

# grouping
source_group("src" FILES ${source_src})
source_group("src\\examples" FILES ${source_src_examples})

set(module_sources
    ${source_src}
    ${source_src_examples}
)
