/*
 *
 * Copyright (C) 2023-2024 Intel Corporation
 *
 * Under the Apache License v2.0 with LLVM Exceptions. See LICENSE.TXT.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 */

#ifndef UMF_MEMSPACE_INTERNAL_H
#define UMF_MEMSPACE_INTERNAL_H 1

#include <umf/memspace.h>

#include "base_alloc.h"
#include "memory_target.h"

#ifdef __cplusplus
extern "C" {
#endif

struct umf_memspace_t {
    size_t size;
    umf_memory_target_handle_t *nodes;
};

///
/// \brief Clones memspace
///
umf_result_t umfMemspaceClone(umf_memspace_handle_t hMemspace,
                              umf_memspace_handle_t *outHandle);

typedef umf_result_t (*umfGetPropertyFn)(umf_memory_target_handle_t,
                                         uint64_t *);

///
/// \brief Sorts memspace by getProperty() in descending order
///
umf_result_t umfMemspaceSortDesc(umf_memspace_handle_t hMemspace,
                                 umfGetPropertyFn getProperty);

typedef umf_result_t (*umfGetTargetFn)(umf_memory_target_handle_t initiator,
                                       umf_memory_target_handle_t *nodes,
                                       size_t numNodes,
                                       umf_memory_target_handle_t *target);

///
/// \brief Filters the targets using getTarget() to create a new memspace
///
umf_result_t umfMemspaceFilter(umf_memspace_handle_t hMemspace,
                               umfGetTargetFn getTarget,
                               umf_memspace_handle_t *filteredMemspace);

///
/// \brief Destroys memspace
/// \param hMemspace handle to memspace
///
void umfMemspaceDestroy(umf_memspace_handle_t hMemspace);

void umfMemspaceHostAllDestroy(void);
void umfMemspaceHighestCapacityDestroy(void);
void umfMemspaceHighestBandwidthDestroy(void);

#ifdef __cplusplus
}
#endif

#endif /* UMF_MEMSPACE_INTERNAL_H */
