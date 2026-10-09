//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.1 (lin64) Build 6140274 Wed May 21 22:58:25 MDT 2025
//Date        : Thu Oct  8 16:50:57 2026
//Host        : zen running 64-bit Ubuntu 24.04.3 LTS
//Command     : generate_target dds_bd_wrapper.bd
//Design      : dds_bd_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module dds_bd_wrapper
   (M_AXIS_DATA_0_tdata,
    M_AXIS_DATA_0_tvalid,
    M_AXIS_PHASE_0_tdata,
    M_AXIS_PHASE_0_tvalid,
    S_AXIS_PHASE_0_tdata,
    S_AXIS_PHASE_0_tvalid,
    aclk_0);
  output [31:0]M_AXIS_DATA_0_tdata;
  output M_AXIS_DATA_0_tvalid;
  output [31:0]M_AXIS_PHASE_0_tdata;
  output M_AXIS_PHASE_0_tvalid;
  input [71:0]S_AXIS_PHASE_0_tdata;
  input S_AXIS_PHASE_0_tvalid;
  input aclk_0;

  wire [31:0]M_AXIS_DATA_0_tdata;
  wire M_AXIS_DATA_0_tvalid;
  wire [31:0]M_AXIS_PHASE_0_tdata;
  wire M_AXIS_PHASE_0_tvalid;
  wire [71:0]S_AXIS_PHASE_0_tdata;
  wire S_AXIS_PHASE_0_tvalid;
  wire aclk_0;

  dds_bd dds_bd_i
       (.M_AXIS_DATA_0_tdata(M_AXIS_DATA_0_tdata),
        .M_AXIS_DATA_0_tvalid(M_AXIS_DATA_0_tvalid),
        .M_AXIS_PHASE_0_tdata(M_AXIS_PHASE_0_tdata),
        .M_AXIS_PHASE_0_tvalid(M_AXIS_PHASE_0_tvalid),
        .S_AXIS_PHASE_0_tdata(S_AXIS_PHASE_0_tdata),
        .S_AXIS_PHASE_0_tvalid(S_AXIS_PHASE_0_tvalid),
        .aclk_0(aclk_0));
endmodule
