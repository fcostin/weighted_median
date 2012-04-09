test:
	cd src && make && cd ..
	python test_lib.py

clean:
	cd src && make clean && cd ..
