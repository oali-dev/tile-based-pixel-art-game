#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
	explicit Camera();								// Constructor
	~Camera();										// Deconstructor
	void Update(float positionX, float positionY);	// Update the camera
	void GoToPoint(float xCoord, float yCoord, double speed);
	void ReturnToCharacter();

private:
	float _scrollSpeed;								// Speed that the camera moves
};

#endif