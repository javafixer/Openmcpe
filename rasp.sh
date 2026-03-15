export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH # add vitasdk tool to $PATH
cmake -DPUBLISH=on -B build -S handheld/project/raspberry
cd build
make -j$(nproc)