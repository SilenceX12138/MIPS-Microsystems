cd std_cpu
iverilog -o output.vvp alu.v bridge.v cmp.v cp0.v cpu.v ctrl.v defines.v dm.v dmdecode.v dmext.v ex.v ext.v forward.v grf.v id.v if.v im.v mem.v mips.v multdiv.v mux.v npc.v pc.v pipe.v stall.v timer.v wb.v tb_mips.v 
vvp output.vvp > ..\tool_exe\verilog_output.txt
del output.vvp
cd ..\tool_exe
ex_verilog_filter.exe
rename verilog_ans.txt MARS_ans.txt
move MARS_ans.txt ..\output
cd ..

cd cpu
iverilog -o output.vvp Bridge.v CPU.v CTRL_Hazard.v CTRL_MAIN.v ExcCode.v EXC_EXE.v EXC_ID.v EXC_IF.v EXC_MEM.v EXE_ALU.v EXE_MD.v head_uart.v ID_CMP.v ID_EXT.v ID_NPC.v ID_RF.v IF_ADD4.v IF_IM.v IF_PC.v MEM_CP0.v MEM_DM.v mips.v MUX_forward.v MUX_normal.v Op.v PIP_D.v PIP_E.v PIP_M.v PIP_W.v PR_Key.v PR_LED.v PR_Switch.v PR_Timer.v PR_Tube.v tb_mips.v UART_rxd.v UART_txd.v UART_uart.v UART_utils.v WB_RDP.v 
vvp output.vvp > ..\tool_exe\verilog_output.txt
del output.vvp
cd ..\tool_exe
verilog_filter.exe
move verilog_ans.txt ..\output
del verilog_output.txt
cd ..

cd output
cmp.exe