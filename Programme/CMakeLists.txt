add_subdirectory(pong_example)

add_executable(SyntheticSchmup
                    # Processing
                    main.cpp
                    
                    SyntheticSchmup.h
                    SyntheticSchmup.cpp
                    
                    Sound.h
                    Sound.cpp

                    # Graphics
                    Drawable.h
                    Object2D.h
                    Object2D.cpp
                    Projectile.h
                    Projectile.cpp
                    Ship.h
                    Ship.cpp

                    # States
                    IState.h
                    StateGame.h
                    StateGame.cpp
                    StateGamePaused.h
                    StateGamePaused.cpp
                    StateManager.h
                    StateManager.cpp
                    StateMenu.h
                    StateMenu.cpp
                    )
target_link_libraries(SyntheticSchmup ${SFML_LIBRARIES} ${OPENGL_LIBRARIES})

add_custom_command(TARGET SyntheticSchmup POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
