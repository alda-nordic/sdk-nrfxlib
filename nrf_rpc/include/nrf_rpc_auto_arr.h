/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _NRF_RPC_AUTO_ARR_H_
#define _NRF_RPC_AUTO_ARR_H_

#include <nrf_rpc_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_rpc_auto_arr Auto array nRF RPC utility
 * @{
 * @ingroup nrf_rpc
 *
 * @brief Auto array utility macros used in nRF RPC.
 */
#ifndef __in_section
#define ___in_section(a, b, c) \
	__attribute__((section(NRF_RPC_STRINGIFY(a)                            \
	                       NRF_RPC_STRINGIFY(b)                            \
			       NRF_RPC_STRINGIFY(c))))
#endif

/** @brief Default @ref NRF_RPC_AUTO_ARR implementation.
 *
 * Macro used by @ref NRF_RPC_AUTO_ARR in case OS specific implementation is
 * not provided in nrf_rpc_os.h
 */
#ifndef NRF_RPC_OS_AUTO_ARR
#define NRF_RPC_OS_AUTO_ARR(_name, _array_key)				       \
	const uint8_t NRF_RPC_CONCAT(_name, _auto_arr_end) __used	       \
	__in_section(NRF_RPC_CONCAT(nrf_rpc_, _array_key), , c);	       \
	const uint8_t *const _name __used				       \
	__in_section(NRF_RPC_CONCAT(nrf_rpc_, _array_key), , a) =	       \
		&NRF_RPC_CONCAT(_name, _auto_arr_end)
#endif

/** @brief Creates new automatically registered array.
 *
 * @param _name      Name of the array. Can be used later for
 *                   @a NRF_RPC_AUTO_ARR_FOR.
 * @param _array_key String array unique key that will be used to add items with
 *                   @a NRF_RPC_AUTO_ARR_ITEM.
 */
#define NRF_RPC_AUTO_ARR(_name, _array_key) \
	NRF_RPC_OS_AUTO_ARR(_name, _array_key)

/** @brief Default @ref NRF_RPC_AUTO_ARR implementation.
 *
 * Macro used by @ref NRF_RPC_OS_AUTO_ARR_ITEM in case OS specific
 * implementation is not provided in nrf_rpc_os.h
 */
#ifndef NRF_RPC_OS_AUTO_ARR_ITEM
#define NRF_RPC_OS_AUTO_ARR_ITEM(_type, _name, _array_key, _item_key)	       \
	_type _name __used						       \
	__in_section(NRF_RPC_CONCAT(nrf_rpc_, _array_key), , b)
#endif

/** @brief Adds new variable to the array.
 *
 * @param _type      Type of the variable.
 * @param _name      Name of the variable.
 * @param _array_key String array unique key.
 * @param _item_key  String item key.
 */
#define NRF_RPC_AUTO_ARR_ITEM(_type, _name, _array_key, _item_key) \
	NRF_RPC_OS_AUTO_ARR_ITEM(_type, _name, _array_key, _item_key)

/** @brief Iterate over array items.
 *
 * This macro must be placed in `for` brackets.
 *
 * @param _it        Pointer variable of type `void *` for iterator.
 * @param _var       Pointer variable that holds each item of the array.
 * @param _array_ptr Pointer to array.
 * @param _type      Type of items in array.
 */
#define NRF_RPC_AUTO_ARR_FOR(_it, _var, _array_ptr, _type)		       \
	(_var) = (_type *)((const uint8_t *const *)(_array_ptr) + 1);	       \
		(const uint8_t *const)_var <				       \
			*(const uint8_t *const *)(_array_ptr);		       \
		(_var) = (_type *)(_var) + 1, (void)_it

/** @brief Get item from the array.
 *
 * @param _array_ptr Pointer to array.
 * @param _index     Index of the item.
 * @param _type      Type of items in array.
 */
#define NRF_RPC_AUTO_ARR_GET(_array_ptr, _index, _type)			       \
	(((_type *)((const uint8_t *const *)(_array_ptr) + 1))[_index])

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _NRF_RPC_AUTO_ARR_H_ */
