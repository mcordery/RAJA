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
# For additional details, please also read raja/README-license.txt.
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

add_definitions(-DRAJA_ENABLE_NESTED)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

cuda_add_executable(reducemin.exe
  ReduceMin.cxx)

add_test(
    NAME reducemin
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducemin.exe>)

cuda_add_executable(reducemax.exe
  ReduceMax.cxx)
add_test(
    NAME reducemax
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducemax.exe>)

cuda_add_executable(reducesum.exe
  ReduceSum.cxx)
add_test(
    NAME reducesum
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducesum.exe>)

cuda_add_executable(traversal.exe
  Traversal.cxx)
add_test(
    NAME traversal
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:traversal.exe>)

cuda_add_executable(nested.exe
  Nested.cxx)
add_test(
    NAME nested
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:nested.exe>)

cuda_add_executable(reduceminloc.exe
  ReduceMinLoc.cxx)
add_test(
    NAME reduceminloc
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reduceminloc.exe>)

cuda_add_executable(reducemaxloc.exe
  ReduceMaxLoc.cxx)
add_test(
    NAME reducemaxloc
    COMMAND ${TEST_DRIVER} $<TARGET_FILE:reducemaxloc.exe>)

target_link_libraries(reducemin.exe RAJA)
target_link_libraries(reducemax.exe RAJA)
target_link_libraries(reducesum.exe RAJA)
target_link_libraries(traversal.exe RAJA)
target_link_libraries(nested.exe RAJA)
target_link_libraries(reduceminloc.exe RAJA)
target_link_libraries(reducemaxloc.exe RAJA)