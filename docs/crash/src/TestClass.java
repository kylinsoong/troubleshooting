
public class TestClass {
	
	static {
		System.loadLibrary("TestJniImpl");
	}

	public TestClass() {
	}

	public native void printHello();

        public static void main(String[] args) {
                new TestClass().printHello();
        }

}
