add_executable(interpolation_task main.cpp
../LinAlg/ThreeDiagonal/ThreeDiagonalMatrix.cpp
../LinAlg/ThreeDiagonal/ThreeDiagonalMatrix.hpp
../LinAlg/vectors/Norm.hpp
../LinAlg/vectors/Vectors.hpp)
include_directories(../LinAlg)
include_directories(..)