#include <SFML/Graphics.hpp>
#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#define X1 -2.1
#define X2 0.6
#define Y1 -1.2
#define Y2 1.2
#define ZOOM 300
#define X_WINDOW (X2 - X1) * ZOOM
#define Y_WINDOW (Y2 - Y1) * ZOOM
#define COLOR_DIVIDER 100
#define MAX_ITERATIONS 600

using namespace std;

int module(double x, double y){

	return sqrt( x * x + y * y );
}

int main(){

	sf::Image image;
	image.create(X_WINDOW, Y_WINDOW, sf::Color::White);

	for (int x = 0; x < X_WINDOW ; ++x) {
		for (int y = 0; y < Y_WINDOW ; ++y) {
		
			complex<double> c ( ((double) x / (double) ZOOM) + X1 , - Y1 - ( (double) y / (double) ZOOM) );
			complex<double> z = 0;
			double i = 0;

			while( module( real(z), imag(z) ) < 2 && i < MAX_ITERATIONS ){
				z = z*z + c;
				i++;
			}
			
			if(i == MAX_ITERATIONS){
				image.setPixel(x,y,sf::Color::Black );
			}
			else{
				int blue_color = 50 + 255 * i / COLOR_DIVIDER;
				int green_color = 15 + 255 * i / COLOR_DIVIDER;
				int red_color = 10 - 255 * i / COLOR_DIVIDER;

				if( blue_color > 255 ){
					blue_color = 255;
				}
				if( green_color > 255 ){
					green_color = 255;
				}
				if( red_color < 0 ){
					red_color = 0;
				}
				
				image.setPixel(x,y,sf::Color(red_color,green_color, blue_color) );
			}	
		}
	}
	
	image.saveToFile("Mandelbrot.png");
   	system("xdg-open Mandelbrot.png");
}