#include "GerenciadorDeColisao.h"

#include "../../../Jogo/Fase/Fase.h"
#include "../../../Jogo/Fase/Mapa/Mapa.h"
#include "../../../Jogo/Fase/Mapa/TileMap/TileMap.h"
#include "../../Entidade/Personagem/Jogador/Jogador.h"
#include "../../Entidade/Personagem/Inimigo/InimigoTipo1/InimigoTipo1.h"

TileMap* GerenciadorDeColisao::tilemap = nullptr;
Jogador* GerenciadorDeColisao::jogador1 = nullptr;
Jogo* GerenciadorDeColisao::jogo = nullptr;
Fase* GerenciadorDeColisao::fase = nullptr;

GerenciadorDeColisao::GerenciadorDeColisao() {
	tilemap = nullptr;
	jogador1 = nullptr;
}

GerenciadorDeColisao::~GerenciadorDeColisao() {}

void GerenciadorDeColisao::setJogador(Jogador* jg) {
	jogador1 = jg;
}

void GerenciadorDeColisao::setTileMap(TileMap* tmap) {
	tilemap = tmap;
}

void GerenciadorDeColisao::setJogo(Jogo* jg) {
	jogo = jg;
}

void GerenciadorDeColisao::setFase(Fase* fs) {
	fase = fs;
}

void GerenciadorDeColisao::colisao_jogador1() {
	SDL_Rect initialhitbox = jogador1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;

	ComponenteTransform* transform = jogador1->getComponente<ComponenteTransform>();

	Vector2D velocity = transform->velocidade;

	if (!jogador1->inGround())
		transform->velocidade.y += 0.05; // simula gravidade 

	for (auto& t : tilemap->hitbox_plataformas) {
		if (t->isOnScreen()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jogador1->getSpeed();
			if (AABB(t->getPos(), hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					jogador1->setGround(true);
					transform->posicao.y = t->getPos().y - hitbox.h;
				}
				else if (velocity.y < 0) //colidiu por baixo
					transform->posicao.y = t->getPos().y + hitbox.h;
				transform->velocidade.y = 0;

			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * jogador1->getSpeed();
			if (AABB(t->getPos(), hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = t->getPos().x - hitbox.w;
				}
				else if (velocity.x < 0) //colidiu pela direita
					transform->posicao.x = t->getPos().x + hitbox.w;
				transform->velocidade.x = 0;
			}
		}
	}

	SDL_Rect hitbox_espinho = { 0,0,0,0 };
	
	for (auto& t : tilemap->hitbox_espinhos) {
		if (t->isOnScreen()) {
			//hitbox na parte inferior do tile
			hitbox_espinho.x = t->getPos().x;
			hitbox_espinho.y = t->getPos().y + Mapa::tamanhoTile() / 2;
			hitbox_espinho.w = t->getPos().w;
			hitbox_espinho.h = t->getPos().h - Mapa::tamanhoTile() / 2;

			//mesma checagem usada para as plataformas
			hitbox = initialhitbox;
			hitbox.y += velocity.y * jogador1->getSpeed();
			if (AABB(hitbox_espinho, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					transform->posicao.y = hitbox_espinho.y - hitbox.h;
					transform->velocidade.y = -1.4;
				}
				else if (velocity.y < 0) {//colidiu por baixo // em teoria, pela montagem da fase, nunca deve acontecer
					transform->posicao.y = hitbox_espinho.y + hitbox_espinho.h;
					transform->velocidade.y = 0;
				}
				jogador1->damage();
				break; //apenas uma colisao por vez
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * jogador1->getSpeed();
			if (AABB(hitbox_espinho, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = t->getPos().x - hitbox.w;
					transform->velocidade.x = -1;
				}
				else if (velocity.x < 0) { //colidiu pela direita
					transform->posicao.x = t->getPos().x + hitbox.w;
					transform->velocidade.x = 1;
				}
				jogador1->damage();
				break;
			}
		}
	}

	if (!jogador1->isAlive()) { //morreu -> encerra fase
		fase->gameOver();
	}
}

void GerenciadorDeColisao::colisao_inimigo1(InimigoTipo1* in1) {
	SDL_Rect initialhitbox = in1->getComponente<ComponenteColisao>()->getColisor();
	SDL_Rect hitbox = initialhitbox;
	SDL_Rect platHitbox = initialhitbox;
	bool noPlatform = true;

	ComponenteTransform* transform = in1->getComponente<ComponenteTransform>();

	Vector2D velocity = transform->velocidade;

	if (!in1->inGround())
		transform->velocidade.y += 0.05; // simula gravidade 

	if (transform->velocidade.x == -1) {
		platHitbox.x -= platHitbox.w;
		platHitbox.y += platHitbox.h;
	}
	else {
		platHitbox.x += platHitbox.w;
		platHitbox.y += platHitbox.h;
	}

	for (auto& t : tilemap->hitbox_plataformas) {
		if (t->isOnScreen()) {
			hitbox = initialhitbox;
			hitbox.y += velocity.y * in1->getSpeed();
			if (AABB(t->getPos(), hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					in1->setGround(true);
					transform->posicao.y = t->getPos().y - hitbox.h;
				}
				transform->velocidade.y = 0;
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * in1->getSpeed();
			if (AABB(t->getPos(), hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = t->getPos().x - hitbox.w;
				}
				else if (velocity.x < 0) //colidiu pela direita
					transform->posicao.x = t->getPos().x + hitbox.w;
				transform->velocidade.x = transform->velocidade.x * -1;
			}
			if (AABB(t->getPos(), platHitbox)) { noPlatform = false; }
		}
	}

	// Faz com que inimigos batam na camera pois plataformas fora da camera nao sao reconhecidas
	if (noPlatform && in1->inGround()) { transform->velocidade.x = transform->velocidade.x * -1; }

	SDL_Rect hitbox_espinho = { 0,0,0,0 };

	for (auto& t : tilemap->hitbox_espinhos) {
		//if (t->isOnScreen()) {
			//hitbox na parte inferior do tile
			hitbox_espinho.x = t->getPos().x;
			hitbox_espinho.y = t->getPos().y + Mapa::tamanhoTile() / 2;
			hitbox_espinho.w = t->getPos().w;
			hitbox_espinho.h = t->getPos().h - Mapa::tamanhoTile() / 2;

			//mesma checagem usada para as plataformas
			hitbox = initialhitbox;
			hitbox.y += velocity.y * in1->getSpeed();
			if (AABB(hitbox_espinho, hitbox)) {
				if (velocity.y > 0) { //colidiu por cima
					in1->setGround(true);
					transform->posicao.y = hitbox_espinho.y - hitbox.h;
				}
				else if (velocity.y < 0) //colidiu por baixo // em teoria, pela montagem da fase, nunca deve acontecer
					transform->posicao.y = hitbox_espinho.y + hitbox_espinho.h;
				transform->velocidade.y = 0;
			}
			hitbox = initialhitbox;
			hitbox.x += velocity.x * in1->getSpeed();
			if (AABB(hitbox_espinho, hitbox)) {
				if (velocity.x > 0) { //colidiu pela esquerda
					transform->posicao.x = t->getPos().x - hitbox.w;
				}
				else if (velocity.x < 0) //colidiu pela direita
					transform->posicao.x = t->getPos().x + hitbox.w;
				transform->velocidade.x = transform->velocidade.x * -1;
			}
		//}
	}

	// Checa bordas do mapa em X
	if (transform->posicao.x < 0 && transform->velocidade.x < 0) {
		transform->posicao.x = 0;
		transform->velocidade.x = transform->velocidade.x * -1;
	}
	else if (transform->posicao.x + in1->getComponente<ComponenteColisao>()->getColisor().w > Mapa::getDimensoes().x && transform->velocidade.x > 0) {
		transform->posicao.x = Mapa::getDimensoes().x - in1->getComponente<ComponenteColisao>()->getColisor().w;
		transform->velocidade.x = transform->velocidade.x * -1;
	}

	// Checa bordas do mapa em Y
	if (transform->posicao.y < 0 && transform->velocidade.y < 0)
		transform->posicao.y = transform->velocidade.y = 0;
	else if (transform->posicao.y + in1->getComponente<ComponenteColisao>()->getColisor().h > Mapa::getDimensoes().y && transform->velocidade.y > 0) {
		transform->posicao.y = Mapa::getDimensoes().y - in1->getComponente<ComponenteColisao>()->getColisor().h;
		transform->velocidade.y = 0;
	}
}

bool GerenciadorDeColisao::AABB(SDL_Rect A, SDL_Rect B) {
	if (A.x + A.w > B.x &&
		B.x + B.w > A.x &&
		A.y + A.h > B.y &&
		B.y + B.h > A.y)
		return true;
	return false;	
}

Jogador* GerenciadorDeColisao::getJogador1(){
	return jogador1;
}
