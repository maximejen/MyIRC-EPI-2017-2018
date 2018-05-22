project(PSU_myirc_2017)

add_executable(server
        server/src/main.c
        server/include/server.h
        server/src/create_server.c
        server/src/main_loop.c
        server/src/connexion.c
        server/src/channels.c
        server/src/client.c
        server/src/broadcast.c
        server/src/cmd_manager.c
        server/src/parse_arg.c
        server/src/user_cmd.c
        server/src/cmd.c
        server/src/client_room_manager.c
        server/src/error.c
        server/src/send_msg.c
        server/src/message_format.c)

add_executable(client
        client/c_myirc/mainwindow.cpp
        client/c_myirc/mainwindow.hpp
        client/c_myirc/ApiConnection.cpp
        client/c_myirc/ApiConnection.hpp)
