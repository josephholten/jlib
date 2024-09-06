find_package(benchmark REQUIRED)

set(benches util.bench.cpp)

foreach(benchfile ${benches})
  cmake_path(GET benchfile STEM LAST_ONLY bench)
  add_executable(${bench} ${benchfile})
  target_link_libraries(${bench} benchmark::benchmark_main)
  target_compile_options(${bench} PRIVATE ${JLIB_RELEASE_FLAGS})
endforeach(benchfile ${benches})
