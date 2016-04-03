// exec command:
// java -classpath drawing.jar:. main


import com.tencent.shape.Shape;
import com.tencent.shape.Painter;
import com.tencent.shape.Param;

class Circle extends Shape {
public void draw(Param param) {
	System.out.println(param.getOne());
	System.out.println(param.getTwo());
	System.out.println("drawing a circle");

	String s = null;
	s.charAt(1);
}
}

public class main {
	public static void main(String argv[]) {
		System.load("/home/cppbreak/workspace/Practice/Language/swig/exception/callback/libdrawing.so");

		System.out.println("start...");
		new Thread() {
			public void run() {
				Painter painter = new Painter();
				painter.drawShape(new Circle());
			}
		}.start();
		
		System.out.println("end...");

		try {
			for (int i = 0; i < 100; i++) {
				System.out.println("main thread");
				Thread.sleep(1000);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}

