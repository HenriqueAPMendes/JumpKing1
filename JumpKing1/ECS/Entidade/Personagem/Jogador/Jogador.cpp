#include "Jogador.h"
#include "../../../Gerenciador/GerenciadorDeCamera.h"
#include "../../../Gerenciador/GerenciadorDeColisao.h"
#include "../../../../Jogo/Jogo.h"
#include "../../../../Jogo/Fase/Mapa/Mapa.h"

Jogador::Jogador() {
	inicializar();
	controladorEventos.setTransform(this);
	GerenciadorDeCamera::setJogador(this);
	GerenciadorDeColisao::setJogador(this);
	speed = 8;
	onGround = false;
}

Jogador::~Jogador() {}

void Jogador::inicializar(){
	addComponente<ComponenteAudio>();
	addComponente<ComponenteColisao>();
	addComponente<ComponenteSaude>();
	addComponente<ComponenteSprite>();
	addComponente<ComponenteTransform>();

	getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	transform->velocidade.x = 0;
	transform->velocidade.y = 0;
	transform->posicao.x = 100;
	transform->posicao.y = 6100;

	getComponente<ComponenteColisao>()->set(transform->posicao.x, transform->posicao.y, 32, 32);
}

void Jogador::atualizar() {
	ComponenteTransform* transform = getComponente<ComponenteTransform>();
	getComponente<ComponenteColisao>()->setPos(transform->posicao.x, transform->posicao.y);
	controladorEventos.atualizar();
	transform->posicao.x += transform->velocidade.x * speed;
	transform->posicao.y += transform->velocidade.y * speed;
}

void Jogador::setGround(const bool inGround) {
	onGround = inGround;
}

bool Jogador::inGround() const {
	return onGround;
}

void Jogador::render() {
	// Posicao Jogador na tela = Posicao Jogador no Mapa - Posicao Camera no Mapa
	SDL_Rect posRect = {0,0,Mapa::tamanhoTile(),Mapa::tamanhoTile()};
	posRect.x = (int)getComponente<ComponenteTransform>()->posicao.x - Mapa::camera.x;
	posRect.y = (int)getComponente<ComponenteTransform>()->posicao.y - Mapa::camera.y;

	getComponente<ComponenteSprite>()->render(posRect);
}