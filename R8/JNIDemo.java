public class JNIDemo{
    static { 
        System.loadLibrary("sum");
    }

    private static native int sum(int[] x);

    public static void main(String[] args){
        int x[] = {1, 2, 3, 4};

        System.out.println("Java: sum() returned: " + sum(x));
    }
}