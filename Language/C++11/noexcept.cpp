
int nothrow() noexcept {
	throw 123;
}

int main()
{
	nothrow();
	return 0;
}

