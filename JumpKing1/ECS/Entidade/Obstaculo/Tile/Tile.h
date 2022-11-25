#pragma once
#include "..//Obstaculo.h"

class Tile : public Obstaculo{
public:
	Tile();
	~Tile();
	void render();
	void renderHitbox();

	void setColide(bool col) { colide = col; }

	void atualizar();
	void salvar(int faseID) { // s�o est�ticos, n�o � necess�rio salvar
	}
	void impedir(Jogador* jogador);

	void setPosition(int x, int y, int srcX, int srcY);
	SDL_Rect getPos() const;
private:
	SDL_Rect fonte;
	SDL_Rect destino;
	bool colide;
};