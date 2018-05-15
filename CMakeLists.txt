project(PSU_ftrace_2017)

add_executable(server
        server/src/main.c
        server/include/server.h
        server/src/create_server.c
        server/src/main_loop.c
        server/src/connexion.c
        server/src/channels.c
        server/src/client.c)