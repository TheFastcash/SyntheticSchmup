add_executable( Pong Pong.cpp )
target_link_libraries( Pong ${SFML_LIBRARIES} )

# Don't forget to add a custom command to move resources, otherwise the program won't find them at runtime
add_custom_command(TARGET Pong POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
