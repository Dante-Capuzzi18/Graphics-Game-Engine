#ifndef MODELLOADER
#define MODELLOADER

//this class will load an obj/mtl file into an opengl useable set of stuff
static class ModelLoader
{
public:
	//LOAD MODEL
	//will load an obj model given the name of the file location/name.obj as "name"
	static void LoadModel(const char* nameOfFile);
private:

};

#endif MODELLOADER