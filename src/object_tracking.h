#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <PerFoRoControl/SelectTarget.h>

using namespace cv;
using namespace std;

static const std::string OPENCV_WINDOW = "Image Window";
static void onMouse(int event, int x, int y, int, void* );

class ObjectTracking
{
public:
	ObjectTracking();

	~ObjectTracking() {cv::destroyWindow(OPENCV_WINDOW);} 

	void 	SelectObject(int event, int x, int y);

protected:
	
	/**
	* NodeHandle is the main access point to communications with the ROS system.
	* The first NodeHandle constructed will fully initialize this node, and the last
	* NodeHandle destructed will close down the node.
	*/

	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Publisher image_pub_;
	ros::Subscriber target_sub_;

	Mat frame;
	float maxDistance, distPrevCurrent;
	int dilation_size, erosion_size;
	Mat elemDilate, elemErode;
	Mat structure_elem;
	bool IMSHOW;
	int trackObject;
	Rect selection;
	Scalar mColorRadius;
	Scalar mLowerBound;
	Scalar mUpperBound;
	Point selectCentroid, selectCenter, origin;
	int rectOffset;
	double minDistThresh;
	double distThresh; 
	int missCount;
	KalmanFilter KF;
	Point kalmanEstimatePt;
	bool selectObject;
	int navX, navY;

	void 	drawArrow(Mat image, Point p, Point q, Scalar color, int arrowMagnitude, int thickness, int line_type, int shift);
	void	ImageCallback(const sensor_msgs::ImageConstPtr& msg);
	void 	SelectTargetCallback(const PerFoRoControl::SelectTarget msg);
	void	initTracker();
	Point	kalmanTracker(Point centroid);
};

namespace ot
{
    ObjectTracking *OT = NULL;
}
