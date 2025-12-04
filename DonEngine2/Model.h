#ifndef MODEL
#define MODEL

#include "SimObject.h"
#include "Mesh.h"

//Loads and stores a bunch of Mesh objects loaded from an OBJ/MTL file
class Model : public SimObject
{
public:
	// CONSTRUCTOR
	Model(const char* name, const char* fileName) : SimObject(name) //fileName is from location/name.obj => name
	{
		//variable data for the filesystems
		std::ifstream inMtlFile(std::filesystem::current_path() / (std::string("Models\\") + fileName + std::string(".mtl")));
		std::ifstream inObjFile(std::filesystem::current_path() / (std::string("Models\\") + fileName + std::string(".obj")));
		std::string nextLine = "";

		//temporary textures
		std::vector<Texture> tempTextures;

		//------ MTL FILE LOADING ------
		//load all textures from .mtl file into a temporary vector
		// File loading error check
		if (!inMtlFile.is_open()) throw "ERROR::MODEL::LOADING::Could not open mtl file.";

		//temporary parsing variables
		bool newMat = false;
		std::string matName;
		std::string texFilename;

		//parser loop for mtl file
		while (std::getline(inMtlFile, nextLine))
		{
			//breaking nextLine into parts to parse
			std::istringstream stream(nextLine);
			std::string prefix;
			stream >> prefix;

			if (!newMat && prefix == "newmtl") //if there is no material being read and you encounter this prefix
			{
				///then there is a new material with this name
				stream >> matName;
				newMat = true;
			}
			else if (newMat && prefix == "map_Kd") //if there is a material being read and you encounter this prefix
			{
				//then there is a texture filepath for this material
				std::string filePath;
				stream >> filePath;
				texFilename = filePath.substr(filePath.find_last_of("\\") + 1);

				//creating a new material and adding it to the vector
				tempTextures.push_back({ matName, texFilename.c_str()});
			}
		}

		//------ OBJ FILE LOADING ------
		//load all vertex pos/tex/nor data from .obj file into temporary vectors
		//File loading error check
		if (!inObjFile.is_open()) throw "ERROR::MODEL::LOADING::Could not open obj file.";

		//temporary parsing variables
		std::vector<glm::vec3> tempPositions, tempNormals;
		std::vector<glm::vec2> tempTexCoords;

		//temporary mesh veriables
		std::string tempObjName;
		Texture tempTexture;
		std::vector<Vertex> tempVertices;
		std::vector<int> tempIndices;

		//parser loop for obj file
		while (std::getline(inObjFile, nextLine))
		{
			//breaking nextLine into parts to parse
			std::istringstream stream(nextLine);
			std::string prefix;
			stream >> prefix;

			if (prefix == "o") //if this prefix
			{
				//------NEEDS FIXED TO SUPPORT MULTIPLE MESHES------
				//if no current mesh name, make new mesh
				//if currently a mesh name, store mesh in Model and make new mesh
				//		clear verts/inds/tex/etc after storing
				
				//set name mesh
				stream >> tempObjName;
			}
			else if (prefix == "v")
			{
				double x, y, z;
				stream >> x >> y >> z;
				tempPositions.push_back(glm::vec3(x, y, z));
			}
			else if (prefix == "vt")
			{
				double x, y;
				stream >> x >> y;
				tempTexCoords.push_back(glm::vec2(x, y));
			}
			else if (prefix == "vn")
			{
				double x, y, z;
				stream >> x >> y >> z;
				tempNormals.push_back(glm::vec3(x, y, z));
			}
			else if (prefix == "usemtl")
			{
				std::string texName;
				stream >> texName;
				
				for (Texture texture : tempTextures)
				{
					if (texture.textureName == texName)
					{
						tempTexture = texture;
						break;
					}
				}
			}
			else if (prefix == "f")
			{
				//getting the faces vertex strings
				std::string item;
				std::vector<std::string> items;
				while (stream >> item) 
				{
					items.push_back(item);
				}

				//parsing the strings into Vertex's and adding them appropriately, 1/2/3 -> Vertex -> add to verts/inds vectors
				for (std::string nextStr : items)
				{
					//parsing the string "1/2/3" into 1, 2, 3 as ints
					std::istringstream nextStream(nextStr);
					int pos, tex, nor;
					char slash;
					nextStream >> pos >> slash >> tex >> slash >> nor;

					//making a new Vertex object from the parsed indices
					Vertex tempVertex = { tempPositions.at(pos - 1), tempNormals.at(nor - 1) ,tempTexCoords.at(tex - 1) };

					//adding the vertices and indices appropriately
					if (tempVertices.empty())
					{
						tempIndices.push_back(tempVertices.size());
						tempVertices.push_back(tempVertex);
					}
					else
					{
						bool hit = false;
						for (size_t i = 0; i < tempVertices.size(); i++)
						{
							// Check if the temp vertex is the same as a vertex already in the array
							if (tempVertex.position == tempVertices.at(i).position &&
								tempVertex.texCoord == tempVertices.at(i).texCoord &&
								tempVertex.normal == tempVertices.at(i).normal)
							{
								tempIndices.push_back(i);
								hit = true;
								break;
							}
						}
					
						if (hit == false)
						{
							tempIndices.push_back(tempVertices.size());
							tempVertices.push_back(tempVertex);
						}
					}
				}
			}
		}
		//------NEEDS FIXED AND POSSIBLY REMOVED------
		//add final Mesh to Model
		this->AddChild(new Mesh(tempObjName.c_str(), tempVertices, tempIndices, tempTexture));

		//SimObject requirements
		UpdateModelMatrix(modelMatrix);

		//cleaning up
		inMtlFile.close();
		inObjFile.close();
	}
};
#endif MODEL