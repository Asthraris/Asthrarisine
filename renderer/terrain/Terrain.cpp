#include "Terrain.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



#include "Chunk.h"
#include "../RandomGenerator.h"


//DEBUG
//#include <glad/glad.h>
//#include <iostream>




Terrain::Terrain(){
	SHADER =  new Shader("renderer/src/shaders/terrain.vert", "renderer/src/shaders/terrain.frag");
	MODEL_MATRIX = glm::mat4(1.0f);
	RandomGenerator rg;
	SEED = rg.getFloat(-1000.0,1000.0);
}

Terrain::Terrain(float seed):SEED(seed){
	SHADER = new Shader("renderer/src/shaders/terrain.vert", "renderer/src/shaders/terrain.frag");
	MODEL_MATRIX = glm::mat4(1.0f);
}

Terrain::~Terrain()
{
	Map.clear();

}

void Terrain::dynamicLoad(float* view_mat, glm::vec2 Cam_Chunk_Loc , const int& NUM_LIGHTS, const int& RenderDistance ,const int& TERR_LOD,const int& TERR_PER){

	SHADER->Activate();
	SHADER->camMatrix(view_mat);
	SHADER->UpdateModelMatrix(glm::value_ptr(MODEL_MATRIX));
	SHADER->UpdateNUM_LIGHTS(NUM_LIGHTS);


	for (int x = Cam_Chunk_Loc.x -  RenderDistance; x < Cam_Chunk_Loc.x + RenderDistance; x++) {
		for (int y = Cam_Chunk_Loc.y - RenderDistance; y < Cam_Chunk_Loc.y + RenderDistance; y++) {
			 
			if (Map[Grid(x, y)] == nullptr || Map[Grid(x, y)]->LOD !=TERR_LOD || Map[Grid(x, y)]->PERLIN != TERR_PER) {
			    Map[Grid(x, y)] = generateChunk(x, y,TERR_LOD,TERR_PER , SEED);  
			}
			Map[Grid(x, y)]->render();
			
			
		}
	}
}

