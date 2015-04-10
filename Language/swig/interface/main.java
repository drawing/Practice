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
}
}

public class main {
	public static void main(String argv[]) {
		System.load("/Users/bodeng/Documents/tools/Practice/Language/swig/interface/libdrawing.so");
		Painter painter = new Painter();
		painter.drawShape(new Circle());
	}
}

