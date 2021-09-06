java -jar AAAMarsMOD.jar a mc CompactDataAtZero dump .text HexText cpu/code.txt testdata/*.asm 
java -jar AAAMarsMOD.jar db nc 40 ae2 mc CompactDataAtZero testdata/*.asm > tool_exe/MARS_data.txt
cd tool_exe
MARS_filter.exe
move MARS_ans.txt ../output

