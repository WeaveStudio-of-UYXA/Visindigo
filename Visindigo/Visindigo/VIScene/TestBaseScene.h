#pragma once
#include "../../../CommonEdit/CECore/CEMacro.h"
#ifdef VI_USE_3D
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <Qt3DExtras>

class TestBaseScene :public Qt3DCore::QEntity {
	Q_OBJECT;
	Qt3DCore::QEntity* SphereEntity;
	Qt3DExtras::QSphereMesh* SphereMesh;
	Qt3DExtras::QPhongMaterial* SphereMaterial;
	Qt3DCore::QTransform* SphereTransform;
	Qt3DCore::QEntity* FlatEntity;
	Qt3DExtras::QPlaneMesh* FlatMesh;
	Qt3DExtras::QPhongMaterial* FlatMaterial;
	Qt3DCore::QTransform* FlatTransform;
	_Public def_init TestBaseScene(Qt3DCore::QNode* parent = nullptr) {
		SphereEntity = new Qt3DCore::QEntity(this);
		SphereMesh = new Qt3DExtras::QSphereMesh(SphereEntity);
		SphereMaterial = new Qt3DExtras::QPhongMaterial(SphereEntity);
		SphereTransform = new Qt3DCore::QTransform(SphereEntity);
		SphereEntity->addComponent(SphereMesh);
		SphereEntity->addComponent(SphereMaterial);
		SphereEntity->addComponent(SphereTransform);
		SphereMesh->setRadius(1);
		SphereMesh->setRings(100);
		SphereTransform->setTranslation(QVector3D(0, 1, 0));
		
		FlatEntity = new Qt3DCore::QEntity(this);
		FlatMesh = new Qt3DExtras::QPlaneMesh(FlatEntity);
		FlatMaterial = new Qt3DExtras::QPhongMaterial(FlatEntity);
		FlatTransform = new Qt3DCore::QTransform(FlatEntity);
		FlatEntity->addComponent(FlatMesh);
		FlatEntity->addComponent(FlatMaterial);
		FlatMesh->setWidth(10);
		FlatMesh->setHeight(10);
		FlatMesh->setMeshResolution(QSize(100, 100));
		FlatMaterial->setShininess(0.0f);
		//放在场景原点作为地板
		FlatTransform->setTranslation(QVector3D(0, 0, 0));

	}
};

class TestSceneView :public Qt3DExtras::Qt3DWindow {
	TestBaseScene* rootScene;
	Qt3DExtras::QOrbitCameraController* camController;
	_Public def_init TestSceneView() {
		rootScene = new TestBaseScene();
		this->camera()->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
		this->camera()->setPosition(QVector3D(0, 10.0f, 10.0f));
		this->camera()->setViewCenter(QVector3D(0, 0, 0));
		camController = new Qt3DExtras::QOrbitCameraController(rootScene);
		camController->setLinearSpeed(50.0f);
		camController->setLookSpeed(180.0f);
		camController->setCamera(this->camera());
		this->defaultFrameGraph()->setClearColor(QColor(32, 32, 32));
		this->setRootEntity(rootScene);
	}
};
#endif