export JAVA_HOME="/home/ubuntu/jdk1.8.0_111"
export PATH=$PATH:$JAVA_HOME/bin
export SRC="/media/Store/Coding/java/SAND"
gcc -L"$JAVA_HOME/jre/lib/amd64/server" -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" "$SRC/src/Test.c" -lpthread -ljvm  && ./a.out



