#include "Figura.h"
#include "ETSIDI.h"
#include <cstdlib>

Figura::Figura() {
	//this->vertices = std::vector<Vector3D>;
	this->texturePath = "";
	this->textureID = 0;
	this->_pos = Vector3D();
	this->scale = 1;
}

Figura::Figura(const char* path, const char* textura, float escala, Vector3D pos) {
	this->textureID = 0;
	//this->x = nx; this->y = ny; this->z = nz;
	this->_pos = pos;
	this->scale = escala;
	this->texturePath = textura;
	std::vector< unsigned int > vertexIndices, uvIndices;
	std::vector<Vector3D> temp_vertices;
	std::vector<Vector2D> temp_uvs;

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
	}

	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			Vector3D vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vector2D uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			//unsigned int vertexIndex[3], basura[6];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		Vector3D vertex = temp_vertices[vertexIndex - 1];
		Vector2D UV = temp_uvs[uvIndex - 1];
		this->vertices.push_back(vertex);
		this->UVs.push_back(UV);
	}
}

Figura::Figura(const char* path, const char* textura, float escala, float nx, float ny, float nz) {
	this->textureID = 0;
	this->_pos = Vector3D(nx, ny, nz);
	this->scale = escala;
	this->texturePath = textura;
	std::vector< unsigned int > vertexIndices, uvIndices;
	std::vector<Vector3D> temp_vertices;
	std::vector<Vector2D> temp_uvs;

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
	}

	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			Vector3D vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vector2D uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			//unsigned int vertexIndex[3], basura[6];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		Vector3D vertex = temp_vertices[vertexIndex - 1];
		Vector2D UV = temp_uvs[uvIndex - 1];
		this->vertices.push_back(vertex);
		this->UVs.push_back(UV);
	}
}


void Figura::dibuja() {
	glTranslatef(this->_pos.x, this->_pos.y, this->_pos.z);
	glEnable(GL_TEXTURE_2D);
	if (this->textureID == 0) {
		glBindTexture(GL_TEXTURE_2D, this->asdf(ETSIDI::getTexture(this->texturePath).id));
	}
	else {
		glBindTexture(GL_TEXTURE_2D, this->textureID );
	}
	for (int i = 0; i < this->vertices.size() / 3; i++) {
		
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		for (int j = 0; j < 3; j++) {
			glTexCoord2d(this->UVs[(3 * i) + j].x, 1-this->UVs[(3 * i) + j].y);
			glVertex3f(this->scale * this->vertices[(3 * i) + j].x, this->scale * this->vertices[(3 * i) + j].y, this->scale * this->vertices[(3 * i) + j].z);
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-this->_pos.x, -this->_pos.y, -this->_pos.z);
}

GLuint Figura::asdf(GLuint ID) {
	this->textureID = ID;
	return this->textureID;
}