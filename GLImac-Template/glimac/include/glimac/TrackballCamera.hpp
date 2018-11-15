class TrackballCamera
{
private:
	float m_fDistance;
	float m_fAngleX;
	float m_fAngleY;

public:
	TrackballCamera();
	~TrackballCamera();
	
	void moveFront(float delta);
	void rotateLeft(float degrees);
	void rotateUp(float degrees);

	glm::mat4 getViewMatrix() const;
};