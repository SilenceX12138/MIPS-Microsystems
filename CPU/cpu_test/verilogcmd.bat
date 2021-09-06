cd cpu
iverilog -o output.vvp  Bridge.v CP0.v CPU.v CTRL_Hazard.v CTRL_MAIN.v ExcCode.v EXE_ALU.v EXE_EXC.v EXE_MD.v ID_CMP.v ID_EXC.v ID_EXT.v ID_NPC.v ID_RF.v IF_ADD4.v IF_EXC.v IF_IM.v IF_PC.v MEM_DM.v MEM_EXC.v mips.v MUX_forward.v MUX_normal.v Op.v PIP_D.v PIP_E.v PIP_M.v PIP_W.v Timer.v WB_RDP.v tb_mips.v
vvp output.vvp > ..\tool_exe\verilog_output.txt
del output.vvp
cd ..\tool_exe