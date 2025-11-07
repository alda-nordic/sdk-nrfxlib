#
# Copyright (c) 2020 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

zephyr_include_directories(include)

zephyr_library()
zephyr_library_sources(nrf_rpc.c)

zephyr_library_sources_ifdef(CONFIG_NRF_RPC_CBOR nrf_rpc_cbor.c)

zephyr_linker_sources(SECTIONS nrf_rpc.ld)
zephyr_linker_section(
  NAME nrf_rpc
  GROUP ROM_REGION
  NOINPUT
)
zephyr_linker_section_configure(
  SECTION nrf_rpc
  KEEP
  SORT NAME
  INPUT "nrf_rpc"
        "nrf_rpc_grp**"
)
