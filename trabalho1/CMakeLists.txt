cmake_minimum_required(VERSION 3.25)
project(trabalho1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(trabalho1
        HistoryEarning.cpp
        HistoryEarning.h
        HistoryPrice.cpp
        HistoryPrice.h
        main.cpp
        MinMax.cpp
        MinMax.h
        SortMethods.cpp
        SortMethods.h
        Wallet.cpp
        Wallet.h BoughtStock.h BoughtStock.cpp StockPriceQtd.h StockPriceQtd.cpp)
