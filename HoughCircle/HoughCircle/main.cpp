#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	string filename = "smarties.png";
	// Loads an image
	Mat src = imread(filename, IMREAD_COLOR);
	Mat srcCopy = src.clone();

	// Check if image is loaded fine
	if (src.empty()) {
		printf(" Error opening image\n");
		return -1;
	}

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	medianBlur(gray, gray, 5);

	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
		gray.rows / 16,  // change this value to detect circles with different distances to each other
		100, 30, 1, 30 // change the last two parameters
   // (min_radius & max_radius) to detect larger circles
	);

	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		// circle center
		circle(src, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(src, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
	}

	imshow("Original Image", srcCopy);
	imshow("detected circles", src);
	waitKey();
	return 0;
}