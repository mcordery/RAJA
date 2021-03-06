###############################################################################
#
# Copyright (c) 2016, Lawrence Livermore National Security, LLC.
#
# Produced at the Lawrence Livermore National Laboratory
#
# LLNL-CODE-689114
#
# All rights reserved.
#
# This file is part of RAJA.
#
# For additional details, please also read RAJA/LICENSE.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the disclaimer below.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the disclaimer (as noted below) in the
#   documentation and/or other materials provided with the distribution.
#
# * Neither the name of the LLNS/LLNL nor the names of its contributors may
#   be used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
# LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

if (NOT RAJA_ENABLE_NESTED)
  add_definitions(-DRAJA_ENABLE_NESTED)
endif()

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

set_source_files_properties(ReduceMin.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(reducemin.exe
  ReduceMin.cxx)

add_test(
    NAME reducemin
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducemin.exe>)

set_source_files_properties(ReduceMax.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(reducemax.exe
  ReduceMax.cxx)
add_test(
    NAME reducemax
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducemax.exe>)

set_source_files_properties(ReduceSum.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(reducesum.exe
  ReduceSum.cxx)
add_test(
    NAME reducesum
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducesum.exe>)

set_source_files_properties(Traversal.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(traversal.exe
  Traversal.cxx)
add_test(
    NAME traversal
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:traversal.exe>)

if(RAJA_ENABLE_OPENMP)
  set_source_files_properties(Nested.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
    cuda_add_executable(nested.exe
      Nested.cxx)
    add_test(
        NAME nested
        COMMAND ${TEST_DRIVER} $<TARGET_FILE:nested.exe>)
    target_link_libraries(nested.exe RAJA)
endif()

set_source_files_properties(ReduceMinLoc.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(reduceminloc.exe
  ReduceMinLoc.cxx)
add_test(
    NAME reduceminloc
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reduceminloc.exe>)

set_source_files_properties(ReduceMaxLoc.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(reducemaxloc.exe
  ReduceMaxLoc.cxx)
add_test(
    NAME reducemaxloc
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducemaxloc.exe>)

set_source_files_properties(test-scan.cxx PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
cuda_add_executable(scan.exe
  test-scan.cxx)
add_test(
    NAME scan
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:scan.exe>)

target_link_libraries(reducemin.exe RAJA)
target_link_libraries(reducemax.exe RAJA)
target_link_libraries(reducesum.exe RAJA)
target_link_libraries(traversal.exe RAJA)
target_link_libraries(reduceminloc.exe RAJA)
target_link_libraries(reducemaxloc.exe RAJA)
target_link_libraries(scan.exe RAJA gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
