#pragma once
#include "../Utilities/utilities.h"

enum CameraMovement {
	FORWARD = 'W',
	BACKWARD = 'S',
	RIGHT = 'D',
	LEFT = 'A',
	UP = 'E',
	DOWN = 'Q',
	ROTUP = 38,
	ROTDOWN = 40,
	ROTRIGHR = 39,
	ROTLEFT = 37
};
class camera
{
public:
	camera();
	void ProcessKeyboard(CameraMovement direction);
	void moveZ(float velocity);
	void moveX(float velocity);
	void moveY(float velocity);
	void rotateX(float velocity);
	void rotateY(float velocity);
	Matrix getViewM();
	Matrix getProjectionM() { return projectionMatrix; };
	Vector2 getPositionCursor();
	void setCursorToCentre();
	void mouseMove(int x, int y);
private:
	Matrix projectionMatrix;
	Vector3 position;
	GLfloat MovementSpeed;
	Vector3 rotation;
	Vector2 positionCursor;



};

