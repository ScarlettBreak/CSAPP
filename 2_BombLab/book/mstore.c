long mult2(long,long);

void multstore(long x, long y, long *dest) {
    long t = mult2(x, y);
    *dest = t;
}

void mytest(long a){
    long s = a ^ a;
    // long q = 0;
}