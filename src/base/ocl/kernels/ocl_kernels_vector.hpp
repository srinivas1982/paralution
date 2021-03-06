// **************************************************************************
//
//    PARALUTION   www.paralution.com
//
//    Copyright (C) 2015  PARALUTION Labs UG (haftungsbeschränkt) & Co. KG
//                        Am Hasensprung 6, 76571 Gaggenau
//                        Handelsregister: Amtsgericht Mannheim, HRA 706051
//                        Vertreten durch:
//                        PARALUTION Labs Verwaltungs UG (haftungsbeschränkt)
//                        Am Hasensprung 6, 76571 Gaggenau
//                        Handelsregister: Amtsgericht Mannheim, HRB 721277
//                        Geschäftsführer: Dimitar Lukarski, Nico Trost
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// **************************************************************************



// PARALUTION version 1.0.0 


#ifndef PARALUTION_OCL_KERNELS_VECTOR_HPP_
#define PARALUTION_OCL_KERNELS_VECTOR_HPP_

namespace paralution {

const char *ocl_kernels_vector =
	"__kernel void kernel_scale(const int size, const ValueType alpha, __global ValueType *x) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    x[gid] = alpha * x[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_scaleadd(const int size, const ValueType alpha,\n"
	"                              __global const ValueType *x, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] = alpha * out[gid] + x[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_scaleaddscale(const int size, const ValueType alpha, const ValueType beta, \n"
	"                                   __global const ValueType *x, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] = alpha * out[gid] + beta * x[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_scaleaddscale_offset(const int size, const int src_offset, const int dst_offset, \n"
	"                                          const ValueType alpha, const ValueType beta, \n"
	"                                          __global const ValueType *x, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid+dst_offset] = alpha * out[gid+dst_offset] + beta * x[gid+src_offset];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_scaleadd2(const int size, const ValueType alpha, const ValueType beta, const ValueType gamma,\n"
	"                               __global const ValueType *x, __global const ValueType *y, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] = alpha * out[gid] + beta * x[gid] + gamma * y[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_pointwisemult(const int size, __global const ValueType *x, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] = out[gid] * x[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_pointwisemult2(const int size, __global const ValueType *x, __global const ValueType *y,\n"
	"                                    __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] = y[gid] * x[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_copy_offset_from(const int size, const int src_offset, const int dst_offset,\n"
	"                                      __global const ValueType *in, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid+dst_offset] = in[gid+src_offset];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_permute(const int size, __global const int *permute,\n"
	"                             __global const ValueType *in, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[permute[gid]] = in[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_permute_backward(const int size, __global const int *permute,\n"
	"                                      __global const ValueType *in, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] = in[permute[gid]];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_dot(const       int  size,\n"
	"                         __global const ValueType *x, __global const ValueType *y,\n"
	"                         __global       ValueType *out, __local        ValueType *sdata,\n"
	"                         const       int  GROUP_SIZE, const       int  LOCAL_SIZE) {\n"
	"\n"
	"    int tid = get_local_id(0);\n"
	"\n"
	"    sdata[tid] = (ValueType)(0.0);\n"
	"\n"
	"    int group_id = GROUP_SIZE * get_group_id(0);\n"
	"    int gid = group_id + tid;\n"
	"\n"
	"    for (int i = 0; i < LOCAL_SIZE; ++i, gid += BLOCK_SIZE) {\n"
	"\n"
	"      if (gid < size)\n"
	"        sdata[tid] += x[gid] * y[gid];\n"
	"      else\n"
	"        i = LOCAL_SIZE;\n"
	"\n"
	"    }\n"
	"\n"
	"    barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    for (int i = BLOCK_SIZE/2; i > 0; i /= 2) {\n"
	"\n"
	"      if (tid < i)\n"
	"        sdata[tid] += sdata[tid + i];\n"
	"\n"
	"      barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    }\n"
	"\n"
	"    if (tid == 0)\n"
	"      out[get_group_id(0)] = sdata[tid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_dotc(const int size,\n"
	"                          __global const ValueType *x, __global const ValueType *y,\n"
	"                          __global ValueType *out, __local ValueType *sdata,\n"
	"                          const int GROUP_SIZE, const int LOCAL_SIZE) {\n"
	"\n"
	"    int tid = get_local_id(0);\n"
	"\n"
	"    sdata[tid] = (ValueType)(0.0);\n"
	"\n"
	"    int group_id = GROUP_SIZE * get_group_id(0);\n"
	"    int gid = group_id + tid;\n"
	"\n"
	"    for (int i = 0; i < LOCAL_SIZE; ++i, gid += BLOCK_SIZE) {\n"
	"\n"
	"      if (gid < size)\n"
	"        sdata[tid] += x[gid] * y[gid];\n"
	"      else\n"
	"        i = LOCAL_SIZE;\n"
	"\n"
	"    }\n"
	"\n"
	"    barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    for (int i = BLOCK_SIZE/2; i > 0; i /= 2) {\n"
	"\n"
	"      if (tid < i)\n"
	"        sdata[tid] += sdata[tid + i];\n"
	"\n"
	"      barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    }\n"
	"\n"
	"    if (tid == 0)\n"
	"      out[get_group_id(0)] = sdata[tid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_norm(const int  size, __global const ValueType *x,\n"
	"                         __global ValueType *out, __local ValueType *sdata,\n"
	"                         const int GROUP_SIZE, const int  LOCAL_SIZE) {\n"
	"\n"
	"    int tid = get_local_id(0);\n"
	"\n"
	"    sdata[tid] = (ValueType)(0.0);\n"
	"\n"
	"    int group_id = GROUP_SIZE * get_group_id(0);\n"
	"    int gid = group_id + tid;\n"
	"\n"
	"    for (int i = 0; i < LOCAL_SIZE; ++i, gid += BLOCK_SIZE) {\n"
	"\n"
	"      if (gid < size)\n"
	"        sdata[tid] += x[gid] * x[gid];\n"
	"      else\n"
	"        i = LOCAL_SIZE;\n"
	"\n"
	"    }\n"
	"\n"
	"    barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    for (int i = BLOCK_SIZE/2; i > 0; i /= 2) {\n"
	"\n"
	"      if (tid < i)\n"
	"        sdata[tid] += sdata[tid + i];\n"
	"\n"
	"      barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    }\n"
	"\n"
	"    if (tid == 0)\n"
	"      out[get_group_id(0)] = sdata[tid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_axpy(const int size, const ValueType alpha,\n"
	"                          __global const ValueType *x, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < size)\n"
	"    out[gid] += alpha * x[gid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_reduce(         const       int  size,\n"
	"                            __global const ValueType *data,\n"
	"                            __global       ValueType *out,\n"
	"                            __local        ValueType *sdata,\n"
	"                                     const       int  GROUP_SIZE,\n"
	"                                     const       int  LOCAL_SIZE) {\n"
	"\n"
	"    int tid = get_local_id(0);\n"
	"\n"
	"    sdata[tid] = (ValueType)(0.0);\n"
	"\n"
	"    int gid = GROUP_SIZE * get_group_id(0) + tid;\n"
	"\n"
	"    for (int i = 0; i < LOCAL_SIZE; ++i, gid += BLOCK_SIZE) {\n"
	"\n"
	"      if (gid < size)\n"
	"        sdata[tid] += data[gid];\n"
	"      else\n"
	"        i = LOCAL_SIZE;\n"
	"\n"
	"    }\n"
	"\n"
	"    barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    for (int i = BLOCK_SIZE/2; i > 0; i /= 2) {\n"
	"\n"
	"      if ( tid < i )\n"
	"        sdata[tid] += sdata[tid + i];\n"
	"\n"
	"      barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    }\n"
	"\n"
	"    if (tid == 0)\n"
	"      out[get_group_id(0)] = sdata[tid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_asum(         const       int  size,\n"
	"                          __global const ValueType *data,\n"
	"                          __global       ValueType *out,\n"
	"                          __local        ValueType *sdata,\n"
	"                                   const       int  GROUP_SIZE,\n"
	"                                   const       int  LOCAL_SIZE) {\n"
	"\n"
	"    int tid = get_local_id(0);\n"
	"\n"
	"    sdata[tid] = (ValueType)(0.0);\n"
	"\n"
	"    int gid = GROUP_SIZE * get_group_id(0) + tid;\n"
	"\n"
	"    for (int i = 0; i < LOCAL_SIZE; ++i, gid += BLOCK_SIZE) {\n"
	"\n"
	"      if (gid < size)\n"
	"        sdata[tid] += fabs(data[gid]);\n"
	"      else\n"
	"        i = LOCAL_SIZE;\n"
	"\n"
	"    }\n"
	"\n"
	"    barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    for (int i = BLOCK_SIZE/2; i > 0; i /= 2) {\n"
	"\n"
	"      if (tid < i)\n"
	"        sdata[tid] += sdata[tid + i];\n"
	"\n"
	"      barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    }\n"
	"\n"
	"    if (tid == 0)\n"
	"      out[get_group_id(0)] = sdata[tid];\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_amax(         const       int  size,\n"
	"                          __global const ValueType *data,\n"
	"                          __global       ValueType *out,\n"
	"                          __global             int *iout,\n"
	"                          __local        ValueType *sdata,\n"
	"                          __local              int *idata,\n"
	"                                   const       int  GROUP_SIZE,\n"
	"                                   const       int  LOCAL_SIZE) {\n"
	"\n"
	"    int tid = get_local_id(0);\n"
	"\n"
	"    sdata[tid] = (ValueType)(0.0);\n"
	"    idata[tid] = 0;\n"
	"\n"
	"    int gid = GROUP_SIZE * get_group_id(0) + tid;\n"
	"\n"
	"    for (int i = 0; i < LOCAL_SIZE; ++i, gid += BLOCK_SIZE) {\n"
	"\n"
	"      if (gid < size) {\n"
	"        ValueType tmp = data[gid];\n"
	"        if (fabs(tmp) > fabs(sdata[tid])) {\n"
	"          sdata[tid] = fabs(tmp);\n"
	"          idata[tid] = gid;\n"
	"        }\n"
	"      }\n"
	"\n"
	"    }\n"
	"\n"
	"    barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    for (int i = BLOCK_SIZE/2; i > 0; i /= 2) {\n"
	"\n"
	"      if (tid < i) {\n"
	"        ValueType tmp = sdata[tid+i];\n"
	"        if (fabs(tmp) > fabs(sdata[tid])) {\n"
	"          sdata[tid] = fabs(tmp);\n"
	"          idata[tid] = idata[tid+i];\n"
	"        }\n"
	"      }\n"
	"\n"
	"      barrier(CLK_LOCAL_MEM_FENCE);\n"
	"\n"
	"    }\n"
	"\n"
	"    if (tid == 0) {\n"
	"      out[get_group_id(0)] = sdata[tid];\n"
	"      iout[get_group_id(0)] = idata[tid];\n"
	"    }\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_power(const int n, const double power, __global ValueType *out) {\n"
	"\n"
	"  int gid = get_global_id(0);\n"
	"\n"
	"  if (gid < n)\n"
	"    out[gid] = pow(out[gid], (ValueType)(power));\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_copy_from_float(const int n, __global const float *in, __global ValueType *out) {\n"
	"\n"
	"  int ind = get_global_id(0);\n"
	"\n"
	"  if (ind < n)\n"
	"    out[ind] = (ValueType)(in[ind]);\n"
	"\n"
	"}\n"
	"\n"
	"__kernel void kernel_copy_from_double(const int n, __global const double *in, __global ValueType *out) {\n"
	"\n"
	"  int ind = get_global_id(0);\n"
	"\n"
	"  if (ind < n)\n"
	"    out[ind] = (ValueType)(in[ind]);\n"
	"\n"
	"}\n"
	"\n"
;
}

#endif // PARALUTION_OCL_KERNELS_VECTOR_HPP_
