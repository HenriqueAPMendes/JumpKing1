#pragma once

#include "../Componente.h"
#include <SDL_image.h>
#include "../../Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../Vector2D/Vector2D.h"

class ComponenteSprite : public Componente {
public:
	ComponenteSprite() {
		textura = nullptr; 
	}
	~ComponenteSprite() {
		SDL_DestroyTexture(textura);
	}

	void setCaminhoArquivo(const char* caminhoArquivo) {
		textura = graphics->LoadTexture(caminhoArquivo);
	}

	void render(SDL_Rect pos) {
		SDL_Rect fonte = { 0, 0, tamanhoTile, tamanhoTile };
		graphics->render(textura, fonte, pos);
	}

	void render(SDL_Rect pos, SDL_Rect fonte, bool flip = false) {
		graphics->render(textura, fonte, pos, flip);
	}
	
private:
	SDL_Texture* textura;
	const int tamanhoTile = 32;
};