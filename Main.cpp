////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include "MeshObject.h"
#include "InstanceObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Scene.h"
#include "BoxTreeObject.h"
#include "AshikhminMaterial.h"
#include "LambertMaterial.h"
#include "Wood.h";
#include <thread>

void project1();
void project2();
void project3();
void Final();

////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {
	std::cout << "Start" << std::endl;
	Final();
	std::this_thread::sleep_for(std::chrono::seconds(20));
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void project1() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Create boxes
	MeshObject box1;
	box1.MakeBox(5.0f,0.1f,5.0f);
	scn.AddObject(box1);

	MeshObject box2;
	box2.MakeBox(1.0f,1.0f,1.0f);

	InstanceObject inst1(box2);
	Matrix34 mtx;
	mtx.MakeRotateX(0.5f);
	mtx.d.y=1.0f;
	inst1.SetMatrix(mtx);
	scn.AddObject(inst1);

	InstanceObject inst2(box2);
	mtx.MakeRotateY(1.0f);
	mtx.d.Set(-1.0f,0.0f,1.0f);
	inst2.SetMatrix(mtx);
	scn.AddObject(inst2);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(0.5f);
	sunlgt.SetDirection(Vector3(-0.5f, -1.0f, -0.5f));
	scn.AddLight(sunlgt);

	PointLight redlgt;
	redlgt.SetBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.SetIntensity(2.0f);
	redlgt.SetPosition(Vector3(2.0f, 2.0f, 0.0f));
	scn.AddLight(redlgt);

	// Create camera
	Camera cam;
	cam.LookAt(Vector3(2.0f, 2.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	cam.SetResolution(800, 600);
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetSuperSample(1);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project1.bmp");
}

////////////////////////////////////////////////////////////////////////////////


void project2() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.8f, 1.0f));

	// Create ground
	MeshObject ground;
	ground.MakeBox(5.0f, 0.1f, 5.0f);
	scn.AddObject(ground);

	Wood tableWood;
	tableWood.SetScale(0.06f);

	// Create dragon
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);
	dragon.Smooth();

	BoxTreeObject tree;
	tree.Construct(dragon);
	//scn.AddObject(tree);

	// Create instance
	InstanceObject inst(tree);
	Matrix34 mtx;
	inst.SetMaterial(&tableWood);
	mtx.MakeRotateY(PI);
	mtx.d.Set(-0.05f, 0.0f, -0.1f);
	inst.SetMatrix(mtx);
	scn.AddObject(inst);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(Vector3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);

	PointLight redlgt;
	redlgt.SetBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.SetIntensity(0.02f);
	redlgt.SetPosition(Vector3(-0.2f, 0.2f, 0.2f));
	scn.AddLight(redlgt);

	PointLight bluelgt;
	bluelgt.SetBaseColor(Color(0.2f, 0.2f, 1.0f));
	bluelgt.SetIntensity(0.02f);
	bluelgt.SetPosition(Vector3(0.1f, 0.1f, 0.3f));
	scn.AddLight(bluelgt);

	// Create camera
	Camera cam;
	cam.LookAt(Vector3(-0.1f, 0.1f, 0.2f), Vector3(-0.05f, 0.12f, 0.0f));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(1);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project2.bmp");
}
void project3() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Materials
	const int nummtls = 4;
	AshikhminMaterial mtl[nummtls];

	// Diffuse
	mtl[0].SetSpecularLevel(0.0f);
	mtl[0].SetDiffuseLevel(1.0f);
	mtl[0].SetDiffuseColor(Color(0.7f, 0.7f, 0.7f));

	// Roughened copper
	mtl[1].SetDiffuseLevel(0.0f);
	mtl[1].SetSpecularLevel(1.0f);
	mtl[1].SetSpecularColor(Color(0.9f, 0.6f, 0.5f));
	mtl[1].SetRoughness(100.0f, 100.0f);

	// Anisotropic gold
	mtl[2].SetDiffuseLevel(0.0f);
	mtl[2].SetSpecularLevel(1.0f);
	mtl[2].SetSpecularColor(Color(0.95f, 0.7f, 0.3f));
	mtl[2].SetRoughness(1.0f, 1000.0f);

	// Red plastic
	mtl[3].SetDiffuseColor(Color(1.0f, 0.1f, 0.1f));
	mtl[3].SetDiffuseLevel(0.8f);
	mtl[3].SetSpecularLevel(0.2f);
	mtl[3].SetSpecularColor(Color(1.0f, 1.0f, 1.0f));
	mtl[3].SetRoughness(1000.0f, 1000.0f);


	//testWood
	Wood tableWood;
	tableWood.SetScale(2.0f);
	tableWood.SetOrigin(Vector3(0, 4.0f, 0));
	tableWood.SetOrientation(ORIENTATION_Y);
	tableWood.SetNoiseBehavior(0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 1.0);

	// Load dragon mesh
	MeshObject dragon;
	dragon.LoadPLY("dragon.ply", 0);

	// Create box tree 
	BoxTreeObject tree;
	tree.Construct(dragon);

	// Create dragon instances
	Matrix34 mtx;
	for (int i = 0; i<nummtls; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx.d.Set(0.0f, 0.0f, -0.1f*float(i));
		inst->SetMatrix(mtx);
		inst->SetMaterial(&mtl[i]);
		scn.AddObject(*inst);
	}

	// Create ground
	LambertMaterial lambert;
	lambert.SetDiffuseColor(Color(0.3f, 0.3f, 0.35f));

	MeshObject ground;
	ground.MakeBox(2.0f, 0.11f, 2.0f, &tableWood);
	scn.AddObject(ground);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(Vector3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);

	// Create camera
	Camera cam;
	cam.LookAt(Vector3(-0.5f, 0.25f, -0.2f), Vector3(0.0f, 0.15f, -0.15f));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(1);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("project3.bmp");
}

void Final() {
	// Create scene
	Scene scn;
	scn.SetSkyColor(Color(0.8f, 0.8f, 1.0f));

	//Materials
	Wood tableWood;
	tableWood.SetScale(2.0f);
	tableWood.SetOrigin(Vector3(10.0f, 0.0f, 0));
	tableWood.SetOrientation(ORIENTATION_Z);
	tableWood.SetNoiseBehavior(0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 1.0);

	// Create ground
	MeshObject ground, backWall, leftWall;
	ground.MakeBox(30.0f, 0.1f, 30.0f);
	backWall.MakeBox(30.0f, 30.0f, 0.1f);
	leftWall.MakeBox(0.1f, 30.0f, 30.f);
	InstanceObject groundInst(ground), backWallInst(backWall);
	scn.AddObject(groundInst);
	Matrix34 mtxBackWall;
	mtxBackWall.d.Set(0.0f, 0.0f, -15.0f);
	backWallInst.SetMatrix(mtxBackWall);
	scn.AddObject(backWallInst);
	InstanceObject leftWallInst(leftWall);
	Matrix34 mtxLeftWall;
	mtxLeftWall.d.Set(-15.0f, 0.0f, 0.0f);
	leftWallInst.SetMatrix(mtxLeftWall);
	scn.AddObject(leftWallInst);


	// Create table
	MeshObject table;
	table.LoadPLY("models/table.ply", 0);
	table.Smooth();
	BoxTreeObject treeTable;
	treeTable.Construct(table);
	// Create instance
	InstanceObject instTable(treeTable);
	instTable.SetMaterial(&tableWood);
	Matrix34 mtxTable;
	//mtxTable.MakeScale(8.0f);
	mtxTable.d.Set(0.0f, 0.0f, 0.0f);
	instTable.SetMatrix(mtxTable);
	scn.AddObject(instTable);

	// Pillars:
	MeshObject column;
	column.LoadPLY("models/column.ply",0);
	column.Smooth();
	BoxTreeObject treeColumn;
	treeColumn.Construct(column);
	InstanceObject instColumn1(treeColumn), instColumn2(treeColumn), instColumn3(treeColumn), instColumn4(treeColumn), instColumn5(treeColumn), instColumn6(treeColumn);
	Matrix34 col1, col2, col3, col4, col5, col6;
	col1.d.Set(10.0f, 0.0f, 10.0f);
	col2.d.Set(-10.0f, 0.0f, 10.0f);
	col3.d.Set(10.0f, 0.0f, 0.0f);
	col4.d.Set(-10.0f, 0.0f, 0.0f);
	col5.d.Set(10.0f, 0.0f, -10.0f);
	col6.d.Set(-10.0f, 0.0f, -10.0f);
	
	instColumn1.SetMatrix(col1);
	//instColumn1.SetMaterial(&tableWood);
	scn.AddObject(instColumn1);
	instColumn2.SetMatrix(col2);
	//instColumn2.SetMaterial(&tableWood);
	scn.AddObject(instColumn2);
	instColumn3.SetMatrix(col3);
	//instColumn3.SetMaterial(&tableWood);
	scn.AddObject(instColumn3);
	instColumn4.SetMatrix(col4);
	//instColumn4.SetMaterial(&tableWood);
	scn.AddObject(instColumn4);
	instColumn5.SetMatrix(col5);
	//instColumn5.SetMaterial(&tableWood);
	scn.AddObject(instColumn5);
	instColumn6.SetMatrix(col6);
	//instColumn6.SetMaterial(&tableWood);
	scn.AddObject(instColumn6);

	// Create lights
	DirectLight sunlgt;
	sunlgt.SetBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.SetIntensity(1.0f);
	sunlgt.SetDirection(Vector3(-0.5f, -1.0f, -0.5f)); //sunlgt.SetDirection(Vector3(2.0f, -3.0f, -2.0f));
	scn.AddLight(sunlgt);

	// Point Light;
	PointLight point1, point2, point3, point4;
	point1.SetBaseColor(Color(1.0f, 1.0f, 1.0f));
	point1.SetIntensity(5.0f);
	point1.SetPosition(Vector3(-5.0f, 15.0f, 5.0f));
	//scn.AddLight(point1);

	point2.SetBaseColor(Color(1.0f, 1.0f, 1.0f));
	point2.SetIntensity(5.0f);
	point2.SetPosition(Vector3(-5.0f, 15.0f, -5.0f));
	//scn.AddLight(point2);


	point3.SetBaseColor(Color(1.0f, 1.0f, 1.0f));
	point3.SetIntensity(5.0f);
	point3.SetPosition(Vector3(5.0f, 15.0f, 5.0f));
	//scn.AddLight(point3);

	point4.SetBaseColor(Color(1.0f, 1.0f, 1.0f));
	point4.SetIntensity(50.0f);
	point4.SetPosition(Vector3(5.0f, 15.0f, -5.0f));
	//scn.AddLight(point4);

	// Create camera
	Camera cam;
	cam.LookAt(Vector3(10.0f, 10.0f, 15.0f), Vector3(0.0f, 0.0f, 0.0f));
	cam.SetFOV(40.0f);
	cam.SetAspect(1.33f);
	cam.SetResolution(800, 600);
	cam.SetSuperSample(1);

	// Render image
	cam.Render(scn);
	cam.SaveBitmap("final1.bmp");
}