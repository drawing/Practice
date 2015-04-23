
all:
	rm -rf build
	mkdir build
	cd build;gobind -lang=java ../fancy > fancy.java
	cd build;gobind -lang=go ../fancy > fancy.go
	go build -ldflags="-shared" .

clean:
	rm -rf build
	rm -rf jar

