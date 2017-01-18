add_subdirectory(pong_example)

add_executable(SyntheticSchmup
                    # Processing
                    main.cpp
                    
                    # Graphics
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
target_link_libraries(SyntheticSchmup ${SFML_LIBRARIES})
