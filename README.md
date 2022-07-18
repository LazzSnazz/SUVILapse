# SUVILapse
A simple converter that preps SUVI (and ABI) images to be made into timelapses

WIP galore
# Usage
```
./SUVILapse /path/to/input /path/to/output [Mode SUVI,ABI] [SUVI Channel 094, 132, 171, 195, 284, 304] #note that SUVI channel is not required when using mode ABI
```
# Install

```
# install dependencies
sudo apt install libopencv-dev cmake imagemagick git g++

# install SUVILapse
git clone https://github.com/LazzSnazz/SUVILapse.git
cd SUVILapse
mkdir build
cd build
cmake ..
build -j4

Done!
```

