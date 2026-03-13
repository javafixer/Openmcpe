
cmake -DPUBLISH=on -B build -S handheld/project/dedicated_server
cd build
make -j$(nproc)