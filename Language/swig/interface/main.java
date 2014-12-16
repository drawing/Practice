// exec command:
// java -classpath drawing.jar:. main


import com.tencent.shape.Shape;
import com.tencent.shape.Painter;

class Circle extends Shape {
public void draw() {
	System.out.println("drawing a circle");
}
}

public class main {
	public static void main(String argv[]) {
		System.load("/Users/bodeng/Documents/tools/Practice/Language/swig/interface/libdrawing.so");
		Painter painter = new Painter();
		painter.drawShape(new Circle());
	}
}

