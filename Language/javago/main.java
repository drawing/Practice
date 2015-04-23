import go.fancy;
import go.Go;

class CB extends Fancy.Callback {
	public void Done(String msg) {
		
	}
}

public class main {
	public static void main(String argv[]) {
		System.load("/Users/bodeng/Documents/tools/Practice/Language/swig/interface/libdrawing.so");

		Go.init(null);

		int sum = Fancy.Calc(1, 2);
	}
}

