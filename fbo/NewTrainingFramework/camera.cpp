#include "stdafx.h"
#include "camera.h"
#include "Globals.h"


void camera::ProcessKeyboard(CameraMovement direction)
{
	GLfloat velocity = this->MovementSpeed;
	switch (direction)
	{
	case FORWARD:moveZ(-velocity);
		break;
	case BACKWARD:moveZ(velocity);
		break;
	case RIGHT:moveX(velocity);
		break;
	case LEFT:moveX(-velocity);
		break;
	case UP:moveY(velocity);
		break;
	case DOWN:moveY(-velocity);
		break;
	case ROTUP:rotateX(-velocity);
		break;
	case ROTDOWN:rotateX(velocity);
		break;
	case ROTRIGHR:rotateY(velocity);
		break;
	case ROTLEFT:rotateY(-velocity);
		break;
	default:
		break;
	}

}
Matrix camera::getViewM() {
	Matrix rotX, rotY, rotZ, tranlsate;
	rotX.SetRotationX(rotation.x);
	rotY.SetRotationY(rotation.y);
	rotZ.SetRotationZ(rotation.z);
	tranlsate.SetTranslation(-position);
	return tranlsate*rotY.Transpose()*rotX.Transpose()*rotZ.Transpose();
}
camera::camera() {
	projectionMatrix.SetPerspective(45.0f, float(Globals::screenWidth) / float(Globals::screenHeight), 0.1f, 500.0f);
	position = Vector3(0.0f, 0.0f, 2.0f);
	rotation= Vector3(0.0f, 0.0f, 0.0f);
	MovementSpeed = 0.2f;
}
void camera::moveZ(float velocity) {
	position.z += velocity;
}
void camera::moveX(float velocity) {
	position.x += velocity;
}
void camera::moveY(float velocity) {
	position.y += velocity;
}
Vector2 camera::getPositionCursor() {
	POINT pos;
	GetCursorPos(&pos);
	positionCursor.x = pos.x;
	positionCursor.x = pos.y;
	return positionCursor;
}
void camera::setCursorToCentre() {
	SetCursorPos(Globals::screenWidth / 2, Globals::screenHeight / 2);
}
void camera::rotateX(float velocity) {
	rotation.x += velocity/15;
}
void camera::rotateY(float velocity) {
	rotation.y += velocity/15;
}
void camera::mouseMove(int x,int y) {
	/*printf("480/%d 360/%d",x,y );
	double temp= (Globals::screenHeight / 2 - y) / 10000.0;
	printf("%f" ,temp);
	rotation.y += temp;
	rotation.x += ((Globals::screenWidth / 2) - x) / 10000.0;
	//printf("%f %f\n", rotation.x, rotation.y);
	/*if (rotation.x > 0.5)
		rotation.x = 0.5;
	if(rotation.x<-0.5)
		rotation.x = -0.5;*/
}