
export JAVA_HOME="/home/nishant/jdk1.8.0_111"
export PATH="$PATH:$JAVA_HOME/bin"

gcc -o /usr/lib/libWriteFIFO.so -m64 -shared -I"$JAVA_HOME/include" -MD -LD -fPIC -I"$JAVA_HOME/include/linux" writeFIFO.c
gcc -o /usr/lib/libReadFIFO.so -m64 -shared -I"$JAVA_HOME/include" -MD -LD -fPIC -I"$JAVA_HOME/include/linux" readFIFO.c
gcc -I"$JAVA_HOME/include" -MD -LD -fPIC -I"$JAVA_HOME/include/linux" 11.c -lpthread


sudo /home/ubuntu/jdk1.8.0_111/binava SAND.java.Main
