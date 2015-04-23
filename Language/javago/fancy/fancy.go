package fancy

func Calc(a, b int) int {
	return a + b
}

type Callback interface {
	Done(msg string)
}

func TestCallback(cb Callback) {
	cb.Done("succ done")
}
