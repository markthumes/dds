startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:dds_compiler:6.0 dds_compiler_0
endgroup
set_property -dict [list \
  CONFIG.DATA_Has_TLAST {Not_Required} \
  CONFIG.DDS_Clock_Rate {310} \
  CONFIG.Frequency_Resolution {0.1} \
  CONFIG.Has_Phase_Out {false} \
  CONFIG.Latency {11} \
  CONFIG.M_DATA_Has_TUSER {Not_Required} \
  CONFIG.Noise_Shaping {Auto} \
  CONFIG.OUTPUT_FORM {Twos_Complement} \
  CONFIG.Optimization_Goal {Speed} \
  CONFIG.Output_Frequency1 {0} \
  CONFIG.Output_Width {16} \
  CONFIG.PINC1 {0} \
  CONFIG.Phase_Increment {Streaming} \
  CONFIG.Phase_Width {32} \
  CONFIG.Phase_offset {Streaming} \
  CONFIG.Resync {true} \
  CONFIG.S_PHASE_Has_TUSER {Not_Required} \
  CONFIG.Spurious_Free_Dynamic_Range {96} \
] [get_bd_cells dds_compiler_0]
