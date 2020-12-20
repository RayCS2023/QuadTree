all: qttest 

qttest: QuadTree.cpp QuadTree.hpp qttest.cpp
		g++ -std=c++11 -o qttest qttest.cpp 

run:    qttest
	./qttest < test1.in > out1.out
	./qttest < test2.in > out2.out
	./qttest < test3.in > out3.out
	./qttest < test4.in > out4.out
	./qttest < test5.in > out5.out
	./qttest < test6.in > out6.out
	./qttest < test7.in > out7.out
	./qttest < mytest1.in > mytestout1.out
	./qttest < mytest2.in > mytestout2.out
	./qttest < Anson_test01.in > Anson_test01out.in

