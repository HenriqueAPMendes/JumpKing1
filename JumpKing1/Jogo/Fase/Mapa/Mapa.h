#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../../ECS/Componentes/Vector2D/Vector2D.h"
#include "TileMap/TileMap.h"
#include "../Boss_Room/Boss_Room.h"

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
	static void setDimMapa(int w, int h);
	
	void clear();

private:
	SDL_Texture* backgroundTex; //background
	static Vector2D nTiles;
	static int tamanhoDoTile;
	TileMap tileMap;
	Boss_Room boss_room;
	bool onBossRoom;
	SDL_Rect fim; //retangulo que indica fim da fase (entrada da sala do boss)
};