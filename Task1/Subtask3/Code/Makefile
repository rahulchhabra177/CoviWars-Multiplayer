all:
	g++ video.cpp -o video -lpthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ video_m1.cpp -o video1 -lpthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ video_m2.cpp -o video2 -lpthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ video_m3.cpp -o video3 -lpthread -std=c++11 `pkg-config --cflags --libs opencv` && g++ video_m4.cpp -o video4 -lpthread -std=c++11 `pkg-config --cflags --libs opencv`

clean: 
	rm video && rm video1 && rm video2 && rm video3 && rm video4