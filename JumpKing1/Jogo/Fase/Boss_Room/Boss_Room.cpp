#include "Boss_Room.h"
#include "../../Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../../ECS/Gerenciador/GerenciadorDeCamera.h"
#include "../../../ECS/Gerenciador/GerenciadorDeColisao.h"
#include <iostream>

Vector2D Boss_Room::nTiles;
int Boss_Room::tamanhoDoTile;

const char* boss1_camada1 = "Assets/TileMap/Mapa1/Boss_Room/boss_room_Camada_0.csv";
const char* boss1_camada2 = "Assets/TileMap/Mapa1/Boss_Room/boss_room_Camada_1.csv";
const char* boss1_camada_espinhos = "Assets/TileMap/Mapa1/Boss_Room/boss_room_Camada_Espinhos.csv";
const char* boss1_camada_colisao = "Assets/TileMap/Mapa1/Boss_Room/boss_room_Camada_Colisao.csv";

const char* boss2_camada1 = "Assets/TileMap/Mapa2/Boss_Room/boss_room_Camada_0.csv";
const char* boss2_camada2 = "Assets/TileMap/Mapa2/Boss_Room/boss_room_Camada_1.csv";
const char* boss2_camada_espinhos = "Assets/TileMap/Mapa2/Boss_Room/boss_room_Camada_espinhos.csv";
const char* boss2_camada_colisao = "Assets/TileMap/Mapa2/Boss_Room/boss_room_Camada_colisao.csv";

Boss_Room::Boss_Room() {
	backgroundTex = nullptr;
	tamanhoDoTile = 32;
}

Boss_Room::~Boss_Room() {
	clear();
}

void Boss_Room::inicializar(int id) {
	switch (id) {
	case 1:
		backgroundTex = GerenciadorGrafico::LoadTexture("Assets/TileMap/Mapa1/Boss_Room/boss_room.png");
		tileMap.inicializa(boss1_camada1, boss1_camada2, boss1_camada_colisao, boss1_camada_espinhos, 60, 34);
		break;
	case 2:
		backgroundTex = GerenciadorGrafico::LoadTexture("Assets/TileMap/Mapa2/Boss_Room/boss_room2.png");
		tileMap.inicializa(boss2_camada1, boss2_camada2, boss2_camada_colisao, boss2_camada_espinhos, 60, 40);
		break;
	default:
		break;
	}
	
	GerenciadorDeColisao::getJogador1()->getComponente<ComponenteTransform>()->posicao.x = 32 * 32;
	GerenciadorDeColisao::getJogador1()->getComponente<ComponenteTransform>()->posicao.y = 28 * 32;

}

void Boss_Room::atualizar() {
	GerenciadorDeCamera::Atualiza();
	tileMap.atualiza();
}

void Boss_Room::render() {;
	SDL_Rect destino = { 0, 0, GerenciadorDeCamera::camera.w, GerenciadorDeCamera::camera.h };
	GerenciadorGrafico::render(backgroundTex, GerenciadorDeCamera::camera, destino);

	tileMap.render();
}

int Boss_Room::tamanhoTile() {
	return tamanhoDoTile;
}

Vector2D Boss_Room::getDimensoes() {
	return nTiles*tamanhoDoTile;
}

void Boss_Room::clear() {
	SDL_DestroyTexture(backgroundTex);
	tileMap.clear();
}