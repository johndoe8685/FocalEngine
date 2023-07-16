#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	:m_Vertices(vertices), m_Indices(indices)
{
	//Creating Buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glBindVertexArray(VAO);

	//Load data into Vertex Buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

	//Load data into Index Buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Indices.size(), &m_Indices[0], GL_STATIC_DRAW);

	/*
		Creating Vertex Buffer Layout:
			-We have 3 Layouts.Starting from the beginning they are;
				Position - Texture Coordinates - Normals
			-We are using GL_FLOAT in all of them.
			-We dont need to normalize our values (They are not integers thus no need to turn them into 0...1 scale
			- Our Vertex Sizes are in 32 bytes.
			- We have 3 Position, 2 Texture Coordinates and 3 Normal values so for their offset will be 0, 12 and 20
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (const void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const void*)12);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const void*)20);
	glEnableVertexAttribArray(2);
}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Indices.size()), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}