cmake_minimum_required(VERSION 2.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(add)

target_sources(app PRIVATE src/main.c)
