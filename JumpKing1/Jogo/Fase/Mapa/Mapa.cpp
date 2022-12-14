#include "Mapa.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../Fase.h"
#include <iostream>

SDL_Point Mapa::nTiles;
int Mapa::tamanhoDoTile;

const char* mapa1_camada1 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_1.csv";
const char* mapa1_camada2 = "Assets/TileMap/Mapa1/mapa1_camada_tiles_2.csv";
const char* mapa1_camada_colisao = "Assets/TileMap/Mapa1/mapa1_camada_colisao.csv";
const char* mapa1_posicoes_lava = "Assets/TileMap/Mapa1/mapa1_posicoes_lava.csv";
const char* mapa1_posicoes_espinhos = "Assets/TileMap/Mapa1/mapa1_posicoes_espinhos.csv";

const char* mapa2_camada1 = "Assets/TileMap/Mapa2/mapa2_Camada_0.csv";
const char* mapa2_camada2 = "Assets/TileMap/Mapa2/mapa2_Camada_1.csv";
const char* mapa2_camada_colisao = "Assets/TileMap/Mapa2/mapa2_Camada_colisao.csv"; 
const char* mapa2_posicoes_lava = "Assets/TileMap/Mapa2/mapa2_posicoes_lava.csv";
const char* mapa2_posicoes_espinhos = "Assets/TileMap/Mapa2/mapa2_posicoes_espinhos.csv";

Mapa::Mapa() {
	backgroundTex = nullptr;
	fase = nullptr;
	tamanhoDoTile = 32;
	fim = { 0,0,0,0 };
	onBossRoom = false;
	id = 0;
	graphics = GerenciadorGrafico::getInstance();
}

Mapa::~Mapa() {
	clear();
	SDL_DestroyTexture(backgroundTex);
}

void Mapa::inicializar(int id, Fase* fs){
	this->id = id;
	fase = fs;

	switch (id) {
	case 1:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa1/mapa1background.png"); //65mb de textura??????
		fim = { 0,64,32,96 };
		tileMap.carregaPosicoesValidas(mapa1_posicoes_lava, mapa1_posicoes_espinhos);
		tileMap.inicializa(mapa1_camada1, mapa1_camada2, mapa1_camada_colisao, 80, 200); 
		break;
	case 2:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa2/mapa2.png");
		fim = { 0,96,32,288 };
		tileMap.carregaPosicoesValidas(mapa2_posicoes_lava, mapa2_posicoes_espinhos);
		tileMap.inicializa(mapa2_camada1, mapa2_camada2, mapa2_camada_colisao, 65, 250);
	default:
		break;
	}

	nTiles = tileMap.getNTiles();
	GerenciadorDeCamera::getInstance()->init();
}

void Mapa::reload(int id, Fase* fs) {
	this->id = id;
	fase = fs;

	switch (id) {
	case 1:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa1/mapa1background.png");
		fim = { 0,64,32,96 };
		if (!onBossRoom) tileMap.inicializa(mapa1_camada1, mapa1_camada2, mapa1_camada_colisao, 80, 200);
		else boss_room.reload(id);
		break;
	case 2:
		backgroundTex = graphics->LoadTexture("Assets/TileMap/Mapa2/mapa2.png");
		fim = { 0,96,32,288 };
		if (!onBossRoom) tileMap.inicializa(mapa2_camada1, mapa2_camada2, mapa2_camada_colisao, 65, 250);
		else boss_room.reload(id);
		break;
	default:
		break;
	}

	GerenciadorDeCamera::getInstance()->init();
}

void Mapa::atualizar() {
	if (!onBossRoom) {
		tileMap.atualiza();
		SDL_Rect hitbox = GerenciadorDeColisao::getInstance()->getJogador1()->getComponente<ComponenteColisao>()->getColisor();
		if (GerenciadorDeColisao::getInstance()->AABB(fim, hitbox)) {
			clear();
			onBossRoom = true;
			boss_room.inicializar(id);
			fase->criaMagos();
			return;
		}
		hitbox = GerenciadorDeColisao::getInstance()->getJogador2()->getComponente<ComponenteColisao>()->getColisor();
		if (GerenciadorDeColisao::getInstance()->AABB(fim, hitbox)) {
			clear();
			onBossRoom = true;
			boss_room.inicializar(id);
			fase->criaMagos();
		}
	}
	else
		boss_room.atualizar();
}

void Mapa::render() {

	if (onBossRoom)
		boss_room.render();
	else {
		SDL_Rect destino = { 0, 0, GerenciadorDeCamera::getInstance()->camera.w, GerenciadorDeCamera::getInstance()->camera.h };
		graphics->render(backgroundTex, GerenciadorDeCamera::getInstance()->camera, destino);

		tileMap.render();
	}
}

int Mapa::tamanhoTile() {
	return tamanhoDoTile;
}

void Mapa::setDimMapa(int w, int h) {
	nTiles.x = w;
	nTiles.y = h;
}

SDL_Point Mapa::getDimensoes() {
	SDL_Point temp = nTiles;
	temp.x *= tamanhoDoTile;
	temp.y *= tamanhoDoTile;
	return temp;
}

void Mapa::clear() {
	tileMap.clear();
	boss_room.clear();
}