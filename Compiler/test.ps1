cd bin
rm * -Exclude *test*, *Compiler*, *Mars*, *.py
./Compiler.exe
python translator.py
java -jar Mars-jdk7-Re-v5.jar nc ae2 mc Default mips.txt > output.txt
cd ..
cat .\bin\output.txt