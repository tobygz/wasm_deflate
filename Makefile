all:
	@git clone https://github.com/madler/zlib.git
	@cd zlib && ./configure && cd ..
	emcc -O2 ./zlib/*.c main.c -o deflate.js -s WASM=1 -s EXPORTED_FUNCTIONS='["_malloc","_getMs","_zlibCompress","_zlibDecompress"]' -s EXPORTED_RUNTIME_METHODS='["cwrap","allocate"]' 

