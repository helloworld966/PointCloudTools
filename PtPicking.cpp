#include "PtPicking.h"


PtPicking::~PtPicking() {}

PtPicking::PtPicking(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in) {
	//  baseCloud.reset(new pcl::PointCloud<pcl::PointXYZ>());
	//  pcl::copyPointCloud(*cloud_in, *baseCloud);
	baseCloud = cloud_in;
	reset();
};

void PtPicking::reset() {
	// Create cloud
	clicked_points_3d.reset(new pcl::PointCloud<pcl::PointXYZ>);
	// Create viewer
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer"));
	//  viewer->setBackgroundColor(0.1, 0.1, 0.1);
	viewer->setBackgroundColor(0, 0, 0);
	// viewer->addCoordinateSystem(1);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(baseCloud);
	viewer->addPointCloud<pcl::PointXYZRGB>(baseCloud, rgb, "cloud");
	//  viewer->addPointCloud(baseCloud, "cloud");
	viewer->setPointCloudRenderingProperties(
		pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	viewer->resetCamera();
	// viewer->initCameraParameters();
	viewer->addText("press X to strat or ending picking, then close the window", 10, 25, 20, 1, 1, 1, "helpInfo");
}

void PtPicking::keyboardEventOccurred(const visualization::KeyboardEvent &event,void *junk) {

	if (event.getKeySym() == "r" && event.keyDown()) {
		baseCloud->push_back(randomPoint());
		viewer->updatePointCloud(baseCloud, "cloud");
	}
};

//��ѡ�¼��ĵ���
void PtPicking::areaPicking() {
	// Register Keyboard Event
	// viewer->registerKeyboardCallback(&dummyClass::keyboardEventOccurred,
	// *this);
	viewer->registerAreaPickingCallback(
		&PtPicking::areaPicking_callback,
		*this); //���ڵ�������д���˳�Ա��������������������������ô�
	std::cout << "press X to strat or ending picking, then press 'Q'..."
		<< std::endl;
}

//��ѡ�ĵ���
void PtPicking::pointPicking() {
	cloud_mutex.lock(); // for not overwriting the point cloud
	viewer->registerPointPickingCallback(&PtPicking::pointPicking_callback,
		*this);
	std::cout << "Shift+click on three floor points, then press 'Q'..."
		<< std::endl;
	cloud_mutex.unlock();
}

//��ѡ�ĵ��ã�����Ƚ�����ѡ��Ļ����λ�ã�
void PtPicking::ptActicPicking() {
	cloud_mutex.lock(); // for not overwriting the point cloud
	viewer->registerPointPickingCallback(&PtPicking::PtActivePick_callback,*this);
	std::cout << "Shift+click on three floor points, then press 'Q'..."<< std::endl;
	cloud_mutex.unlock();
}

//��ѡ�¼��Ļص�������
//��ѡ��Ļ�ϵ�һ���ֵ���
//ѡ��ʽ������һ��x��ʾ��ʼ���߽���������x�����ڼ�����������ѡ���ƣ����Զ�ο�ѡ������q���˳�ѡ��
void PtPicking::areaPicking_callback(
	const pcl::visualization::AreaPickingEvent &event, void *args) {
	struct callback_args *data =
		(struct callback_args *)args; //�������� & ���ӻ�����
	std::vector<int> indices;
	if (event.getPointsIndices(indices) == false)
		return;
	pcl::PointXYZ clicked_point;
	for (size_t i = 0; i < indices.size(); i++) {
		clicked_point.x = baseCloud->points.at(indices[i]).x;
		clicked_point.y = baseCloud->points.at(indices[i]).y;
		clicked_point.z = baseCloud->points.at(indices[i]).z;
		clicked_points_3d->points.push_back(clicked_point);
	}
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> red(
		clicked_points_3d, 255, 0, 0);
	viewer->removePointCloud("clicked_points");
	viewer->addPointCloud(clicked_points_3d, red, "clicked_points");
	viewer->setPointCloudRenderingProperties(
		pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "clicked_points");
	//  for (int i = 0; i < clicked_points_3d->points.size(); i++)
	//    std::cout << clicked_points_3d->points[i].x << std::endl;
	std::cout << "clicked_points_3d->points.size(): "
		<< clicked_points_3d->points.size() << std::endl;
}

//��ѡ�¼��Ļص�����
//��ѡ��Ļ�ϵĵ���
//ѡ��ʽ����סshift����������ѡ
void PtPicking::pointPicking_callback(
	const pcl::visualization::PointPickingEvent &event, void *args) {
	struct callback_args *data =
		(struct callback_args *)args; //�������� & ���ӻ�����
	if (event.getPointIndex() == -1)
		return;
	pcl::PointXYZ current_point;
	event.getPoint(current_point.x, current_point.y, current_point.z);
	clicked_points_3d->points.push_back(current_point);
	// Draw clicked points in red:
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> red(
		clicked_points_3d, 255, 0, 0);
	viewer->removePointCloud("clicked_points");
	viewer->addPointCloud(clicked_points_3d, red, "clicked_points");
	viewer->setPointCloudRenderingProperties(
		pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "clicked_points");
	std::cout << current_point.x << " " << current_point.y << " "
		<< current_point.z << std::endl;
}

//��ѡ�¼��Ļص�����
//��ѡ�¼����������Ļ�ϵ���һ�㣨pointPicking_callback()��һ��Ҫ������������ϵĵ㣩
//ѡ��ʽ����סshift��������ѡ�񡣼������� Q ���˳�ѡ��
void PtPicking::PtActivePick_callback(
	const pcl::visualization::PointPickingEvent &event, void *args) {
	std::cout << "Picking event active" << std::endl;
	pcl::PointXYZ current_point;
	if (event.getPointIndex() != -1) {
		float x, y, z;
		event.getPoint(current_point.x, current_point.y, current_point.z);
		// std::cout << x << ";" << y << ";" << z << std::endl;
		clicked_points_3d->points.push_back(current_point);
	}
	// Draw clicked points in red:
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> red(
		clicked_points_3d, 255, 0, 0);
	viewer->removePointCloud("clicked_points");
	viewer->addPointCloud(clicked_points_3d, red, "clicked_points");
	viewer->setPointCloudRenderingProperties(
		pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "clicked_points");
	std::cout << current_point.x << " " << current_point.y << " "
		<< current_point.z << std::endl;
}

pcl::PointXYZRGB PtPicking::randomPoint() {
	pcl::PointXYZRGB pt;
	pt.x = (double)rand() / RAND_MAX * 10 - 5;
	pt.y = (double)rand() / RAND_MAX * 10 - 5;
	pt.z = (double)rand() / RAND_MAX * 10 - 5;
	pt.r = 255;
	pt.g = 0;
	pt.b = 0;
	return pt;
};

void PtPicking::spin() {
	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
};

