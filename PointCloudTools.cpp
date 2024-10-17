#include "PointCloudTools.h"
#include <QFileDialog>
#include <iostream>
#include <vtkRenderWindow.h>
#include <QColorDialog>
#include <QString>
#include <QMessageBox>
#pragma execution_character_set("utf-8")
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingContextOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)


pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

PointCloudTools::PointCloudTools(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//冷知识，槽函数使用时，函数体内不能定义变量
	connect(ui.open, &QAction::triggered, this, &PointCloudTools::open);
	connect(ui.AddAction,&QAction::triggered,this,&PointCloudTools::AddPointCloud);
	connect(ui.clear, &QAction::triggered, this, &PointCloudTools::clear);
	connect(ui.save, &QAction::triggered, this, &PointCloudTools::save);
	connect(ui.exit, &QAction::triggered, this, &PointCloudTools::exit);

	connect(ui.mainwindowaction, &QAction::triggered, this, &PointCloudTools::mainview);
	connect(ui.leftviewaction, &QAction::triggered, this, &PointCloudTools::leftview);
	connect(ui.topviewaction, &QAction::triggered, this, &PointCloudTools::topview);
	connect(ui.resetviewaction, &QAction::triggered, this, &PointCloudTools::resetview);

	connect(ui.actionPassThrough, &QAction::triggered, this, [=] { openFilterPanel(0); });
	connect(ui.actionStatisticalOutlierRemoval, &QAction::triggered, this, [=] { openFilterPanel(1); });
	connect(ui.passthrough_confirm, SIGNAL(clicked()), this, SLOT(FilterPassThrough()));
	connect(ui.statistical_confirm, SIGNAL(clicked()), this, SLOT(FilterStatisticalOutlierRemoval()));


	connect(ui.actionRegionGrowing, &QAction::triggered, this, [=] { openRegionGrowingPanel(true); });
	connect(ui.actionColorBasedRegionGrowing, &QAction::triggered, this, [=] { openRegionGrowingPanel(false); });
	connect(ui.basic_confirm, SIGNAL(clicked()), this, SLOT(RegionGrowing()));
	connect(ui.color_confirm, SIGNAL(clicked()), this, SLOT(RegionGrowingRGB()));

	


	connect(ui.actionPlanFit, &QAction::triggered, this, &PointCloudTools::planFit);
	connect(ui.sphereAction, &QAction::triggered, this, &PointCloudTools::sphereFit);
	connect(ui.pickingaction, &QAction::triggered, this, &PointCloudTools::areaPicking);
	connect(ui.segmentationAction, &QAction::triggered, this, &PointCloudTools::segmentation);

	connect(ui.RegistrationAction, &QAction::triggered, this, &PointCloudTools::Registration);


	connect(ui.showleafnodeaction, &QAction::triggered, this, &PointCloudTools::ShowLeafNode);//展示叶子节点
	connect(ui.showleafnodeaction, &QAction::triggered, this, &PointCloudTools::Centroid);

	connect(ui.meshsurfaceAction, &QAction::triggered, this, &PointCloudTools::convertSurface);
	connect(ui.wireframeAction, &QAction::triggered, this, &PointCloudTools::convertWireframe);
	connect(ui.actionOrigin, &QAction::triggered, [=] { changeTheme(0); });
	connect(ui.actionLight, &QAction::triggered, [=] { changeTheme(1); });
	connect(ui.actionDark, &QAction::triggered, [=] { changeTheme(2); });
	connect(ui.actionEnglish, &QAction::triggered, [=] { changeLanguage(0); });
	connect(ui.actionChinese, &QAction::triggered, [=] { changeLanguage(1); });


	connect(ui.dataTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(itemSelected(QTreeWidgetItem*, int)));

	initial();//调用初始化函数
}



//-----------------------------------------打开点云文件--------------------------------------
void PointCloudTools::open()
{

	QStringList filePathList = QFileDialog::getOpenFileNames(this, tr("Open point cloud file"), toQString(mycloud.fileDir),toQString(fileio.getInputFormatsStr()));
	if (filePathList.isEmpty())
		return;

	// Clear cache
	// TODO: abstract a function
	mycloud_vec.clear();
	total_points = 0;
	ui.dataTree->clear();
	viewer_->removeAllPointClouds();

	doopen(filePathList);

}
void PointCloudTools::doopen(const QStringList &filePathList)
{
	// Open point cloud file one by one
	for (int i = 0; i != filePathList.size(); i++) {
		timeStart();                          // time start
		mycloud.cloud.reset(new PointCloudT); // Reset cloud
		QFileInfo fileInfo(filePathList[i]);
		std::string filePath = fromQString(fileInfo.filePath());
		std::string fileName = fromQString(fileInfo.fileName());

		// begin loading
		ui.statusBar->showMessage(fileInfo.fileName() + ": " + QString::number(i) + "/" + QString::number(filePathList.size()) + " point cloud loading...");

		mycloud = fileio.load(fileInfo);

		mycloud.viewer = viewer_;
		mycloud_vec.push_back(mycloud);

		time_cost = timeOff(); // time off

		consoleLog("Open", toQString(mycloud.fileName), toQString(mycloud.filePath), "Time cost: " + time_cost + " s, Points: " +
			QString::number(mycloud.cloud->points.size()));

		// update tree widget
		QTreeWidgetItem *cloudName = new QTreeWidgetItem(QStringList() << toQString(mycloud.fileName));
		//	cloudName->setIcon(0, QIcon(":/Resources/images/icon.png"));
		ui.dataTree->addTopLevelItem(cloudName);

		total_points += mycloud.cloud->points.size();
	}
	ui.statusBar->showMessage("");
	colorCloudVecDistances();
	showPointcloudAdd();
	setPropertyTable();
}
//-----------------------------------------增加点云文件--------------------------------------
void PointCloudTools::AddPointCloud()
{
	QStringList filePathList = QFileDialog::getOpenFileNames(
		this, tr("Add point cloud file"), toQString(mycloud.fileDir),
		toQString(fileio.getInputFormatsStr()));
	if (filePathList.isEmpty())
		return;
	doopen(filePathList);
}


//-----------------------------------------保存点云文件--------------------------------------
void PointCloudTools::save()
{
	if (!mycloud.isValid) {
		QMessageBox::critical(this, tr("Saving file error"),
			tr("There is no point cloud to save"));
		return;
	}

	// get binary flag from sender()
	QAction *action = qobject_cast<QAction *>(sender());
	QVariant v = action->data();
	bool isSaveBinary = (bool)v.value<bool>();

	QString selectedFilter = toQString(fileio.outputFiltersMap.at(mycloud.fileSuffix));
	QString saveFilePath = QFileDialog::getSaveFileName(
		this,                                    // parent
		toQString("Save point cloud" + string(isSaveBinary ? " (binary)" : "")), // caption
		toQString(mycloud.filePath),             // dir
		toQString(fileio.getOutputFormatsStr()), // filter
		&selectedFilter                          // selected filter
	);
	if (saveFilePath.isEmpty()) return;

	QFileInfo fileInfo(saveFilePath);
	QString saveFileName = fileInfo.fileName();
	string saveFilePathStd = fromQString(saveFilePath);
	string saveFileNameStd = fromQString(saveFileName);

	if (mycloud_vec.size() > 1) {
		savemulti(fileInfo, isSaveBinary);
		return;
	}

	bool saveStatus = fileio.save(mycloud, fileInfo, isSaveBinary);
	if (!saveStatus) {
		QMessageBox::critical(this, tr("Saving file error"),
			tr("We can not save the file"));
		return;
	}

	consoleLog("Save", saveFileName, saveFilePath, "Single save");

	setWindowTitle(saveFilePath + " - CloudViewer");
	QMessageBox::information(this, tr("save point cloud file"),
		toQString("Save " + saveFileNameStd + " successfully!"));
}

void PointCloudTools::savemulti(const QFileInfo &fileInfo, bool isSaveBinary)
{
	string subname = fromQString(fileInfo.fileName());
	QString saveFilePath = fileInfo.filePath();
	PointCloudT::Ptr multi_cloud;
	multi_cloud.reset(new PointCloudT);
	multi_cloud->height = 1;
	int sum = 0;
	for (auto c : mycloud_vec) {
		sum += c.cloud->points.size();
	}
	multi_cloud->width = sum;
	multi_cloud->resize(multi_cloud->height * multi_cloud->width);
	int k = 0;
	for (int i = 0; i != mycloud_vec.size(); ++i) {
		// 注意cloudvec[i]->points.size()和cloudvec[i]->size()的区别
		for (int j = 0; j != mycloud_vec[i].cloud->points.size(); ++j) {
			multi_cloud->points[k].x = mycloud_vec[i].cloud->points[j].x;
			multi_cloud->points[k].y = mycloud_vec[i].cloud->points[j].y;
			multi_cloud->points[k].z = mycloud_vec[i].cloud->points[j].z;
			multi_cloud->points[k].r = mycloud_vec[i].cloud->points[j].r;
			multi_cloud->points[k].g = mycloud_vec[i].cloud->points[j].g;
			multi_cloud->points[k].b = mycloud_vec[i].cloud->points[j].b;
			k++;
		}
	}

	MyCloud multiMyCloud;
	multiMyCloud.cloud = multi_cloud;
	multiMyCloud.isValid = true;

	// save multi_cloud
	bool saveStatus = fileio.save(multiMyCloud, fileInfo, isSaveBinary);
	if (!saveStatus) {
		QMessageBox::critical(this, tr("Saving file error"),
			tr("We can not save the file"));
		return;
	}

	if (isSaveBinary) {
		consoleLog("Save as binary", QString::fromLocal8Bit(subname.c_str()),
			saveFilePath, "Multi save (binary)");
	}
	else {
		consoleLog("Save", QString::fromLocal8Bit(subname.c_str()), saveFilePath,
			"Multi save");
	}

	// 将保存后的 multi_cloud 设置为当前 mycloud,以便保存之后直接进行操作
	mycloud.cloud = multi_cloud;
	mycloud.filePath = fromQString(saveFilePath);
	mycloud.fileName = subname;

	setWindowTitle(saveFilePath + " - CloudViewer");
	QMessageBox::information(this, tr("save point cloud file"),
		toQString("Save " + subname + " successfully!"));
}

//-----------------------------------------清除点云--------------------------------------
void PointCloudTools::clear()
{
	mycloud_vec.clear();             //从点云容器中移除所有点云
	viewer_->removeAllPointClouds(); //从viewer中移除所有点云
	viewer_->removeAllShapes();      //这个remove更彻底
	ui.dataTree->clear();            //将dataTree清空

	ui.propertyTable->clear(); //清空属性窗口propertyTable
	QStringList header;
	header << "Property"
		<< "Value";
	ui.propertyTable->setHorizontalHeaderLabels(header);

	//输出窗口
	consoleLog("Clear", "All point clouds", "", "");

	setWindowTitle("CloudProcess"); //更新窗口标题
	showPointcloud();              //更新显示
}
void PointCloudTools::colorCloudVecDistances()
{
	QList<QTreeWidgetItem *> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	// 如果未选中任何点云，则对视图窗口中的所有点云进行着色
	if (selected_item_count == 0) {
		for (int i = 0; i != mycloud_vec.size(); i++) {
			int cloud_id = i;
			colorCloudDist(cloud_id);
		}

		// 输出窗口
		consoleLog("Color on axis", "All point clous", "", "");

	}
	else {
		for (int i = 0; i != selected_item_count; i++) {
			int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
			colorCloudDist(cloud_id);
		}

		// 输出窗口
		consoleLog("Color on axis", "Point clouds selected", "", "");
	}
}

void PointCloudTools::colorCloudDist(int cloud_id) {

	// Find the minimum and maximum values along the selected axis
	double min, max;
	// Set an initial value
	switch (filtering_axis_) {
	case 0: // x
		min = mycloud_vec[cloud_id].cloud->points[0].x;
		max = mycloud_vec[cloud_id].cloud->points[0].x;
		break;
	case 1: // y
		min = mycloud_vec[cloud_id].cloud->points[0].y;
		max = mycloud_vec[cloud_id].cloud->points[0].y;
		break;
	default: // z
		min = mycloud_vec[cloud_id].cloud->points[0].z;
		max = mycloud_vec[cloud_id].cloud->points[0].z;
		break;
	}

	// Search for the minimum/maximum
	for (PointCloudT::iterator cloud_it = mycloud_vec[cloud_id].cloud->begin();
		cloud_it != mycloud_vec[cloud_id].cloud->end(); ++cloud_it) {
		switch (filtering_axis_) {
		case 0: // x
			if (min > cloud_it->x)
				min = cloud_it->x;

			if (max < cloud_it->x)
				max = cloud_it->x;
			break;
		case 1: // y
			if (min > cloud_it->y)
				min = cloud_it->y;

			if (max < cloud_it->y)
				max = cloud_it->y;
			break;
		default: // z
			if (min > cloud_it->z)
				min = cloud_it->z;

			if (max < cloud_it->z)
				max = cloud_it->z;
			break;
		}
	}

	// Compute LUT scaling to fit the full histogram spectrum
	double lut_scale = 255.0 / (max - min); // max is 255, min is 0

	if (min ==
		max) // In case the cloud is flat on the chosen direction (x,y or z)
		lut_scale = 1.0; // Avoid rounding error in boost

	for (PointCloudT::iterator cloud_it = mycloud_vec[cloud_id].cloud->begin();
		cloud_it != mycloud_vec[cloud_id].cloud->end(); ++cloud_it) {
		int value;
		switch (filtering_axis_) {
		case 0: // x
			value = boost::math::iround(
				(cloud_it->x - min) *
				lut_scale); // Round the number to the closest integer
			break;
		case 1: // y
			value = boost::math::iround((cloud_it->y - min) * lut_scale);
			break;
		default: // z
			value = boost::math::iround((cloud_it->z - min) * lut_scale);
			break;
		}

		// Apply color to the cloud
		switch (color_mode_) {
		case 0:
			// Blue (= min) -> Red (= max)
			cloud_it->r = value;
			cloud_it->g = 0;
			cloud_it->b = 255 - value;
			break;
		case 1:
			// Green (= min) -> Magenta (= max)
			cloud_it->r = value;
			cloud_it->g = 255 - value;
			cloud_it->b = value;
			break;
		case 2:
			// White (= min) -> Red (= max)
			cloud_it->r = 255;
			cloud_it->g = 255 - value;
			cloud_it->b = 255 - value;
			break;
		case 3:
			// Grey (< 128) / Red (> 128)
			if (value > 128) {
				cloud_it->r = 255;
				cloud_it->g = 0;
				cloud_it->b = 0;
			}
			else {
				cloud_it->r = 128;
				cloud_it->g = 128;
				cloud_it->b = 128;
			}
			break;
		default:
			// Blue -> Green -> Red (~ rainbow)
			cloud_it->r =
				value > 128 ? (value - 128) * 2 : 0; // r[128] = 0, r[255] = 255
			cloud_it->g =
				value < 128
				? 2 * value
				: 255 - ((value - 128) * 2); // g[0] = 0, g[128] = 255, g[255] = 0
			cloud_it->b =
				value < 128 ? 255 - (2 * value) : 0; // b[0] = 255, b[128] = 0
		}
	}
}

//-----------------------------------------点云初始化--------------------------------------
void PointCloudTools::initial()
{

	// 界面初始化
	setWindowIcon(QIcon(tr("favicon.ico")));
	setWindowTitle("点云处理");

	//点云初始化
	mycloud.cloud.reset(new PointCloudT);
	mycloud.cloud->resize(1);
	mycloudSelected.cloud.reset(new PointCloudT);
	mycloudSelected.cloud->resize(1);
	mycloudSelected.fileName = "selected";
	mycloudSelected.viewer = viewer_;
	mycloudSelected.cloudId = "selected";
	viewer_.reset(new pcl::visualization::PCLVisualizer("viewer_", false));

	ui.qvtkWidget->SetRenderWindow(viewer_->getRenderWindow());
	//ui.qvtkWidget->render->setBackground(1.0,1.0,1.0);
	viewer_->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();

	ui.propertyTable->setSelectionMode(
		QAbstractItemView::NoSelection); // 禁止点击属性管理器的 item
	ui.consoleTable->setSelectionMode(
		QAbstractItemView::NoSelection); // 禁止点击输出窗口的 item
	ui.dataTree->setSelectionMode(
		QAbstractItemView::ExtendedSelection); // 允许 dataTree 进行多选

	// 设置默认主题
	QString qss = darcula_qss;
	qApp->setStyleSheet(qss);

	setPropertyTable();
	setConsoleTable();
	// 输出窗口
	consoleLog("Software start", "CloudViewer", "Welcome to use CloudViewer", "");

	// 设置背景颜色为 dark
	viewer_->setBackgroundColor(30/255, 30 / 255, 30 / 255);
}
//-----------------------------------------显示点云--------------------------------------
void PointCloudTools::showPointcloud()
{
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer_->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
	}
	ui.qvtkWidget->update();
}

void PointCloudTools::showPointcloudAdd()
{
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer_->addPointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
		viewer_->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
	}
	viewer_->resetCamera();
	ui.qvtkWidget->update();
}
//-----------------------------------------设置点云颜色--------------------------------------
void PointCloudTools::setCloudColor(unsigned int r, unsigned int g, unsigned int b)
{
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		mycloud.cloud->points[i].r = r;
		mycloud.cloud->points[i].g = g;
		mycloud.cloud->points[i].b = b;
		mycloud.cloud->points[i].a = 255;
	}
}
void PointCloudTools::setA(unsigned int a)
{
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		mycloud.cloud->points[i].a = a;
	}
}

int PointCloudTools::areaPicking()
{
	QList<QTreeWidgetItem *> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	// 如果未选中任何点云
	if (selected_item_count == 0) {
		// 错误提示：没有选择点云文件
		QMessageBox::critical(this, tr("Select a part of pointcloud with mouse."),
			tr("There is no Pointcloud file selected."));
		return -1;

	}

	else if (selected_item_count == 1) {

		cloudselect_id = ui.dataTree->indexOfTopLevelItem(itemList[0]);

		//若该点云没有被框选过，则计数值归零，否则增加计数
		if (!mycloud_vec[cloudselect_id].is_seleted) selected_num = 0;
		else selected_num++;

		pcl::PointXYZRGB point;
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr rgbCloudSelect(new pcl::PointCloud<pcl::PointXYZRGB>);
		//按坐标轴赋颜色
		colorCloudVecDistances();

		for (size_t i = 0; i < mycloud_vec[cloudselect_id].cloud->size(); i++) {
			point.x = mycloud_vec[cloudselect_id].cloud->points[i].x;
			point.y = mycloud_vec[cloudselect_id].cloud->points[i].y;
			point.z = mycloud_vec[cloudselect_id].cloud->points[i].z;
			point.r = mycloud_vec[cloudselect_id].cloud->points[i].r;
			point.g = mycloud_vec[cloudselect_id].cloud->points[i].g;
			point.b = mycloud_vec[cloudselect_id].cloud->points[i].b;
			rgbCloudSelect->push_back(point);
		}
		if (!rgbCloudSelect) {
			return -1;
		}
		//更新框选状态
		mycloud_vec[cloudselect_id].is_seleted = true;

		// 输出窗口
		consoleLog("SelectPointCloudPart",
			toQString(mycloud_vec[cloudselect_id].fileName),
			toQString(mycloud_vec[cloudselect_id].filePath),
			"press 'X' to strat or ending picking");

		ui.statusBar->showMessage("");


		//框选类

		PtPicking dc(rgbCloudSelect);
		dc.areaPicking();  //调用区域选择类
		dc.spin();

		mycloudSelected.cloud.reset(new PointCloudT);

		//将框选结果复制给mycloudSelected
		pcl::copyPointCloud(*dc.clicked_points_3d, *mycloudSelected.cloud);

		//根据计数值给新增的框选点云编号
		stringstream ss;
		ss << mycloud_vec[cloudselect_id].fileName << "-selected-" << selected_num;

		mycloudSelected.fileName = ss.str();
		mycloudSelected.viewer = viewer_;
		mycloudSelected.cloudId = "cloud-" + mycloudSelected.fileName;
		//mycloudSelected.isValid = true;
		mycloudSelected.setPointColor(255, 255, 255); // red

		mycloud_vec.push_back(mycloudSelected);

		//更新点云可视化窗口
		viewer_->addPointCloud(mycloud_vec.back().cloud, mycloud_vec.back().cloudId);

		viewer_->setPointCloudRenderingProperties(
			pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,
			mycloud_vec.back().cloudId);
		viewer_->updatePointCloud(mycloud_vec.back().cloud, mycloud_vec.back().cloudId);
		ui.qvtkWidget->update();

		// update tree widget
		QTreeWidgetItem *cloudName = new QTreeWidgetItem(
			QStringList() << toQString(mycloudSelected.fileName));
		cloudName->setIcon(0, QIcon("E:\\5-GLSL\\mota.png"));
		ui.dataTree->addTopLevelItem(cloudName);

		total_points += mycloud.cloud->points.size();
		setPropertyTable();

	}
	else {
		//错误提示：只能选择一个点云文件
		QMessageBox::critical(this, tr("Select a part of pointcloud with mouse."),
			tr("You can just select one Pointcloud file."));
		return -1;
	}
	return 0;
}

//-----------------------------------------设置属性窗口--------------------------------------
void PointCloudTools::setPropertyTable()
{
	QStringList header;
	header << "Property" << "Value";
	ui.propertyTable->setHorizontalHeaderLabels(header);
	ui.propertyTable->setItem(0, 0, new QTableWidgetItem("Clouds"));
	ui.propertyTable->setItem(1, 0, new QTableWidgetItem("Points"));
	ui.propertyTable->setItem(2, 0, new QTableWidgetItem("Total points"));
	ui.propertyTable->setItem(3, 0, new QTableWidgetItem("RGB"));


	ui.propertyTable->setItem(0, 1, new QTableWidgetItem(QString::number(mycloud_vec.size())));
	ui.propertyTable->setItem(1, 1, new QTableWidgetItem(""));
	ui.propertyTable->setItem(2, 1, new QTableWidgetItem(QString::number(total_points)));
	ui.propertyTable->setItem(4, 1, new QTableWidgetItem(""));
}
void PointCloudTools::setConsoleTable()
{
	// 设置输出窗口
	QStringList header2;
	header2 << "Time" << "Operation" << "Operation obeject" << "Details" << "Note";
	ui.consoleTable->setHorizontalHeaderLabels(header2);
	ui.consoleTable->setColumnWidth(0, 150);
	ui.consoleTable->setColumnWidth(1, 200);
	ui.consoleTable->setColumnWidth(2, 200);
	ui.consoleTable->setColumnWidth(3, 300);

	//ui.consoleTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	ui.consoleTable->verticalHeader()->setDefaultSectionSize(22); //设置行距

	ui.consoleTable->setContextMenuPolicy(Qt::CustomContextMenu);

}

void PointCloudTools::consoleLog(QString operation, QString subname, QString filename, QString note)
{
	if (enable_console == false) {
		return;
	}
	int rows = ui.consoleTable->rowCount();
	ui.consoleTable->setRowCount(++rows);
	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	QString time_str = time.toString("MM-dd hh:mm:ss"); //设置显示格式
	ui.consoleTable->setItem(rows - 1, 0, new QTableWidgetItem(time_str));
	ui.consoleTable->setItem(rows - 1, 1, new QTableWidgetItem(operation));
	ui.consoleTable->setItem(rows - 1, 2, new QTableWidgetItem(subname));
	ui.consoleTable->setItem(rows - 1, 3, new QTableWidgetItem(filename));
	ui.consoleTable->setItem(rows - 1, 4, new QTableWidgetItem(note));

	ui.consoleTable->scrollToBottom(); // 滑动自动滚到最底部
}

void PointCloudTools::itemSelected(QTreeWidgetItem* item, int count)
{
	count = ui.dataTree->indexOfTopLevelItem(item);  //获取item的行号
	for (int i = 0; i != mycloud_vec.size(); i++)
	{
		viewer_->updatePointCloud(mycloud_vec[i].cloud, "cloud" + QString::number(i).toStdString());
		viewer_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud" + QString::number(i).toStdString());
	}
	//提取当前点云的RGB,点云数量等信息
	int cloud_size = mycloud_vec[count].cloud->points.size();
	unsigned int cloud_r = mycloud_vec[count].cloud->points[0].r;
	unsigned int cloud_g = mycloud_vec[count].cloud->points[0].g;
	unsigned int cloud_b = mycloud_vec[count].cloud->points[0].b;
	bool multi_color = true;
	if (mycloud_vec[count].cloud->points.begin()->r == (mycloud_vec[count].cloud->points.end() - 1)->r) //判断点云单色多色的条件
		multi_color = false;

	ui.propertyTable->setItem(0, 1, new QTableWidgetItem(QString::number(mycloud_vec.size())));
	ui.propertyTable->setItem(1, 1, new QTableWidgetItem(QString::number(cloud_size)));
	ui.propertyTable->setItem(2, 1, new QTableWidgetItem(QString::number(total_points)));
	ui.propertyTable->setItem(3, 1, new QTableWidgetItem(multi_color ? "Multi Color" : (QString::number(cloud_r) + " " + QString::number(cloud_g) + " " + QString::number(cloud_b))));

	//选中item所对应的点云尺寸变大
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	for (int i = 0; i != selected_item_count; i++) {
		int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[i]);
		viewer_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
			2, "cloud" + QString::number(cloud_id).toStdString());
	}

	ui.qvtkWidget->update();

}
void PointCloudTools::popMenu(const QPoint&)
{
	QTreeWidgetItem *curItem = ui.dataTree->currentItem(); //获取当前被点击的节点
	if (curItem == NULL)
		return; //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
	QString name = curItem->text(0);
	int id = ui.dataTree->indexOfTopLevelItem(curItem);
	MyCloud &myCloud = mycloud_vec[id];

	QAction hideItemAction("Hide", this);
	QAction showItemAction("Show", this);
	QAction deleteItemAction("Delete", this);
	QAction changeColorAction("Change color", this);
	// show mode
	QAction pointModeAction("Set point mode", this);
	QAction meshModeAction("Set mesh mode", this);
	QAction pointMeshModeAction("Set point+mesh mode", this);
	pointModeAction.setData(QVariant(CLOUDVIEWER_MODE_POINT));
	meshModeAction.setData(QVariant(CLOUDVIEWER_MODE_MESH));
	pointMeshModeAction.setData(QVariant(CLOUDVIEWER_MODE_POINT_MESH));

	pointModeAction.setCheckable(true);
	meshModeAction.setCheckable(true);
	pointMeshModeAction.setCheckable(true);

	if (myCloud.curMode == "point") {
		pointModeAction.setChecked(true);
	}
	else if (myCloud.curMode == "mesh") {
		meshModeAction.setChecked(true);
	}
	else if (myCloud.curMode == "point+mesh") {
		pointMeshModeAction.setChecked(true);
	}

	connect(&hideItemAction, &QAction::triggered, this, &PointCloudTools::hideItem);
	connect(&showItemAction, &QAction::triggered, this, &PointCloudTools::showItem);
	connect(&deleteItemAction, &QAction::triggered, this,&PointCloudTools::deleteItem);
	//connect(&changeColorAction, &QAction::triggered, this,&PointCloudTools::pointcolorChanged);

	connect(&pointModeAction, SIGNAL(triggered()), this,SLOT(setRenderingMode()));
	connect(&meshModeAction, SIGNAL(triggered()), this, SLOT(setRenderingMode()));
	connect(&pointMeshModeAction, SIGNAL(triggered()), this,SLOT(setRenderingMode()));

	QPoint pos;
	QMenu menu(ui.dataTree);
	menu.addAction(&hideItemAction);
	menu.addAction(&showItemAction);
	menu.addAction(&deleteItemAction);
	menu.addAction(&changeColorAction);

	menu.addAction(&pointModeAction);
	menu.addAction(&meshModeAction);
	menu.addAction(&pointMeshModeAction);

	if (mycloud_vec[id].visible == true) {
		menu.actions()[1]->setVisible(false);
		menu.actions()[0]->setVisible(true);
	}
	else {
		menu.actions()[1]->setVisible(true);
		menu.actions()[0]->setVisible(false);
	}

	const vector<string> modes = myCloud.supportedModes;
	if (std::find(modes.begin(), modes.end(), "point") == modes.end()) {
		menu.actions()[4]->setVisible(false);
	}
	if (std::find(modes.begin(), modes.end(), "mesh") == modes.end()) {
		menu.actions()[5]->setVisible(false);
	}
	if (std::find(modes.begin(), modes.end(), "point+mesh") == modes.end()) {
		menu.actions()[6]->setVisible(false);
	}

	menu.exec(QCursor::pos()); //在当前鼠标位置显示

}

void PointCloudTools::hideItem()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	for (int i = 0; i != ui.dataTree->selectedItems().size(); i++) {
		//TODO hide之后，item变成灰色，再次右击item时，“hideItem” 选项变成 “showItem”
		//QTreeWidgetItem* curItem = ui.dataTree->currentItem();
		QTreeWidgetItem* curItem = itemList[i];
		QString name = curItem->text(0);
		int id = ui.dataTree->indexOfTopLevelItem(curItem);
		string cloud_id = "cloud" + QString::number(id).toStdString();
		// 将cloud_id所对应的点云设置成透明
		viewer_->setPointCloudRenderingProperties(pcl::visualization::RenderingProperties::PCL_VISUALIZER_OPACITY, 0.0, cloud_id, 0);
		QColor item_color = QColor(112, 122, 132, 255);
		curItem->setTextColor(0, item_color);
		mycloud_vec[id].visible = false;
	}

	// 输出窗口
	consoleLog("Hide point clouds", "Point clouds selected", "", "");

	ui.qvtkWidget->update(); //刷新视图窗口
}
void PointCloudTools::showItem()
{
	QList<QTreeWidgetItem*> itemList = ui.dataTree->selectedItems();
	for (int i = 0; i != ui.dataTree->selectedItems().size(); i++)
	{
		QTreeWidgetItem* curItem = itemList[i];
		QString name = curItem->text(0);
		int id = ui.dataTree->indexOfTopLevelItem(curItem);
		string cloud_id = "cloud" + QString::number(id).toStdString();
		viewer_->setPointCloudRenderingProperties(pcl::visualization::RenderingProperties::PCL_VISUALIZER_OPACITY, 0.0, cloud_id, 0);
		QColor item_color;
		if (theme_id == 0)
		{
			item_color = QColor(0, 0, 0, 255);
		}
		else
		{
			item_color = QColor(241, 241, 241, 255);
		}
		curItem->setTextColor(0, item_color);
		mycloud_vec[id].visible = false;
	}
	// 输出窗口
	consoleLog("Show point clouds", "Point clouds selected", "", "");

	ui.qvtkWidget->update();
}

void PointCloudTools::deleteItem()
{
	QList<QTreeWidgetItem *> itemList = ui.dataTree->selectedItems();
	// 随着迭代次数而改变，因此循环条件要设置为固定大小的 selected_item_count
	int selected_item_count = ui.dataTree->selectedItems().size();
	for (int i = 0; i != selected_item_count; i++) {
		QTreeWidgetItem *curItem = itemList[i];
		QString name = curItem->text(0);
		int id = ui.dataTree->indexOfTopLevelItem(curItem);
		// QMessageBox::information(this, "information", "curItem: " + name + " " +
		// QString::number(id));
		auto it = mycloud_vec.begin() + ui.dataTree->indexOfTopLevelItem(curItem);
		// 删除点云之前，将其点的数目保存
		int delete_points = (*it).cloud->points.size();
		it = mycloud_vec.erase(it);
		total_points -= delete_points;
		setPropertyTable();

		ui.dataTree->takeTopLevelItem(ui.dataTree->indexOfTopLevelItem(curItem));
	}

	// 移除之后再添加，避免 id 和资源管理树行号不一致的情况
	viewer_->removeAllPointClouds();
	for (int i = 0; i != mycloud_vec.size(); i++) {
		viewer_->addPointCloud(mycloud_vec[i].cloud, mycloud_vec[i].cloudId);
		viewer_->updatePointCloud(mycloud_vec[i].cloud, mycloud_vec[i].cloudId);
	}

	// 输出窗口
	consoleLog("Delete point clouds", "Point clouds selected", "", "");

	ui.qvtkWidget->update();
}

//-----------------------------------------改变主题--------------------------------------
void PointCloudTools::changeTheme(int index)
{
	QFile qss;
	switch (index)
	{
	case 0:
		qss.setFileName("origin.qss");
		qss.open(QFile::ReadOnly);
		qApp->setStyleSheet(qss.readAll());
		qss.close();
		ui.statusBar->showMessage(tr("Origin Theme"), 2000);
		break;
	case 1:
		qss.setFileName("light.qss");
		qss.open(QFile::ReadOnly);
		qApp->setStyleSheet(qss.readAll());
		qss.close();
		ui.statusBar->showMessage(tr("Light Theme"), 2000);
		break;
	case 2:
		qss.setFileName("dark.qss");
		qss.open(QFile::ReadOnly);
		qApp->setStyleSheet(qss.readAll());
		qss.close();
		ui.statusBar->showMessage(tr("Dark Theme"), 2000);
		break;
	}
}
//-----------------------------------------改变语言--------------------------------------
void PointCloudTools::changeLanguage(int index)
{
	QAction *action = qobject_cast<QAction *>(sender());
	QVariant v = action->data();
	int language = (int)v.value<int>();

	switch (language) {
	case CLOUDVIEWER_LANG_ENGLISH: {
		consoleLog("Change language", "English", "", "");
		break;
	}
	case CLOUDVIEWER_LANG_CHINESE: {
		consoleLog("Change language", "Chinese",
			"Doesn't support Chinese temporarily", "");
		break;
	}
	}
}
void PointCloudTools::mainview() {
	viewer_->setCameraPosition(0, -1, 0, 0.5, 0.5, 0.5, 0, 0, 1);
	ui.qvtkWidget->update();
}

void PointCloudTools::leftview() {
	viewer_->setCameraPosition(-1, 0, 0, 0, 0, 0, 0, 0, 1);
	ui.qvtkWidget->update();
}

void PointCloudTools::topview() {
	viewer_->setCameraPosition(0, 0, 1, 0, 0, 0, 0, 1, 0);
	ui.qvtkWidget->update();
}
//重置视图
void PointCloudTools::resetview() {
	viewer_->resetCamera();
	ui.qvtkWidget->update();
}

//-----------------------------------------点云面片重建--------------------------------------
int PointCloudTools::convertSurface()
{
	/* 问题
好像该方法只能处理PointXYZ的点云，用PointXZYRGBA的点云编译会报错
调用boost::this_thread::sleep好像也会编译出错
*/
	pcl::PointXYZ point;
	cloud_xyz.reset(new pcl::PointCloud<pcl::PointXYZ>);
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		point.x = mycloud.cloud->points[i].x;
		point.y = mycloud.cloud->points[i].y;
		point.z = mycloud.cloud->points[i].z;
		cloud_xyz->push_back(point);
	}
	if (!cloud_xyz)
	{
		return -1;
	}

	/****** 法向估计模块 ******/
	//创建法线估计对象 n
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	//创建法向数据指针 normals
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//创建 kdtree 用于法向计算时近邻搜索
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud_xyz); //为 kdtree 输入点云
	n.setInputCloud(cloud_xyz); //为法向估计对象输入点云
	n.setSearchMethod(tree);  //设置法向估计时所采取的搜索方式为kdtree
	n.setKSearch(20); //设置法向估计时，k近邻搜索的点数
	n.compute(*normals); //进行法向估计


	/****** 点云数据与法向数据拼接 ******/
	//从这之后出现问题

	//创建同时包含点和法线的数据结构的指针
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);

	//将已获得的点数据和法向数据拼接
	pcl::concatenateFields(*cloud_xyz, *normals, *cloud_with_normals); //这里编译出错，与cloud的类型有关？改成PointXYZ的点云就没有报错了

	//创建另一个kdtree用于重建
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	//为kdtree输入点云数据，该点云数据类型为点和法向
	tree2->setInputCloud(cloud_with_normals);

	/****** 曲面重建模块 ******/
	//创建贪婪三角形投影重建对象
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
	//创建多边形网格对象，用来存储重建结果
	pcl::PolygonMesh triangles;
	//设置参数
	gp3.setSearchRadius(25); //设置连接点之间最大距离，用于确定k近邻的球半径
	gp3.setMu(2.5); //设置最近邻距离的乘子，以得到每个点的最终搜索半径
	gp3.setMaximumNearestNeighbors(100); //设置搜索的最近邻点的最大数量
	gp3.setMaximumSurfaceAngle(M_PI / 2); //45度 最大平面角
	gp3.setMinimumAngle(M_PI / 18); //10度 每个三角的最大角度？
	gp3.setMaximumAngle(2 * M_PI / 3); //120度
	gp3.setNormalConsistency(false); //若法向量一致，设为true
	//设置点云数据和搜索方式
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	// 开始重建
	gp3.reconstruct(triangles);
	QMessageBox::information(this, "informaiton", "Reconstruction finished");



	//将重建结果保存到硬盘文件中，重建结果以VTK格式存储
	pcl::io::saveVTKFile("mymesh.vtk", triangles);



	/****** 图形显示模块 ******/
	viewer_->addPolygonMesh(triangles, "my"); //设置要显示的网格对象
	//设置网格模型显示模式
	viewer_->setRepresentationToSurfaceForAllActors(); //网格模型以面片形式显示
	//viewer_->setRepresentationToPointsForAllActors(); //网格模型以点形式显示
	//viewer_->setRepresentationToWireframeForAllActors(); //网格模型以线框图模式显示

	// 输出窗口
	//consoleLog("Convert surface", "", "", "");

	viewer_->removeAllShapes();
	while (!viewer_->wasStopped())
	{
		viewer_->spinOnce(100);
		//boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	return 0;

}
//-----------------------------------------点云网格重建--------------------------------------
int PointCloudTools::convertWireframe()
{
	pcl::PointXYZ point;
	cloud_xyz.reset(new pcl::PointCloud<pcl::PointXYZ>);
	for (size_t i = 0; i < mycloud.cloud->size(); i++)
	{
		point.x = mycloud.cloud->points[i].x;
		point.y = mycloud.cloud->points[i].y;
		point.z = mycloud.cloud->points[i].z;
		cloud_xyz->push_back(point);
	}
	if (!cloud_xyz)
	{
		return -1;
	}
	/****** 法向估计模块 ******/
	//创建法线估计对象 n
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	//创建法向数据指针 normals
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//创建 kdtree 用于法向计算时近邻搜索
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud_xyz); //为 kdtree 输入点云
	n.setInputCloud(cloud_xyz); //为法向估计对象输入点云
	n.setSearchMethod(tree);  //设置法向估计时所采取的搜索方式为kdtree
	n.setKSearch(20); //设置法向估计时，k近邻搜索的点数
	n.compute(*normals); //进行法向估计


	/****** 点云数据与法向数据拼接 ******/
	//从这之后出现问题

	//创建同时包含点和法线的数据结构的指针
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);

	//将已获得的点数据和法向数据拼接
	pcl::concatenateFields(*cloud_xyz, *normals, *cloud_with_normals); //这里编译出错，与cloud的类型有关？改成PointXYZ的点云就没有报错了

	//创建另一个kdtree用于重建
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	//为kdtree输入点云数据，该点云数据类型为点和法向
	tree2->setInputCloud(cloud_with_normals);



	/****** 曲面重建模块 ******/
	//创建贪婪三角形投影重建对象
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
	//创建多边形网格对象，用来存储重建结果
	pcl::PolygonMesh triangles;
	//设置参数
	gp3.setSearchRadius(25); //设置连接点之间最大距离，用于确定k近邻的球半径
	gp3.setMu(2.5); //设置最近邻距离的乘子，以得到每个点的最终搜索半径
	gp3.setMaximumNearestNeighbors(100); //设置搜索的最近邻点的最大数量
	gp3.setMaximumSurfaceAngle(M_PI / 2); //45度 最大平面角
	gp3.setMinimumAngle(M_PI / 18); //10度 每个三角的最大角度？
	gp3.setMaximumAngle(2 * M_PI / 3); //120度
	gp3.setNormalConsistency(false); //若法向量一致，设为true
	//设置点云数据和搜索方式
	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree2);
	// 开始重建
	gp3.reconstruct(triangles);
	QMessageBox::information(this, "informaiton", "Reconstruction finished");

	//将重建结果保存到硬盘文件中，重建结果以VTK格式存储
	pcl::io::saveVTKFile("mymesh.vtk", triangles);
	/****** 图形显示模块 ******/
	viewer_->addPolygonMesh(triangles, "my"); //设置要显示的网格对象
	//设置网格模型显示模式
	//viewer_->setRepresentationToSurfaceForAllActors(); //网格模型以面片形式显示
	//viewer_->setRepresentationToPointsForAllActors(); //网格模型以点形式显示
	viewer_->setRepresentationToWireframeForAllActors(); //网格模型以线框图模式显示

	// 输出窗口
	
	consoleLog("Convert wireframe", "", "", "");

	viewer_->removeAllShapes();
	while (!viewer_->wasStopped())
	{
		viewer_->spinOnce(100);

	}
	return 0;
}


//-----------------------------------------平面拟合--------------------------------------
int PointCloudTools::planFit()
{
	QList<QTreeWidgetItem*>curitem = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	// 如果未选中任何点云，则对视图窗口中的所有点云进行着色
	if (selected_item_count == 0) {
		// 错误提示：没有选择点云文件
		QMessageBox::critical(this, tr("Select a part of pointcloud with mouse."),
			tr("There is no Pointcloud file selected."));
		return -1;

	}
	else if (selected_item_count == 1) {

		int cloud_id = ui.dataTree->indexOfTopLevelItem(curitem[0]);
		pcl::PointXYZ point;
		cloud_xyz.reset(new pcl::PointCloud<pcl::PointXYZ>);
		for (size_t i = 0; i < mycloud_vec[cloud_id].cloud->size(); i++) {
			point.x = mycloud_vec[cloud_id].cloud->points[i].x;
			point.y = mycloud_vec[cloud_id].cloud->points[i].y;
			point.z = mycloud_vec[cloud_id].cloud->points[i].z;
			cloud_xyz->push_back(point);
		}
		if (!cloud_xyz) {
			return -1;
		}

		PlanFit detect;

		detect.setInputCloud(cloud_xyz);

		bool ok_getNormalDisThres;
		double normalDisThres = QInputDialog::getDouble(this, tr("Set plane fit normal distance weight"),
			tr("normal distance weight (0~1):"), 0.3, 0, 1, 2, &ok_getNormalDisThres);
		bool ok_getPlaneDisThres;
		double planeDisThres = QInputDialog::getDouble(this, tr("Set plane fit distance threshold"),
			tr("plane distance threshold (>0):"), 0.1, 0, 10, 2, &ok_getPlaneDisThres);
		if (ok_getNormalDisThres&&ok_getPlaneDisThres) {
			detect.setPara(planeDisThres, normalDisThres, 0.1);
		}


		detect.compute();
		//平面参数
		mycloud_vec[cloud_id].plane_A = detect.A;
		mycloud_vec[cloud_id].plane_B = detect.B;
		mycloud_vec[cloud_id].plane_C = detect.C;
		mycloud_vec[cloud_id].plane_D = detect.D;

		stringstream detectRes_s;
		detectRes_s << "(" << detect.A << ")x+("
			<< detect.B << ")y+("
			<< detect.C << ")z+("
			<< detect.D << ")=0";
		// 输出窗口
		consoleLog("Plane Fit result", toQString(mycloud_vec[cloud_id].fileName),
			"plane coeffs:", toQString(detectRes_s.str()));

		ui.statusBar->showMessage("");

		// 构造了一个QTableWidget的对象，用来显示平面拟合的参数
		QTableWidget *tableWidget = new QTableWidget(1, 4);
		tableWidget->setWindowTitle("平面参数Ax+By+Cz+D=0");
		tableWidget->resize(600, 50); //设置表格大小
		QStringList header;
		header << "A"
			<< "B"
			<< "C"
			<< "D";
		tableWidget->setHorizontalHeaderLabels(header);
		tableWidget->setItem(0, 0, new QTableWidgetItem(QString("%1").arg(detect.A)));
		tableWidget->setItem(
			0, 1, new QTableWidgetItem(QString("%1").arg(detect.B)));
		tableWidget->setItem(
			0, 2, new QTableWidgetItem(QString("%1").arg(detect.C)));
		tableWidget->setItem(
			0, 3, new QTableWidgetItem(QString("%1").arg(detect.D)));
		// tableWidget->resizeColumnsToContents(); //列宽适应内容
		//禁止修改单元格内容
		tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		//整行选中
		tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		//设置为可以选中多个目标
		tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

		tableWidget->show();

	}
	else {
		//错误提示：只能选择一个点云文件
		QMessageBox::critical(this, tr("Select a part of pointcloud with mouse."),
			tr("You can just select one Pointcloud file."));
		return -1;
	}
	return 0;
}
int PointCloudTools::sphereFit()
{
	QList<QTreeWidgetItem *> itemList = ui.dataTree->selectedItems();
	int selected_item_count = ui.dataTree->selectedItems().size();
	// 如果未选中任何点云，则对视图窗口中的所有点云进行着色
	if (selected_item_count == 0) {
		// 错误提示：没有选择点云文件
		QMessageBox::critical(this, tr("Select a part of pointcloud with mouse."),
			tr("There is no Pointcloud file selected."));
		return -1;

	}
	else if (selected_item_count == 1) {

		int cloud_id = ui.dataTree->indexOfTopLevelItem(itemList[0]);
		pcl::PointXYZ point;
		cloud_xyz.reset(new pcl::PointCloud<pcl::PointXYZ>);
		for (size_t i = 0; i < mycloud_vec[cloud_id].cloud->size(); i++) {
			point.x = mycloud_vec[cloud_id].cloud->points[i].x;
			point.y = mycloud_vec[cloud_id].cloud->points[i].y;
			point.z = mycloud_vec[cloud_id].cloud->points[i].z;
			cloud_xyz->push_back(point);
		}
		if (!cloud_xyz) {
			return -1;
		}

		SphereFit detect;

		detect.setInputCloud(cloud_xyz);

		detect.compute();

		//球面直径
		stringstream detectRes_s;
		detectRes_s << detect.diameter << "mm";
		// 输出窗口
		consoleLog("Height Diff result", toQString(mycloud_vec[cloud_id].fileName),
			toQString(detectRes_s.str()), "");

		ui.statusBar->showMessage("");

		QMessageBox::about(this, "Result", "球面直径:" + QString::number(detect.diameter) + "mm");



	}
	else {
		//错误提示：只能选择一个点云文件
		QMessageBox::critical(this, tr("Select a part of pointcloud with mouse."),
			tr("You can just select one Pointcloud file."));
		return -1;
	}
	return 0;
}
//-----------------------------------------点云滤波--------------------------------------
void PointCloudTools::openFilterPanel(int type)
{
	if (ui.filterDock->isVisible()) {
		ui.filterTab->setCurrentIndex(type);
	}
	else {
		ui.filterDock->setVisible(true);
		ui.filterTab->setCurrentIndex(type);
	}
}

void PointCloudTools::FilterPassThrough()
{
	std::string axis = ui.axis_input->currentText().toStdString();
	float lower_limit = ui.lower_limit_input->text().toFloat();
	float upper_limit = ui.upper_limit_input->text().toFloat();
	PointCloudT::Ptr cloud_filtered = PassThroughFilter(mycloud.cloud, axis, lower_limit, upper_limit);
	// 显示过滤后的点云
	pcl::copyPointCloud(*cloud_filtered, *(mycloud.cloud));
	viewer_->removeAllPointClouds();
	viewer_->addPointCloud(mycloud.cloud, "cloud");
	ui.qvtkWidget->update();
}

void PointCloudTools::FilterStatisticalOutlierRemoval()
{
	bool isNegative = ui.negative_input->currentText().toStdString() == "True" ? true : false;
	int meank = ui.meank_input->text().toInt();
	double stddev = ui.stddev_input->text().toDouble();
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_filtered = StatisticalOutlierRemovalFilter(mycloud.cloud, isNegative,meank,stddev);
	// 显示过滤之后的点云
	pcl::copyPointCloud(*cloud_filtered, *(mycloud.cloud));
	viewer_->removeAllPointClouds();
	viewer_->addPointCloud(mycloud.cloud, "cloud");
	ui.qvtkWidget->update();
}
void PointCloudTools::segmentation(){
	if (0 == mycloud_vec.size() || 0 == mycloud.cloud->points.size())
	{
		ui.statusBar->showMessage(tr("The point cloud count is 0"));
		return;
	}
	PointCloudT::Ptr cloud(new PointCloudT);
	
	if (0 != mycloud_vec.size())
		pcl::copyPointCloud(*mycloud.cloud, m_indicesVec, *cloud);
	else if (0 == mycloud_vec.size() && 0 != mycloud.cloud->points.size())
		pcl::copyPointCloud(*mycloud.cloud, *cloud);
	//QMessageBox::information(this, "informaiton", "11111 finished");
	
	euclideanSegmentation(cloud);//出错位置
	
	ui.statusBar->showMessage(tr("This point cloud file segmentation over"));
}

//上次运行，欧几里得分割函数报错,导致不能运行分割功能
void PointCloudTools::euclideanSegmentation(const PointCloudT::Ptr &cloud)
{
	MyCloud mycloud;
	mycloud.cloud.reset(new PointCloudT);
	// 建立kd-tree对象用来搜索 .
	pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	kdtree->setInputCloud(cloud);
	//QMessageBox::information(this, "informaiton", "22222 finished");//没问题
	// Euclidean 聚类对象.
	pcl::EuclideanClusterExtraction<PointT> clustering;
	// 设置聚类的最小值 40cm (small values may cause objects to be divided
	// in several clusters, whereas big values may join objects in a same cluster).
	clustering.setClusterTolerance(0.5);
	// 设置聚类的小点数和最大点云数
	clustering.setMinClusterSize(100);//100
	clustering.setMaxClusterSize(35000);//25000
	clustering.setSearchMethod(kdtree);
	clustering.setInputCloud(cloud);
	std::vector<pcl::PointIndices> clustersIndices;
	clustering.extract(clustersIndices);
	mycloud.m_indicesVec = clustersIndices;
	//QMessageBox::information(this, "informaiton", "333333 finished");//第三次测试，没问题
	// For every cluster...
	for (std::vector<pcl::PointIndices>::const_iterator i = clustersIndices.begin(); i != clustersIndices.end(); ++i)
	{
		//添加所有的点云到一个新的点云中
		PointCloudT::Ptr cluster(new PointCloudT);
		for (std::vector<int>::const_iterator point = i->indices.begin(); point != i->indices.end(); point++)
			cluster->points.push_back(cloud->points[*point]);
		cluster->width = cluster->points.size();
		cluster->height = 1;
		cluster->is_dense = true;

		// 保存
		if (cluster->points.size() <= 0)
			break;

		*mycloud.cloud += *cluster;
	}
	
	viewer_->removeShape("area_picking" + QString::number(m_iAreaPickingIndex).toStdString());
	viewer_->removePointCloud("area_picking" + QString::number(m_iAreaPickingIndex).toStdString());
	

	//代码错误出现在这段，一直到QMessageBox为止
	// 节点还可以添加子节点
	m_pCarItem->setHidden(false);
	m_pTreeItem->setHidden(false);
	QString strCar = tr("Car_") + QString::number(m_iSegmentationCarIndex);
	QTreeWidgetItem *cloudCarItem = new QTreeWidgetItem(QStringList() << strCar);
	//cloudCarItem->setIcon(0, QIcon(":/Resources/images/icon.png"));
	m_pCarItem->addChild(cloudCarItem);
	QMessageBox::information(this, "informaiton", "44444 finished");//第三次测试，没问题



	QString strTree = tr("Tree_") + QString::number(m_iSegmentationTreeIndex);
	QTreeWidgetItem *cloudTreeItem = new QTreeWidgetItem(QStringList() << strTree);
	cloudTreeItem->setIcon(0, QIcon(":/Resources/images/icon.png"));
	m_pTreeItem->addChild(cloudTreeItem);
	
	ui.dataTree->addTopLevelItem(m_pCarItem);
	ui.dataTree->addTopLevelItem(m_pTreeItem);
	//mycloud.m_strPointName = strCar.toStdString();
	m_pointCloudMap.insert(std::make_pair(strCar, mycloud));
	pcl::visualization::PointCloudColorHandlerCustom<PointT> green(mycloud.cloud, 0, 255, 0);
	viewer_->addPointCloud(mycloud.cloud, green, strCar.toStdString());
	viewer_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, strCar.toStdString());
	// 将cloud_id所对应的点云设置成透明
	m_iSegmentationCarIndex++;

	setPropertyTable();
	ui.qvtkWidget->update();

	
}
//条件欧几里得分割算法有错误。无法实现此功能
void PointCloudTools::conditionalEuclideanSegmentation(const PointCloudT::Ptr &Cloud)
{
	//PointCloudT::Ptr add_cloud(new PointCloudT);

	//pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
	//kdtree->setInputCloud(cloud);


	//pcl::ConditionalEuclideanClustering<pcl::PointXYZ> clustering;
	//clustering.setClusterTolerance(0.4);
	//clustering.setMinClusterSize(100);
	//clustering.setMaxClusterSize(25000);
	//clustering.setInputCloud(cloud);

	//clustering.setConditionFunction(&customCondition);
	//std::vector<pcl::PointIndices> clusters;
	//clustering.segment(clusters);

	//// For every cluster...
	//for (std::vector<pcl::PointIndices>::const_iterator i = clusters.begin(); i != clusters.end(); ++i)
	//{

	//	PointCloudT::Ptr cluster(new PointCloudT);
	//	for (std::vector<int>::const_iterator point = i->indices.begin(); point != i->indices.end(); point++)
	//		cluster->points.push_back(cloud->points[*point]);
	//	cluster->width = cluster->points.size();
	//	cluster->height = 1;
	//	cluster->is_dense = true;

	//	if (cluster->points.size() <= 0)
	//		break;

	//	*add_cloud += *cluster;
	//}
	//viewer_->removeShape("area_picking" + QString::number(m_iAreaPickingIndex).toStdString());
	//viewer_->removePointCloud("area_picking" + QString::number(m_iAreaPickingIndex).toStdString());

	//static int iSegmentationIndex = 1;
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> blue(add_cloud, 0, 0, 255);
	//viewer_->removeShape("segmentation" + QString::number(iSegmentationIndex - 1).toStdString());
	//viewer_->addPointCloud(add_cloud, blue, "segmentation" + QString::number(iSegmentationIndex).toStdString());
	//iSegmentationIndex++;

	//ui.qvtkWidget->update();
}
void PointCloudTools::openRegionGrowingPanel(bool isBasic) {
	if (ui.regionGrowingDock->isVisible()) {
		ui.rgTab->setCurrentIndex(isBasic ? 0 : 1);
	}
	else {
		ui.regionGrowingDock->setVisible(true);
		ui.rgTab->setCurrentIndex(isBasic ? 0 : 1);
	}
}
void PointCloudTools::RegionGrowing()
{
	int k = ui.ksearch_input->text().toInt();
	int min_cluster_size = ui.min_cluster_size_input->text().toInt();
	int max_cluster_size = ui.max_cluster_size_input->text().toInt();
	unsigned int neighbour_number = ui.neighbour_num_input->text().toUInt();
	float smoothness_theta = ui.smoothness_theta_input->text().toFloat();
	float curvature = ui.curvature_input->text().toFloat();
	pcl::RegionGrowing<pcl::PointXYZRGBA, pcl::Normal> regionGrowing = getRegionGrowing(mycloud.cloud, k,
		min_cluster_size,
		max_cluster_size, neighbour_number,
		smoothness_theta,
		curvature);

	std::vector<pcl::PointIndices> clusters;
	regionGrowing.extract(clusters);

	std::cout << "Number of clusters is equal to " << clusters.size() << std::endl;
	std::cout << "First cluster has " << clusters[0].indices.size() << " points." << endl;
	std::cout << "These are the indices of the points of the initial" <<
	std::endl << "cloud that belong to the first cluster:" << std::endl;
	int counter = 0;
	while (counter < clusters[0].indices.size()) {
		std::cout << clusters[0].indices[counter] << ", ";
		counter++;
		if (counter % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;

	if (clusters.size() != 0) {
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud = regionGrowing.getColoredCloud();
		viewer_->removeAllPointClouds();
		viewer_->addPointCloud(colored_cloud);
		ui.qvtkWidget->update();
		consoleLog("处理成功", "已显示分割点云", "", "");
	}
	else {
		consoleLog("处理发生错误", "分类点集数目为0,请更改参数", "", "");
	}
}


//出现一些问题导致PointXYZRGB无法与PointXYZRGBA进行转换
void PointCloudTools::RegionGrowingRGB()
{
	//pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	//QString fileName = QFileDialog::getOpenFileName(this,
	//	tr("Open RGB PointCloud"), ".",
	//	tr("Open point cloud files(*.pcd)"));
	//if (!fileName.isEmpty()) {
	//	pcl::io::loadPCDFile<pcl::PointXYZRGB>(fileName.toStdString(), *cloud);
	//	int min_cluster_size = ui.min_cluster_size2_input->text().toInt();
	//	float neighbors_distance = ui.neighbours_dist_input->text().toFloat();
	//	float point_color_diff = ui.point_color_diff_input->text().toFloat();
	//	float region_color_diff = ui.region_color_diff_input->text().toFloat();
	//	pcl::RegionGrowingRGB<pcl::PointXYZRGB> regionGrowingRGB = getRegionGrowingRGB(cloud, min_cluster_size,
	//		neighbors_distance,
	//		point_color_diff,
	//		region_color_diff);

	//	std::vector<pcl::PointIndices> clusters;
	//	regionGrowingRGB.extract(clusters);

	//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud = regionGrowingRGB.getColoredCloud();
	//	viewer_->removeAllPointClouds();
	//	viewer_->addPointCloud(colored_cloud);
	//	viewer_->resetCamera();
	//	ui.qvtkWidget->update();
	//}
}


//void PointCloudTools::SearchKNear(float x, float y, float z, int &k)
//{
//	KNearWidget *widget = new KNearWidget();
//	widget->show();
//}
//
//
////找到八叉树中的叶子节点并显示
void PointCloudTools::ShowLeafNode()
{
	float resolu = 0.01f;
	pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> tree(resolu);
	tree.setInputCloud(cloud_xyz);
	tree.addPointsFromInputCloud();
	std::cout << "叶子节点个数：" << tree.getLeafCount() << std::endl;
	int depth = tree.getTreeDepth();
	std::vector<Eigen::Vector3f> min, max;
	for (auto it = tree.begin(depth); it != tree.end(); it++)
	{
		if (it.isLeafNode())
		{
			Eigen::Vector3f min_pt, max_pt;
			tree.getVoxelBounds(it, min_pt, max_pt);
			min.push_back(min_pt);
			max.push_back(max_pt);
		}
	}

	float r = 0.0f, g = 0.0f, b = 1.0f;
	//pcl::visualization::PCLVisualizer viewer;
	int id = 0;
	for (auto it = min.begin(), its = max.begin(); it != min.end(); it++, its++)
	{
		std::cout << "极小值：" << it->x() << "\t" << it->y() << "\t" << it->z() << std::endl;
		std::cout << "极大值：" << its->x() << "\t" << its->y() << "\t" << its->z() << std::endl;
		std::cout << std::endl;
		viewer_->addCube(it->x(), its->x(), it->y(), its->y(), it->z(), its->z(), r, g, b, std::to_string(id));
		id++;
	}
	viewer_->setBackgroundColor(0.0, 0.0, 0.0);
	while (!viewer_->wasStopped())
	{
		viewer_->spinOnce();
	}
}
void PointCloudTools::Centroid()
{
	/*pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<PointT>::Ptr cloud_centroid(new pcl::PointCloud<PointT>);*/
	// PCL函数计算质心
	Eigen::Vector4f centroid;					// 质心
	pcl::compute3DCentroid(*cloud, centroid);	// 齐次坐标，（c0,c1,c2,1）
	// 按公式计算质心
	PointT p_c;
	p_c.x = 0; p_c.y = 0; p_c.z = 0;
	for (auto p : cloud->points) {
		p_c.x += p.x;
		p_c.y += p.y;
		p_c.z += p.z;
	}

	p_c.x /= cloud->points.size();
	p_c.y /= cloud->points.size();
	p_c.z /= cloud->points.size();

	//更新点云可视化窗口
	/*viewer_->addPointCloud(cloud);

	viewer_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,mycloud_vec.back().cloudId);
	viewer_->updatePointCloud(cloud);*/
	
	//cout << "pcl计算点云质心结果：" << centroid << endl;
	consoleLog("pcl计算点云质心结果：", "centroid", "Welcome to use CloudViewer", "");
	//pcl::visualization::PCLVisualizer viewer;
	viewer_->addPointCloud(cloud);
	viewer_->addCoordinateSystem();
	// 质心坐标
	PointT center;
	center.x = centroid(0);
	center.y = centroid(1);
	center.z = centroid(2);

	viewer_->addSphere(center, 0.03, 1, 0, 0, "sphere", 0);
	while (!viewer_->wasStopped())
	{
		viewer_->spinOnce(100);
	}
	ui.qvtkWidget->update();
}

void PointCloudTools::Registration()
{
	PointCloudTT::Ptr cloud_in(new PointCloudTT);  // 原始点云
	PointCloudTT::Ptr cloud_tr(new PointCloudTT);  // 转换点云
	PointCloudTT::Ptr cloud_icp(new PointCloudTT);  //ICP输出点云


	int iterations = 1;  // Default number of ICP iterations
	
	pcl::console::TicToc time;
	time.tic();


}

//-----------------------------------------退出--------------------------------------
void PointCloudTools::exit()
{
	this->close();
}