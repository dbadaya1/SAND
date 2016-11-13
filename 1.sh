export SRC="/home/ubuntu/SAND"

export JAVA_HOME="/home/ubuntu/jdk1.8.0_111"

export PATH="$PATH:$JAVA_HOME/bin"

cd src
javah -d ../out -jni SAND.java.WriteFIFO
javah -d ../out -jni SAND.java.ReadFIFO


cd "$SRC/src/SAND/c"
sudo gcc -o /usr/lib/libWriteFIFO.so -m64 -shared -I"$JAVA_HOME/include" -MD -LD -fPIC -I"$JAVA_HOME/include/linux" writeFIFO.c
sudo gcc -o /usr/lib/libReadFIFO.so -m64 -shared -I"$JAVA_HOME/include" -MD -LD -fPIC -I"$JAVA_HOME/include/linux" readFIFO.c
sudo gcc -I"$JAVA_HOME/include" -MD -LD -fPIC -I"$JAVA_HOME/include/linux" 11.c -lpthread


cd "$SRC/src/SAND/java"
"$JAVA_HOME/bin/javac" -d ../../../out *.java

#cd "$SRC/out"
#sudo "$JAVA_HOME/bin/java" SAND.java.Main
cd "$SRC/src/SAND/c"
./a.out

#"/home/ubuntu/jdk1.8.0_111/bin/java" SAND.java.Main