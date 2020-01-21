cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex4 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h Solver.h FileCacheManager.h CacheManager.h GeneralServer.cpp GeneralServer.h Client.h GeneralSocket.h GeneralSocket.cpp Client.cpp StringReverser.h Main.h MyTestClientHandler.h ISearchable.h State.h ISearcher.h Searcher.h BestFirstSearch.h DFS.h BFS.h Astar.h Coordinates.h Matrix.h Adapter.h TimeOutException.h BasicString.h FinalClientHandler.h MyParallelServer.h MyParallelServer.cpp)