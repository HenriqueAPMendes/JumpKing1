#pragma once
#include <SDL.h>

class Jogador;
class TileMap;

class GerenciadorDeColisao
{
public:
	GerenciadorDeColisao();
	~GerenciadorDeColisao();

	static Jogador* getJogador1();
	static void setJogador(Jogador* jg);
	static void setTileMap(TileMap* tmap);

	static void colisao_jogador1();
	//void colisao_jogador2();
	//static void colisao_inimigos();

	static bool AABB(SDL_Rect A, SDL_Rect B);
private:

	static Jogador* jogador1;
	static TileMap* tilemap;
};

