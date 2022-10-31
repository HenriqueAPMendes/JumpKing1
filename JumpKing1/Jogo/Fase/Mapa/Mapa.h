#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../../ECS/Componentes/Vector2D/Vector2D.h"
#include "TileMap/TileMap.h"

class Jogo;

class Mapa {
public:
	Mapa();
	~Mapa();
	void inicializar();

	void atualizar();
	void render();
	static int tamanhoTile();
	static Vector2D getDimensoes();

	static SDL_Rect camera;
	
	void clear();

private:
	SDL_Texture* backgroundTex; //background
	static Vector2D nTiles;
	static int tamanhoDoTile;
	TileMap tileMap;
};