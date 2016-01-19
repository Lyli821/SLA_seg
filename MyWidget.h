#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

#include <cv.h>
#include <highgui.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <vector>
#include <list>
#include <qdir.h>
#include <qstring.h>

using namespace std;
using namespace cv;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef vector<Point_2> Points;

typedef struct tagEdge{
	double xi;
	double dx;
	//int ymax;
	double ymax;
	bool live;
	bool operator < (const tagEdge& A) const{
		return xi < A.xi;
	}
	void print(){
		cout <<"("<<xi<<","<<dx<<","<<ymax<<")->";
	}
} EDGE;
static bool IsEdgeOutOfActive(EDGE e, /*int*/double y){
	  return (e.ymax < y + 1);
}

class Line{
public:
	Line(){
		this->p = Vec3f(0, 0, 0);
		this->q = Vec3f(0, 0, 0);
	}

	Line(Vec3f p, Vec3f q){
		this->p = p;
		this->q = q;
	}

	Line(const Line &line){
		p = line.p;
		q = line.q;
	}

	Line &operator=(Line &line){
		this->p = line.p;
		this->q = line.q;

		return *this;
	}

public:
	Vec3f p;
	Vec3f q;
};

class face{
public:
	face(Vec3f n, Vec3f p[3]){
		this->n = n;
		this->p[0] = p[0];
		this->p[1] = p[1];
		this->p[2] = p[2];
	}

	float min_x(){
		float x = p[0][0];
		x = x < p[1][0] ? x : p[1][0];
		x = x < p[2][0] ? x : p[2][0];

		return x;
	}

	float max_x(){
		float x = p[0][0];
		x = x > p[1][0] ? x : p[1][0];
		x = x > p[2][0] ? x : p[2][0];

		return x;
	}


	float min_y(){
		float y = p[0][1];
		y = y < p[1][1] ? y : p[1][1];
		y = y < p[2][1] ? y : p[2][1];

		return y;
	}

	float max_y(){
		float y = p[0][1];
		y = y > p[1][1] ? y : p[1][1];
		y = y > p[2][1] ? y : p[2][1];

		return y;
	}

	float min_z(){
		float z = p[0][2];
		z = z < p[1][2] ? z : p[1][2];
		z = z < p[2][2] ? z : p[2][2];

		return z;
	}

	float max_z(){
		float z = p[0][2];
		z = z > p[1][2] ? z : p[1][2];
		z = z > p[2][2] ? z : p[2][2];

		return z;
	}

	

	Vec3f n;
	Vec3f p[3];
};

class MyWidget: public QGLWidget{
	Q_OBJECT

public:
	MyWidget(QWidget *parent = 0);
	~MyWidget();

public:  
	void initializeGL();  
	void resizeGL(int w, int h);  
	void paintGL();

public:
	//鼠标事件
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

public:
	void readModel(QString &filePath);
	void body_scaleChanged(float value);
	void body_rxChanged(float value);
	void body_ryChanged(float value);
	void body_rzChanged(float value);
	void body_mxChanged(float value);
	void body_myChanged(float value);
	void body_mzChanged(float value);
	void body_parameter_chanegd();
	void conversion_of_coordinates(Vec3f &from, Vec3f &to, float scale, float rx, float ry, float rz);
	float min_y();
	float max_y();
	float min_x();
	float max_x();
	float min_z();
	float max_z();

	//cv::Rect getRect();
	void getGFloor(QString folder);
	void slice(float y, bool fill, QString folder);
	

	void clear(std::vector<face *>& faces);
	void initialize();
	void drawCoordinates();

	//计算平面y 与三角面片的交线
	bool CalPlaneLineIntersectPoint(Vec3f p[3], float y, std::vector<Vec3f> &result);
	void wcl_to_screen(double cx, double cy, double cz, double &sx, double &sy);

	//平面分割工具函数
	int discrete(vector<Line *> lines, vector<Points> &points_set);
	void rotate(Points original, Points &rotated, Points convexhull, int index/*index of the starting point of the base edge*/, double &angle);
	void rotate(Points original, Points &rotated, double angle);
	void buildNet(vector<list<EDGE>> &slNet, Points polygon, int ymin);
	void buildAet(vector<list<EDGE>> &slAet, vector<list<EDGE>> slNet, int ymin);
	void buildXs(vector<vector<double>> &slXs, vector<list<EDGE>> slAet, int ymin);
	Mat draw(Points polygon, vector<Points> polygon_in, QString folder, bool fill, double xmin, double xmax, int ymin, int ymax);
	void drawSeg(vector<Mat> &mats, Mat mat0, Points centers_r, int sum_cur, QString folder, double xmin, int ymax);
	int segment(Points &centers_r, vector<vector<double>> slXs, int ymin);
	
	double cross(Point_2 pi,Point_2 pj,Point_2 pk);
	int InPolygon(const Points arr,const Point_2 &p,int on_edge=1);
	void getBound(Points &points_r, double &xmin, double &xmax, int &ymin, int &ymax);
	void buildAll(vector<vector<double>> &slXs, Points polygon, int ymin, int num);
	void mergeXs(vector<vector<double>> &slXs, vector<vector<double>> slXs2);


private:  
	std::vector<face *> faces;			//三角形面片，原始数据
	std::vector<face *> faces_clone;	//三角形面片，显示
	std::vector<Line *> lines;			//显示切割线

	//鼠标事件
	//场景变换参数
	float m_xRotation, m_yRotation, m_zRotation;
	float m_xTranslation, m_yTranslation, m_zTranslation;
	float m_Scaling;
	float m_x, m_y, m_z;
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];

	//鼠标点击的上一个点和当前点
	QPointF lastPoint;
	QPointF curPoint;

	//物体变换参数
	float body_scale;			//物体大小变换
	float body_rx, body_ry, body_rz;			//物体旋转变换
	float body_mx, body_my, body_mz;			//物体位移
	

	//坐标系常量
	static const int SEMI_LENGTH_SIDE = 17;
	static const int MM_PER_PIXEL = 4;
	static const int MM_PER_PIXEL2 = 32;
};

#endif

