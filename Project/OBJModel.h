#pragma once
class OBJModel
{
public:
	OBJModel();
	~OBJModel();

	void LoadFromFile(const char* fileName);
	std::vector<float> GetVertexData();
	int GetVertexCount();

private:
	struct Position {float x, y, z};
	struct Color {float r, g, b};
	struct Normal {float x, y, z};
};