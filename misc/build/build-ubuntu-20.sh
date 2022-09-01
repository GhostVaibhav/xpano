# DO NOT MODIFY: Auto-generated by the gen_installer.py script from the .github/workflows/ubuntu.yml Github Action

export BUILD_TYPE='Release'
export CATCH_VERSION='v3.1.0'
export OPENCV_VERSION='4.6.0'
export SDL_VERSION='release-2.24.0'

git submodule update --init


git clone https://github.com/catchorg/Catch2.git catch --depth 1 --branch $CATCH_VERSION
cd catch
cmake -B build \
  -DCMAKE_C_COMPILER=gcc-10 \
  -DCMAKE_CXX_COMPILER=g++-10 \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DCMAKE_INSTALL_PREFIX=install \
  -DBUILD_TESTING=OFF
cmake --build build --target install -j $(nproc)
cd ..


git clone https://github.com/opencv/opencv.git --depth 1 --branch $OPENCV_VERSION
cd opencv
cmake -B build \
  -DCMAKE_C_COMPILER=gcc-10 \
  -DCMAKE_CXX_COMPILER=g++-10 \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DCMAKE_INSTALL_PREFIX=install \
  `cat ../misc/build/opencv_minimal_flags.txt`
cmake --build build --target install -j $(nproc)
cd ..


git clone https://github.com/libsdl-org/SDL.git --depth 1 --branch $SDL_VERSION
cd SDL
cmake -B build \
  -DCMAKE_C_COMPILER=gcc-10 \
  -DCMAKE_CXX_COMPILER=g++-10 \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DCMAKE_INSTALL_PREFIX=install
cmake --build build --target install -j $(nproc)
cd ..

cmake -B build \
  -DCMAKE_C_COMPILER=gcc-10 \
  -DCMAKE_CXX_COMPILER=g++-10 \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DCMAKE_INSTALL_PREFIX=install \
  -DBUILD_TESTING=ON \
  -DCatch2_DIR=../catch/install/lib/cmake/Catch2 \
  -DOpenCV_DIR=opencv/install/lib/cmake/opencv4 \
  -DSDL2_DIR=SDL/install/lib/cmake/SDL2

cmake --build build -j $(nproc) --target install
cd build
ctest
cd ..
