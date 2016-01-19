#include "MyWidget.h"  
#include <QFile>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <math.h> 
#include <qdir.h>
#include <qstring.h>

#include <GL/glut.h>
#include <QPushButton>

#include<cmath>  
#include<cstring>  
#include<cstdio>  
#include<cstdlib>  
#include<time.h> 

#include "Calculator.h"
//opencv
#define PI 3.14159265358979323846
using namespace std;
using namespace cv;

static const double interval = 1;
static const double block_width = 17;	//Suppose the block's block_width is 2 and block_height is 1
static const double block_height = 17;
bool debug = 0;
const int offset=1000;  
const double eps=1e-8;

MyWidget::MyWidget(QWidget *parent /* = 0 */)  
	: QGLWidget(parent)  
{  
	initialize();
}  

MyWidget::~MyWidget()  
{  

}  

void MyWidget::initializeGL()  
{  
	glShadeModel(GL_SMOOTH);  

	glClearColor(1.0,1.0,1.0,1.0);  
	glClearDepth(1.0);  

	glEnable(GL_DEPTH_TEST);  

	glDepthFunc(GL_LEQUAL);  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); 

	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_ambient[] = {0.1f, 0.1f, 0.1f, 1.1f};
	GLfloat sun_light_diffuse[] = {0.7f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_specular[] = {0.5 , 0.0 , 0.0 , 0.5};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

	GLfloat sun_mat_ambient[] = {0.5f, 0.4f, 0.1f, 1.0f};
	GLfloat sun_mat_diffuse[] = {0.6f, 0.2f, 0.2f, 1.0f};
	GLfloat sun_mat_specular[] = {0.2f, 0.3f, 0.4f, 1.0f};
	GLfloat sun_mat_emission[] = {1.0f, 0.5f, 0.5f, 1.0f};
	GLfloat sun_mat_shininess = 0.5f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
	glutSolidSphere(2.0, 40, 32);
}  

void MyWidget::resizeGL(int w, int h)  
{  
	glViewport(0,0,(GLint)width(),(GLint)height());  

	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  

	gluPerspective(45.0,(GLfloat)width() / (GLfloat)height(),0.1,1000.0);  
	glMatrixMode(GL_MODELVIEW);  

	glLoadIdentity();  
}  

void MyWidget::paintGL()  
{  

	//第一版
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glLoadIdentity();
	glTranslatef(m_xTranslation, m_yTranslation, m_zTranslation);
	glTranslatef(m_x, m_y, m_z);
	glRotatef(m_xRotation,1.0f,0.0f,0.0f);
	glRotatef(m_yRotation,0.0f,1.0f,0.0f);
	glRotatef(m_zRotation,0.0f,0.0f,1.0f);
	glScalef(m_Scaling, m_Scaling, m_Scaling);
	glTranslatef(-m_x, -m_y, -m_z);

	glColor3f(1.0, 0.5, 0.5);

	for(int i = 0; i < faces.size(); i ++){
	glBegin(GL_TRIANGLES);
	glVertex3f(faces[i]->p[0][0], faces[i]->p[0][1],faces[i]->p[0][2]);
	glVertex3f(faces[i]->p[1][0], faces[i]->p[1][1],faces[i]->p[1][2]);
	glVertex3f(faces[i]->p[2][0], faces[i]->p[2][1],faces[i]->p[2][2]);
	glEnd();  
	}

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);*/


	//第二版
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glLoadIdentity();
	glTranslatef(m_xTranslation, m_yTranslation, m_zTranslation);
	glRotatef(m_xRotation,1.0f,0.0f,0.0f);
	glRotatef(m_yRotation,0.0f,1.0f,0.0f);
	glRotatef(m_zRotation,0.0f,0.0f,1.0f);
	glScalef(m_Scaling, m_Scaling, m_Scaling);

	//坐标系
	drawCoordinates();

	//物体
	glEnable(GL_LIGHT0);   //支持光源GL_LIGHT0---GL_LIGHT7
	glEnable(GL_LIGHTING);
	for(int i = 0; i < faces.size(); i ++){
		glBegin(GL_TRIANGLES);
		glVertex3f(faces_clone[i]->p[0][0], faces_clone[i]->p[0][1],faces_clone[i]->p[0][2]);
		glVertex3f(faces_clone[i]->p[1][0], faces_clone[i]->p[1][1],faces_clone[i]->p[1][2]);
		glVertex3f(faces_clone[i]->p[2][0], faces_clone[i]->p[2][1],faces_clone[i]->p[2][2]);
		glEnd();
	}
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glColor3f(0.0, 0.0, 0.0);

	glPushAttrib(GL_LINE_BIT);
	double gra, range[2];
	glGetDoublev(GL_LINE_WIDTH_GRANULARITY, &gra);
	glGetDoublev(GL_LINE_WIDTH_RANGE, range);
	glLineWidth(range[0] + 10 * gra);
	//x轴1
	for(int i = 0; i < lines.size(); i ++){
		glBegin(GL_LINES);
		glVertex3f(lines[i]->p[0], lines[i]->p[1], lines[i]->p[2]);
		glVertex3f(lines[i]->q[0], lines[i]->q[1], lines[i]->q[2]);
		glEnd();
	}
	glPopAttrib();


	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
} 

void MyWidget::mousePressEvent(QMouseEvent *event){
	lastPoint = event->posF();
}

void MyWidget::mouseMoveEvent(QMouseEvent *event){
	curPoint = event->posF();

	double sx,sy;
	double cx,cy;
	wcl_to_screen(0.0,0.0,0.0,sx,sy);
	wcl_to_screen(0.0,1.0,0.0,cx,cy);

	m_xRotation -= (float)(lastPoint.y()- curPoint.y()) / 2;
	m_yRotation = cy >= sy ? m_yRotation + (float)(lastPoint.x() - curPoint.x()) / 2 : m_yRotation - (float)(lastPoint.x() - curPoint.x()) / 2;

	lastPoint = curPoint;
	update();
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event){
	curPoint = event->posF();
	lastPoint = curPoint;
}

void MyWidget::wheelEvent(QWheelEvent *event){
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;
	if (numSteps > 0)
	{
		m_Scaling *= 1.25;
		if (m_Scaling < 0.00001) 
			m_Scaling = 0.00001f;
	}
	else 
	{
		m_Scaling *= 0.85;
		if (m_Scaling < 0.00001) 
			m_Scaling = 0.00001f;
	}
	update();
}

void MyWidget::readModel(QString &filePath){
	//清空上个模型
	clear(faces);
	clear(faces_clone);

	float min_x = 100000, min_y = 100000, min_z = 1000000;
	float max_x = -100000, max_y = -100000, max_z = -1000000;
	//read
	QFile file(filePath);
	file.open(QIODevice::ReadOnly);


	char head[80];					//文件头
	int unTriangles = 0;			//三角面片个数
	float x, y, z;					//法线矢量，坐标点
	char unusedByte;				//无用数据

	//读取文件头
	file.read((char*)&head, sizeof(head));
	//printf("%s\n", head);

	//面片个数
	file.read((char*)&unTriangles, sizeof(unTriangles));
	//printf("face number = %d\n", unTriangles);

	if(unTriangles == 0){
		file.close();
		return;
	}
	
	//读取面片信息
	for(int i = 0; i < unTriangles; i ++){
		Vec3f nx;
		Vec3f p[3];

		//printf("\n");
		for (int j = 0; j < 4; j ++){
			file.read((char*)&x, sizeof(x));
			file.read((char*)&y, sizeof(y));
			file.read((char*)&z, sizeof(z));
			//printf("x = %f, y = %f, z = %f\n", x, y, z);

			if(j == 0){
				nx = Vec3f(x, y, z);
			} else {
				p[j - 1] = Vec3f(x, y, z);

				min_x = min_x < x ? min_x : x;
				min_y = min_y < y ? min_y : y;
				min_z = min_z < z ? min_z : z;

				max_x = max_x > x ? max_x : x;
				max_y = max_y > y ? max_y : y;
				max_z = max_z > z ? max_z : z;
			}
		}
		//无用数据位
		file.read((char*)&unusedByte, sizeof(unusedByte));
		file.read((char*)&unusedByte, sizeof(unusedByte));

		//存储
		faces.push_back(new face(nx, p));
	}
	file.close();

	m_x = (min_x + max_x) / 2;
	m_y = (min_y + max_y) / 2;
	m_z = (min_z + max_z) / 2;
	
	//数据更新和处理
	for(int i = 0; i < faces.size(); i ++){
		Vec3f vec3f(m_x, m_y, m_z);
		faces[i]->p[0] = faces[i]->p[0] - vec3f;
		faces[i]->p[1] = faces[i]->p[1] - vec3f;
		faces[i]->p[2] = faces[i]->p[2] - vec3f;
	}
	min_x -= m_x; max_x -= m_x;
	min_y -= m_y; max_y -= m_y;
	min_z -= m_z; max_z -= m_z;

	for(int i = 0; i < faces.size(); i ++){
		Vec3f vec3f(0, SEMI_LENGTH_SIDE + min_y, 0);

		Vec3f p[3];
		p[0] = faces[i]->p[0] - vec3f;
		p[1] = faces[i]->p[1] - vec3f;
		p[2] = faces[i]->p[2] - vec3f;

		faces_clone.push_back(new face(faces[i]->n, p));
	}

	update();
}

void MyWidget::clear(vector<face *> &faces){
	for(int i = 0; i < faces.size(); i ++){
		delete faces[i];
	}
	faces.clear();
}

void MyWidget::body_scaleChanged(float value){
	body_scale = value;
	body_parameter_chanegd();
}

void MyWidget::body_rxChanged(float value){
	body_rx = value;
	body_parameter_chanegd();
}

void MyWidget::body_ryChanged(float value){
	body_ry = value;
	body_parameter_chanegd();
}

void MyWidget::body_rzChanged(float value){
	body_rz = value;
	body_parameter_chanegd();
}

void MyWidget::body_mxChanged(float value){
	body_mx = value;
	body_parameter_chanegd();
}

void MyWidget::body_myChanged(float value){
	body_my = value;
	body_parameter_chanegd();
}

void MyWidget::body_mzChanged(float value){
	body_mz = value;
	body_parameter_chanegd();
}

void MyWidget::body_parameter_chanegd(){
	clear(faces_clone);

	float min_y = 10000;
	for(int i = 0; i < faces.size(); i ++){
		Vec3f p[3];
		for(int j = 0; j < 3; j ++){
			conversion_of_coordinates(faces[i]->p[j], p[j], body_scale, body_rx, body_ry, body_rz);
			min_y = min_y < p[j][1] ? min_y : p[j][1];
		}
		faces_clone.push_back(new face(faces[i]->n, p));
	}

	printf("min_y = %f, body_my = %f\n", min_y, body_my);

	Vec3f move_vec3f = (body_mx, body_my, body_mz);
	for(int i = 0; i < faces_clone.size(); i ++){
		Vec3f vec3f(body_mx, body_my - min_y - SEMI_LENGTH_SIDE, body_mz);

		faces_clone[i]->p[0] = faces_clone[i]->p[0] + vec3f;
		faces_clone[i]->p[1] = faces_clone[i]->p[1] + vec3f;
		faces_clone[i]->p[2] = faces_clone[i]->p[2] + vec3f;
	}
	update();
}

void MyWidget::conversion_of_coordinates(Vec3f &from, Vec3f &to, float scale, float rx, float ry, float rz){
	float sinx = sin(rx / 180 * PI);
	float cosx = cos(rx / 180 * PI);
	float siny = sin(ry / 180 * PI);
	float cosy = cos(ry / 180 * PI);
	float sinz = sin(rz / 180 * PI);
	float cosz = cos(rz / 180 * PI);

	float x = from[0] * scale, y = from[1] * scale, z = from[2] * scale;

	to[0] = x * cosy * cosz + y * (sinx * siny * cosz - cosx * sinz) + z * (cosx * siny * cosz + sinx * sinz);
	to[1] = x * cosy * sinz + y * (sinx * siny * sinz + cosx * cosz) + z * (cosx * siny * sinz - sinx * cosz);
	to[2] = -x * siny + y * sinx * cosy + z * cosx * cosy;
}

void MyWidget::getGFloor(QString folder){
	//Rect rect = getRect();
	QDir dir;
	Calculator::removeDirWithContent(folder);
	dir.mkdir(folder);
	QString datafile = folder + QString("/") + QString("data.txt");
	ofstream fout(datafile.toStdString().c_str());

	int num_x = ceil((max_x()-min_x())/block_width);
	int num_z = ceil((max_z()-min_z())/block_height);
	int cur = 0;
	for(int i = 0; i < num_x; i++){
		for(int j = 0; j < num_z; j++){
			Mat mat(ceil((block_height)*MM_PER_PIXEL2), ceil((block_width)*MM_PER_PIXEL2), CV_8UC1, Scalar(255));
			QString imagefile = folder + QString("/%1").arg(cur) + QString(".jpg");
			imwrite(imagefile.toStdString(), mat);
			cur++;
			fout << "c " << min_x()+(i+0.5)*block_width << " " << min_z()+(j+0.5)*block_height << endl;
		}
	}
	fout << "#";
	fout.close();
	//Mat GFloor(2 * SEMI_LENGTH_SIDE * MM_PER_PIXEL, 2 * SEMI_LENGTH_SIDE * MM_PER_PIXEL, CV_8UC1, Scalar(255));

	//Mat roi = GFloor(rect);
	//Mat mat(rect.height, rect.width, CV_8UC1, Scalar(255));
	//mat.copyTo(roi);

	//return GFloor;
}

void MyWidget::slice(float y, bool fill, QString folder){
	if(y < -50 ){
		printf("out of range!\n");
	}

	for(int i = 0; i < lines.size(); i ++){
		delete lines[i];
	}
	lines.clear();

	for(int i = 0; i < faces_clone.size(); i ++){
		face &f = *faces_clone[i];

		if(f.min_y() > y || f.max_y() < y){
			continue;
		}

		vector<Vec3f> result;
		if(CalPlaneLineIntersectPoint(faces_clone[i]->p, y, result)){
			lines.push_back(new Line(result[0], result[1]));
		}
	}
	
	update();
	QDir dir;
	Calculator::removeDirWithContent(folder);
	dir.mkdir(folder);
	QString datafile = folder + QString("/") + QString("data.txt");
	ofstream fout(datafile.toStdString().c_str());
	vector<int> sums, ymin_set, ymax_set;
	vector<double> xmin_set, xmax_set, angles;
	vector<Points> points_set, points_r_set, centers_r_set, centers_set;
	vector<Mat> mats;

	double xmin, xmax;
	int ymin, ymax;
	vector<vector<int>> contain;
	vector<Points> points_in, points_in_r;
	vector<bool> valid;
	vector<vector<Points>> points_in_r_set;

	int num = discrete(lines, points_set);
	//fout << num << endl;
	for(unsigned int i = 0; i < num; i++){
		vector<int> c;
		c.clear();
		contain.push_back(c);
		valid.push_back(true);
	}
	bool in;
	for(unsigned int i = 0; i < num; i++){
		for(unsigned int j = 0; j < num && j != i; j++){
			in = true;
			for(unsigned int k = 0; k < points_set[i].size(); k++){
				if(!InPolygon(points_set[j],points_set[i][k])){
					in = false;
					break;
				}
			}
			if(in){
				if(debug)
					cout << i << " in " << j << endl;
				contain[j].push_back(i);
			}
		}
	}
	Points points, convexhull, points_r, centers_r, centers;
	double angle = 0;
	int sum_cur = 0;
	for(unsigned int m = 0; m < num; m++){
		if(!valid[m]){
			continue;
		}
		if(debug){
			cout << "-------------------------------------------------------------------------" << endl;
			cout << m << ": " << endl;
			cout << "-------------------------------------------------------------------------" << endl;
		}
		points.clear();
	    points = points_set[m];

		points_in.clear();
		if(contain[m].size() > 0){
			for(unsigned int i = 0; i < contain[m].size(); i++){
				valid[contain[m][i]] = false;
				points_in.push_back(points_set[contain[m][i]]);
			}
		}

	    convexhull.clear();
		sums.clear(); ymin_set.clear(); ymax_set.clear(); xmin_set.clear(); xmax_set.clear(); angles.clear();
	    points_r_set.clear(); centers_r_set.clear(); centers_set.clear(); mats.clear();
		points_in_r_set.clear();
	    CGAL::convex_hull_2( points.begin(), points.end(), std::back_inserter(convexhull) );
	    for(unsigned int index = 0; index < convexhull.size(); index++){
			rotate(points, points_r, convexhull, index, angle);
			angles.push_back(angle);

			Points tmp; points_in_r.clear();
			if(points_in.size() > 0){
				for(unsigned int i = 0; i < points_in.size(); i++){
					rotate(points_in[i], tmp, angle);
					getBound(tmp, xmin, xmax, ymin, ymax);
					points_in_r.push_back(tmp);
				}
			}
			points_in_r_set.push_back(points_in_r);

		    getBound(points_r, xmin, xmax, ymin, ymax);
		    points_r_set.push_back(points_r);
		    ymin_set.push_back(ymin); ymax_set.push_back(ymax);
		    xmin_set.push_back(xmin); xmax_set.push_back(xmax);
		    int num1 = ceil((ymax-ymin)/interval)+1;
			vector<vector<double>> slXs(num1-1);
			buildAll(slXs, points_r, ymin, num1);

			if(points_in_r.size() > 0){
				for(unsigned int i = 0; i < points_in_r.size(); i++){
					vector<vector<double>> tmp2(num1-1);
					buildAll(tmp2, points_in_r[i], ymin, num1);
					mergeXs(slXs, tmp2);//
				}
			}

		    int sum = segment(centers_r, slXs, ymin);
		    sums.push_back(sum); centers_r_set.push_back(centers_r);
		    rotate(centers_r, centers, -angle);
			centers_set.push_back(centers);
			if(debug){
				cout << "---------------------------------------------------" << endl;
			}
		}
	    int sum_min = sums[0]; int ideal = 0;
	    for(unsigned int index = 1; index < sums.size(); index++){
		    if(sums[index] < sum_min){
				sum_min = sums[index];
			    ideal = index;
		    }
		}
	    xmin = xmin_set[ideal]; xmax = xmax_set[ideal]; ymin = ymin_set[ideal]; ymax = ymax_set[ideal];
	    Mat mat0 = draw(points_r_set[ideal], points_in_r_set[ideal], folder, fill, xmin, xmax, ymin, ymax);
	    drawSeg(mats, mat0, centers_r_set[ideal], sum_cur, folder, xmin, ymax);
		sum_cur += sum_min;
		fout << "a " << angles[ideal] << endl;
		for(unsigned int index = 0; index < centers_set[ideal].size(); index++){
			fout << "c " << centers_set[ideal][index].x() << " " << centers_set[ideal][index].y() << endl;
		}
	}
	fout << "#";
	fout.close();
}

float MyWidget::min_y(){
	if(faces_clone.size() == 0)
		return 0;

	float min_y = SEMI_LENGTH_SIDE;
	for(int i = 0; i < faces_clone.size(); i++){
		min_y = min_y < faces_clone[i]->min_y() ? min_y : faces_clone[i]->min_y();
	}

	min_y = min_y >= -SEMI_LENGTH_SIDE ? min_y : -SEMI_LENGTH_SIDE;

	return min_y;
}
float MyWidget::max_y(){
	if(faces_clone.size() == 0)
		return 0;

	float max_y = -SEMI_LENGTH_SIDE;
	for(int i = 0; i < faces_clone.size(); i ++){
		max_y = max_y > faces_clone[i]->max_y() ? max_y : faces_clone[i]->max_y();
	}

	return max_y;
}
float MyWidget::min_x(){
	if(faces_clone.size() == 0)
		return 0;

	float min_x = SEMI_LENGTH_SIDE;
	for(int i = 0; i < faces_clone.size(); i++){
		min_x = min_x < faces_clone[i]->min_x() ? min_x : faces_clone[i]->min_x();
	}

	return min_x;
}
float MyWidget::max_x(){
	if(faces_clone.size() == 0)
		return 0;

	float max_x = -SEMI_LENGTH_SIDE;
	for(int i = 0; i < faces_clone.size(); i ++){
		max_x = max_x > faces_clone[i]->max_x() ? max_x : faces_clone[i]->max_x();
	}

	return max_x;
}
float MyWidget::min_z(){
	if(faces_clone.size() == 0)
		return 0;

	float min_z = SEMI_LENGTH_SIDE;
	for(int i = 0; i < faces_clone.size(); i++){
		min_z = min_z < faces_clone[i]->min_z() ? min_z : faces_clone[i]->min_z();
	}

	return min_z;
}
float MyWidget::max_z(){
	if(faces_clone.size() == 0)
		return 0;

	float max_z = -SEMI_LENGTH_SIDE;
	for(int i = 0; i < faces_clone.size(); i ++){
		max_z = max_z > faces_clone[i]->max_z() ? max_z : faces_clone[i]->max_z();
	}

	return max_z;
}
/*
Rect MyWidget::getRect(){//仅用在getGFloor
	if(faces_clone.size() == 0)
		return Rect(0, 0, 0, 0);

	float max_x = -SEMI_LENGTH_SIDE;
	float max_z = -SEMI_LENGTH_SIDE;
	float min_x = SEMI_LENGTH_SIDE;
	float min_z = SEMI_LENGTH_SIDE;

	for(int i = 0; i < faces_clone.size(); i ++){
		max_x = max_x > faces_clone[i]->max_x() ? max_x : faces_clone[i]->max_x();
		max_z = max_z > faces_clone[i]->max_z() ? max_z : faces_clone[i]->max_z();

		min_x = min_x < faces_clone[i]->min_x() ? min_x : faces_clone[i]->min_x();
		min_z = min_z < faces_clone[i]->min_z() ? min_z : faces_clone[i]->min_z();
	}

	Rect rect((min_x + SEMI_LENGTH_SIDE) * MM_PER_PIXEL, (min_z + SEMI_LENGTH_SIDE) * MM_PER_PIXEL, (max_x - min_x) * MM_PER_PIXEL, (max_z - min_z) * MM_PER_PIXEL);
	return rect;
}
*/
void MyWidget::initialize(){
	clear(faces);
	clear(faces_clone);
	m_xTranslation = 0.0f;
	m_yTranslation = 0.0f;
	m_zTranslation = -70.0f;//z-axis perpendicular to the scene

	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
	m_zRotation = 0.0f;

	m_Scaling = 1.0f;

	//物体中心点
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;

	//物体参数,大小和旋转角度
	body_scale = 1.0;
	body_rx = 0;
	body_ry = 0;
	body_rz = 0;
	body_mx = 0;
	body_my = 0;
	body_mz = 0;
}

void MyWidget::drawCoordinates(){
	glColor3f(0.3, 0.3, 0.3);

	//x轴1
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glEnd();
	//x轴2
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glEnd();
	//x轴3
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();
	//x轴4
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();

	//y轴1
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(-SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glEnd();
	//y轴2
	glBegin(GL_LINES);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glEnd();
	//y轴3
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glVertex3f(-SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();
	//y轴4
	glBegin(GL_LINES);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();

	//z轴1
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();
	//z轴2
	glBegin(GL_LINES);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();
	//z轴3
	glBegin(GL_LINES);
	glVertex3f(-SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(-SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();
	//z轴4
	glBegin(GL_LINES);
	glVertex3f(SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();


	//画底面
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE);
	glVertex3f(SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glVertex3f(-SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, SEMI_LENGTH_SIDE);
	glEnd();


	////画坐标方向
	//glColor3f(1.0, 0, 0);
	////x正方向
	//glBegin(GL_LINES);
	//glVertex3f(0, -SEMI_LENGTH_SIDE, 0);
	//glVertex3f(1.2 * SEMI_LENGTH_SIDE, -SEMI_LENGTH_SIDE, 0);
	//glEnd();
	////y正方向
	//glBegin(GL_LINES);
	//glVertex3f(0, -SEMI_LENGTH_SIDE, 0);
	//glVertex3f(0, 1.2 * SEMI_LENGTH_SIDE, 0);
	//glEnd();
	////z正方向
	//glBegin(GL_LINES);
	//glVertex3f(0, -SEMI_LENGTH_SIDE, 0);
	//glVertex3f(0, -SEMI_LENGTH_SIDE, 1.2 * SEMI_LENGTH_SIDE);
	//glEnd();


}

bool MyWidget::CalPlaneLineIntersectPoint(Vec3f p[3], float y, std::vector<Vec3f> &result){
	//初始化
	result.clear();

	vector<Vec3f> sp;
	vector<Vec3f> mp;
	vector<Vec3f> bp;

	for(int i = 0; i < 3; i ++){
		if(p[i][1] < y){
			sp.push_back(p[i]);
		} else if(p[i][1] > y){
			bp.push_back(p[i]);
		} else {
			mp.push_back(p[i]);
		}
	}

	if(mp.size() == 0){

		if(sp.size() == 0 || bp.size() == 0){
			//printf("wrong face!\n");
			return false;
		}

		if(sp.size() == 1){
			float x = sp[0][0] + (y - sp[0][1]) * (bp[0][0] - sp[0][0]) / (bp[0][1] - sp[0][1]);
			float z = sp[0][2] + (y - sp[0][1]) * (bp[0][2] - sp[0][2]) / (bp[0][1] - sp[0][1]);
			result.push_back(Vec3f(x, y, z));

			x = sp[0][0] + (y - sp[0][1]) * (bp[1][0] - sp[0][0]) / (bp[1][1] - sp[0][1]);
			z = sp[0][2] + (y - sp[0][1]) * (bp[1][2] - sp[0][2]) / (bp[1][1] - sp[0][1]);
			result.push_back(Vec3f(x, y, z));
		} else {
			float x = sp[0][0] + (y - sp[0][1]) * (bp[0][0] - sp[0][0]) / (bp[0][1] - sp[0][1]);
			float z = sp[0][2] + (y - sp[0][1]) * (bp[0][2] - sp[0][2]) / (bp[0][1] - sp[0][1]);
			result.push_back(Vec3f(x, y, z));

			x = sp[1][0] + (y - sp[1][1]) * (bp[0][0] - sp[1][0]) / (bp[0][1] - sp[1][1]);
			z = sp[1][2] + (y - sp[1][1]) * (bp[0][2] - sp[1][2]) / (bp[0][1] - sp[1][1]);
			result.push_back(Vec3f(x, y, z));
		}
	} else if(mp.size() == 1){
		if(sp.size() != 1 && bp.size() != 1){
			//printf("wrong face!\n");
			return false;
		}

		result.push_back(mp[0]);

		float x = sp[0][0] + (y - sp[0][1]) * (bp[0][0] - sp[0][0]) / (bp[0][1] - sp[0][1]);
		float z = sp[0][2] + (y - sp[0][1]) * (bp[0][2] - sp[0][2]) / (bp[0][1] - sp[0][1]);
		result.push_back(Vec3f(x, y, z));

	} else if(mp.size() == 2){
		result.push_back(mp[0]);
		result.push_back(mp[1]);
	} else {
		//printf("wrong face!\n");
		return false;
	}

	return true;
}

void MyWidget::wcl_to_screen(double cx, double cy, double cz, double &sx, double &sy){
	GLdouble winx, winy, winz;
	gluProject(cx, cy, cz, modelMatrix, projMatrix, viewport, &winx, &winy, &winz); 

	sx = winx;
	sy = height() - winy;
}

int MyWidget::discrete(vector<Line *> lines, vector<Points> &points_set){
	Points tmp;
	while(lines.size() != 0){
		if(tmp.size() == 0){
			tmp.push_back(Point_2(lines[0]->p[0],lines[0]->p[2]));
			tmp.push_back(Point_2(lines[0]->q[0],lines[0]->q[2]));
			lines.erase(lines.begin());
		}else{
			Point_2 tail = tmp[tmp.size()-1];
			Point_2 head = tmp[0];
			Point_2 add;
			for(vector<Line *>::iterator cur = lines.begin(); cur != lines.end(); cur++){
				if((*cur)->p[0] == tail.x() && (*cur)->p[2] == tail.y()){
					add = Point_2((*cur)->q[0],(*cur)->q[2]);
					if(add == head){
						points_set.push_back(tmp);
						tmp.clear();
					}else{
						tmp.push_back(add);
					}
					lines.erase(cur);
					break;
				}else if((*cur)->q[0] == tail.x() && (*cur)->q[2] == tail.y()){
					add = Point_2((*cur)->p[0],(*cur)->p[2]);
					if(add == head){
						points_set.push_back(tmp);
						tmp.clear();
					}else{
						tmp.push_back(add);
					}
					lines.erase(cur);
					break;
				}
			}
		}
	}
	return points_set.size();
}

void MyWidget::rotate(Points original, Points &rotated, Points convexhull, int index/*index of the starting point of the base edge*/, double &angle){
	rotated.clear();
	Point_2 a,b;
	a = convexhull[index];
	b = convexhull[(index+1)%convexhull.size()];
	if(a.x() == b.x())
		angle = PI / 2;
	else
		angle = atan((a.y()-b.y())/(a.x()-b.x()));
	for(unsigned int i = 0; i < original.size(); i++){
		rotated.push_back(Point_2(original[i].x()*cos(angle)+original[i].y()*sin(angle),original[i].y()*cos(angle)-original[i].x()*sin(angle)));
	}
}
void MyWidget::rotate(Points original, Points &rotated, double angle){
	rotated.clear();
	for(unsigned int i = 0; i < original.size(); i++){
		rotated.push_back(Point_2(original[i].x()*cos(angle)+original[i].y()*sin(angle),original[i].y()*cos(angle)-original[i].x()*sin(angle)));
	}
}

void MyWidget::buildNet(vector<list<EDGE>> &slNet, Points polygon, int ymin){//构建新边表slNet
	EDGE e;
	vector<Point_2>::iterator ps, pe, pee, pss;
	for(ps = polygon.begin(); ps != polygon.end(); ps++){
		if(ps == polygon.begin())	pss = polygon.end()-1;
		else	pss = pe-1;			//ps的上一个点
		if(ps == polygon.end()-1)   pe = polygon.begin();
		else	pe = ps+1;			//ps的下一个点
		if(pe == polygon.end()-1)   pee = polygon.begin();
		else	pee = pe+1;			//ps的下两个点
		if(ps->y() != pe->y())	//不处理水平线
		{
			e.dx = (pe->x() - ps->x())/(pe->y() - ps->y());
			if(pe->y() > ps->y())
			{
				e.xi = ps->x();
				if(pee->y() > pe->y())
					e.ymax = (double)pe->y() - 0.9 * interval;//1;
				else
					e.ymax = pe->y();
				int index = (ps->y() - ymin) / interval;
				slNet[index].push_front(e);
			}
			else
			{
				e.xi = pe->x();
				if(pss->y() > ps->y())
					e.ymax = (double)ps->y() - 0.9 * interval;//1;
				else
					e.ymax = ps->y();
				int index = (pe->y() - ymin) / interval;
				slNet[index].push_front(e);	
			}
		}
	}
	if(debug){
		cout<<"Net:"<<endl;
		for(unsigned int i = 0; i < slNet.size(); i++){
			if(!slNet[i].empty()){
				cout<<i*interval+ymin<<":";
				for(list<EDGE>::iterator it = slNet[i].begin(); it != slNet[i].end(); it++)
					it->print();
				cout<<endl;
			}
		}
	}
}

void MyWidget::buildAet(vector<list<EDGE>> &slAet, vector<list<EDGE>> slNet, int ymin){
	list<EDGE> aet;//当前扫描线的活动边表
	for(unsigned int i = 0; i < slNet.size(); i++){
		if(!slNet[i].empty()){
			for(list<EDGE>::iterator it = slNet[i].begin(); it != slNet[i].end(); it++){
				//it->live = true;
				aet.push_front(*it);
			}
		}
		aet.sort();
		//构建当前扫描线的活动边表aet完毕
		slAet[i] = aet;
		//为下一个扫描线的活动边表做准备:
		aet.remove_if(bind2nd(ptr_fun(IsEdgeOutOfActive), i * interval + ymin));
		for(list<EDGE>::iterator it = aet.begin(); it!= aet.end(); it ++){
			it->xi += it->dx * interval;
		}
	}
	if(debug){
		cout<<"Aet:"<<endl;
		for(unsigned int i = 0; i < slAet.size(); i++){
			if(!slAet[i].empty()){
				cout<<i*interval+ymin<<":";
				for(list<EDGE>::iterator it = slAet[i].begin(); it != slAet[i].end(); it++)
					it->print();
				cout<<endl;
			}
		}
	}
}
void MyWidget::buildXs(vector<vector<double>> &slXs, vector<list<EDGE>> slAet, int ymin){
	vector<double> xs;
    for(unsigned int i = 0; i < slAet.size() - 1; i++){
	    xs.clear();
	    if(!slAet[i].empty() && !slAet[i+1].empty()){
		    vector<EDGE> Aet1, Aet2;
		    Aet1.clear(); Aet2.clear();
		    for(list<EDGE>::iterator itl = slAet[i].begin(); itl != slAet[i].end(); itl++)
				Aet1.push_back(*itl);
			for(list<EDGE>::iterator itl = slAet[i+1].begin(); itl != slAet[i+1].end(); itl++)
				Aet2.push_back(*itl);
			vector<EDGE>::iterator it, it2;
		    //预处理
		    for(it = Aet1.begin(); it != Aet1.end()-1 && it != Aet1.end(); ){
			    if(abs(it->xi - (it+1)->xi) <= 1e-5 && (it->ymax <= i*interval+ymin && (it+1)->ymax <= i*interval+ymin)){
				    it = Aet1.erase(it);it = Aet1.erase(it);
			    }else{
				    it = it+1;
			    }
		    }
			if(debug)
				cout << Aet1.size() << " ";
		    for(it = Aet2.begin(); it != Aet2.end()-1 && it != Aet2.end(); ){
			    if(abs(it->xi - (it+1)->xi) <= 1e-5 && (it->ymax > (i+1)*interval+ymin || (it+1)->ymax > (i+1)*interval+ymin)){
				    it = Aet2.erase(it);it = Aet2.erase(it);
			    }else{
				    it = it+1;
			   }
		    }
			if(debug)
				cout << Aet2.size() << " ";
		    //获得每行的分界的x序列 xs
		    if(Aet1.size() == Aet2.size()){
				for(unsigned int j = 0; j < Aet1.size(); j+=2){
				    xs.push_back(Aet1[j].xi <= Aet2[j].xi? Aet1[j].xi: Aet2[j].xi);
				    xs.push_back(Aet1[j+1].xi >= Aet2[j+1].xi? Aet1[j+1].xi: Aet2[j+1].xi);
			    }
			    vector<double>::iterator ite;
			    for(ite = xs.begin()+1; ite != xs.end()-1; ){
				    if(*ite == *(ite+1)){
					    ite = xs.erase(ite);ite = xs.erase(ite);
				    }else{
					    ite = ite+2;
				    }
			    }
			}
			slXs[i] = xs;
		}
	}
	if(debug){
		cout<<"Xs:"<<endl;
		for(unsigned int i = 0; i < slXs.size(); i++){
			if(!slAet[i].empty()){
				cout<<((double)i+0.5)*interval+ymin<<":";
				for(vector<double>::iterator it = slXs[i].begin(); it != slXs[i].end(); it++)
					cout << *it << " ";
				cout<<endl;
			}
		}
	}
}
int MyWidget::segment(Points &centers_r, vector<vector<double>> slXs, int ymin){
	int sum = 0;
	int step = block_height/interval;
	if(debug)
		cout<<"centers_r:"<<endl;
    centers_r.clear();
    double center_x, center_y, y0;
	vector<double> xs;
	vector<double> xs1, xs2;
    for(unsigned int i = 0; i < slXs.size(); i+=step){
	    xs.clear();
		if(step == 1)
			xs = slXs[i];
		else{				//step >= 2
			xs = slXs[i];
			for(unsigned int j = i+1; j < i+step && j < slXs.size(); j++){
				int k, k2;
				if(xs.size() == slXs[j].size()){
					for(k = 0; k < slXs[j].size(); k+=2){
						xs[k] = slXs[j][k] < xs[k]? slXs[j][k] : xs[k];
						xs[k+1] = slXs[j][k+1] > xs[k+1]? slXs[j][k+1] : xs[k+1];
					}
				}
				else{
					if(slXs[j].size() > xs.size()){
						xs1 = xs;
						xs2 = slXs[j];
					}
					else{
						xs1 = slXs[j];
						xs2 = xs;
					}
					for(k = 0; k < xs2.size(); k+=2){
						if(xs1[xs1.size()-1] < xs2[k]) break;
					}
					for(k2 = xs2.size()-1; k2 > -1; k2-=2){
						if(xs1[0] > xs2[k2]) break;
					}
					xs.clear();
					if(k2 != -1){
						for(unsigned int k3 = 0; k3 <= k2; k3++)
							xs.push_back(xs2[k3]);
					}
					xs.push_back(xs2[k2+1] < xs1[0]? xs2[k2+1] : xs1[0]);
					xs.push_back(xs2[k-1] > xs1[xs1.size()-1]? xs2[k-1] : xs1[xs1.size()-1]);
					if(k != xs2.size()){
						for(unsigned int k3 = k; k3 <= xs2.size()-1; k3++)
							xs.push_back(xs2[k3]);
					}
					
				}
			}
		}
	    if(!xs.empty()){
			if(debug)
				cout<<(double)i*interval+0.5*block_height+ymin<<": ";
			for(vector<double>::iterator ite = xs.begin(); ite != xs.end(); ite+=2){
				if(debug)
					cout<<*ite<<" "<<*(ite+1)<<" ";
				for(double x0 = *ite; x0 < *(ite+1); x0 += block_width){
					y0 = (double)i*interval+block_height+ymin;
					center_x = x0+0.5*block_width;
					center_y = y0-0.5*block_height;
					centers_r.push_back(Point_2(center_x,center_y));
					//cout<<"("<<center_x<<","<<center_y<<") ";
					sum++;
				}
			}
		    if(debug)
				cout<<endl;
		}
	}
	if(debug)
		cout << "sum: " << sum << endl;
	return sum;
}
Mat MyWidget::draw(Points polygon, vector<Points> polygon_in, QString folder/*int m/*, int index*/, bool fill, double xmin, double xmax, int ymin, int ymax){
	Mat mat(ceil((ymax-ymin+1e-5)*MM_PER_PIXEL2), ceil((xmax-xmin+1e-5)*MM_PER_PIXEL2), CV_8UC1, Scalar(0));
	for(unsigned int j = 0; j < polygon.size(); j ++){
		line(mat,
			Point2f((polygon[j].x() - xmin) * MM_PER_PIXEL2, (ymax - polygon[j].y()) * MM_PER_PIXEL2),
			Point2f((polygon[(j+1)%polygon.size()].x() - xmin) * MM_PER_PIXEL2, (ymax - polygon[(j+1)%polygon.size()].y()) * MM_PER_PIXEL2),
			Scalar(255));
	}
	if(polygon_in.size() > 0){
		for(unsigned int i = 0; i < polygon_in.size(); i++){
			for(unsigned int j = 0; j < polygon_in[i].size(); j ++){
				line(mat,
					Point2f((polygon_in[i][j].x() - xmin) * MM_PER_PIXEL2, (ymax - polygon_in[i][j].y()) * MM_PER_PIXEL2),
					Point2f((polygon_in[i][(j+1)%polygon_in[i].size()].x() - xmin) * MM_PER_PIXEL2, (ymax - polygon_in[i][(j+1)%polygon_in[i].size()].y()) * MM_PER_PIXEL2),
					Scalar(255));
			}
		}
	}
	if(fill){
		//内部填充
		int mm = mat.rows;
		int n = mat.cols;
		int **data = new int*[mm];
		for(int i = 0; i < mm; i ++){
			data[i] = new int[n];
			for(int j = 0; j < n; j ++){
				int v = mat.at<unsigned char>(i, j);
				data[i][j] = v;
			}
		}
		for(int i = 0; i < mm; i ++){
			for (int j = 0; j < n; j ++){
				if(Calculator::pointInContours(data, mm, n, Point(i, j))){
					mat.at<unsigned char>(i, j) = 255;
				}
			}
		}
		for(int i = 0; i < mm; i ++){
			delete[] data[i];
		}
		delete[] data;
		//腐蚀
		int erosion_size = 1;
		Mat element1 = getStructuringElement( MORPH_CROSS, Size( 2 * erosion_size + 1 , 2 * erosion_size + 1 ), Point( erosion_size, erosion_size ));  
		//膨胀
		int dilation_size = 1;
		Mat element2 = getStructuringElement( MORPH_CROSS, Size( 2 * dilation_size + 1, 2 * dilation_size + 1 ), Point( dilation_size,  dilation_size));  
		erode ( mat, mat, element1 );		//腐蚀
		dilate( mat, mat, element2 );		//膨胀
		//颜色翻转
		for(int i = 0; i < mm; i ++){
			for (int j = 0; j < n; j ++){
				mat.at<unsigned char>(i, j) = abs(mat.at<unsigned char>(i, j) - 255);
			}
		}
		erode ( mat, mat, element1 );		//腐蚀
		dilate( mat, mat, element2 );		//膨胀
		//颜色翻转
		for(int i = 0; i < mm; i ++){
			for (int j = 0; j < n; j ++){
				mat.at<unsigned char>(i, j) = abs(mat.at<unsigned char>(i, j) - 255);
			}
		}
	} else {
		//膨胀(使白色目标区域变大一圈）
		int dilation_size = 1;
		Mat element = getStructuringElement( MORPH_CROSS, Size( 2 * dilation_size + 1, 2 * dilation_size + 1 ), Point( dilation_size,  dilation_size));  
		dilate( mat, mat, element );		//膨胀
	}
	QString imagefile = folder + QString("/00.jpg");
	imwrite(imagefile.toStdString(), mat);
	return mat;
}
void MyWidget::drawSeg(vector<Mat> &mats, Mat mat0, Points centers_r, int sum_cur, QString folder, double xmin, int ymax){
	mats.clear();
	for(int c = 0; c < centers_r.size(); c++){
		Mat mat(ceil((block_height)*MM_PER_PIXEL2), ceil((block_width)*MM_PER_PIXEL2), CV_8UC1, Scalar(0));
		int mm = mat.rows;
		int n = mat.cols;
		double center_x = centers_r[c].x();
		double center_y = centers_r[c].y();
		double x0 = center_x-0.5*block_width;
		double y0 = center_y+0.5*block_height;
		for(int i = 0; i < mm; i ++){
			for (int j = 0; j < n; j ++){
				int i0 = i + (ymax-y0)*MM_PER_PIXEL2;
				int j0 = j + (x0-xmin)*MM_PER_PIXEL2;
				if(i0 < mat0.rows && j0 < mat0.cols && i0 >= 0 && j0 >= 0){
					mat.at<unsigned char>(i, j) = mat0.at<unsigned char>(i0, j0);
				}
			}
		}
		mats.push_back(mat);
		QString imagefile = folder + QString("/%1").arg(sum_cur + c) + QString(".jpg");
		imwrite(imagefile.toStdString(), mat);
	}
}

double MyWidget::cross(Point_2 pi,Point_2 pj,Point_2 pk){ // (pi,pj)X(pi,pk)  
    return (pj.x()-pi.x())*(pk.y()-pi.y())-(pj.y()-pi.y())*(pk.x()-pi.x());  
}  
int MyWidget::InPolygon(const Points arr,const Point_2 &p,int on_edge){ 
	Point_2 q;
	int len = arr.size();
	int i=0,counter;  
	while(i<len){  
		q = Point_2(rand()+offset,rand()+offset);//随机取一个足够远的点q 以p为起点q为终点做射线L
		for(counter=i=0;i<len;i++){//依次对多边形的每条边进行考察  
			if(fabs(cross(p,arr[i],arr[(i+1)%len]))<eps &&  
				(arr[i].x()-p.x())*(arr[(i+1)%len].x()-p.x())<eps && (arr[i].y()-p.y())*(arr[(i+1)%len].y()-p.y())<eps)  
				return on_edge; //点p在边上,返回on_edge  
			else if(fabs(cross(p,q,arr[i]))<eps) break; //点arr[i]在射线pq上，停止本循环，另取q  
			else if(cross(p,arr[i],q)*cross(p,arr[(i+1)%len],q)<-eps &&  
				cross(arr[i],p,arr[(i+1)%len])*cross(arr[i],q,arr[(i+1)%len])<-eps) 
				counter++;  
		}  
	}  
	return counter&1;  
}

void MyWidget::getBound(Points &points_r, double &xmin, double &xmax, int &ymin, int &ymax){
	for(vector<Point_2>::iterator it = points_r.begin(); it != points_r.end(); it++){
		*it = Point_2(it->x(),/*floor(it->y()+0.5)*/(int)it->y());//对旋转后的多边形进行纵坐标取整(取整到1mm，interval=1）
	}
	ymin = points_r[0].y(); ymax = ymin;
	for(unsigned int i = 1; i < points_r.size(); i++){
		if(points_r[i].y() < ymin) ymin = points_r[i].y();
		if(points_r[i].y() > ymax) ymax = points_r[i].y();
	}
	if(debug) cout<<"ymin:"<<ymin<<" ymax:"<<ymax<<endl;
	xmin = points_r[0].x(); xmax = xmin;
	for(unsigned int i = 1; i < points_r.size(); i++){
		if(points_r[i].x() < xmin) xmin = points_r[i].x();
		if(points_r[i].x() > xmax) xmax = points_r[i].x();
	}
	if(debug) cout<<"xmin:"<<xmin<<" xmax:"<<xmax<<endl;
}
void MyWidget::buildAll(vector<vector<double>> &slXs, Points polygon, int ymin, int num){
	vector<list<EDGE>> slNet(num); //新边表
	buildNet(slNet, polygon, ymin);
	vector<list<EDGE>> slAet(num); //所有活动边表
	buildAet(slAet, slNet, ymin);
	buildXs(slXs, slAet, ymin);
}
void MyWidget::mergeXs(vector<vector<double>> &slXs, vector<vector<double>> slXs2){
	for(unsigned int i = 0; i < slXs.size(); i++){
		for(unsigned int j = 0; j < slXs2[i].size(); j++){
			slXs[i].push_back(slXs2[i][j]);
		}
		sort(slXs[i].begin(),slXs[i].end());
	}
}