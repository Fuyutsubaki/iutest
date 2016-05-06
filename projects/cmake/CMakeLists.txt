########################################################################
# CMake build script for iutest.
#

# option
option(build_gtest_samples "gtest sample build." OFF)

# Defines pre_project_set_up_hermetic_build() and set_up_hermetic_build().
include(cmake/hermetic_build.cmake OPTIONAL)

if (COMMAND pre_project_set_up_hermetic_build)
  pre_project_set_up_hermetic_build()
endif()

########################################################################
#
# Project-wide settings

# �v���W�F�N�g��
project(iutest CXX C)

# CMake �o�[�W����
cmake_minimum_required(VERSION 2.6.2)

if (COMMAND set_up_hermetic_build)
  set_up_hermetic_build()
endif()

# include
include(internal_utils.cmake)
config_compiler_and_linker()  # Defined in internal_utils.cmake.

# �C���N���[�h�p�X
include_directories(
  ${PROJECT_SOURCE_DIR}/../../include
  )


########################################################################
#
# ���C�u����
#
cxx_library(iutest "${cxx_strict}" ../../src/iutest_all.cpp)
cxx_library(iutest_main "${cxx_strict}" ../../src/iutest_main.cpp)

########################################################################
#
# �T���v��
#
cxx_executable_sample(iutest_sample
 ../../samples/main.cpp
 ../../samples/assertion.cpp
 ../../samples/disabledtest.cpp
 ../../samples/exception.cpp
 ../../samples/fixture.cpp
 ../../samples/matcher.cpp
 ../../samples/parameterized.cpp
 ../../samples/printto.cpp
 ../../samples/simple.cpp
 ../../samples/typed.cpp
 )

########################################################################
#
# gtest �T���v��
#
if (build_gtest_samples)
  cxx_executable_gtest_sample(sample1_unittest  ../../samples/gtest sample1.cc)
  cxx_executable_gtest_sample(sample2_unittest  ../../samples/gtest sample2.cc)
  cxx_executable_gtest_sample(sample3_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample4_unittest  ../../samples/gtest sample4.cc)
  cxx_executable_gtest_sample(sample5_unittest  ../../samples/gtest sample1.cc)
  cxx_executable_gtest_sample(sample6_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample7_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample8_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample9_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample10_unittest ../../samples/gtest )
endif()
