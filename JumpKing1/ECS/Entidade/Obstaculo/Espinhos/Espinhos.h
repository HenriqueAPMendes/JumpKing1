#pragma once

#include "../Obstaculo.h"

class Espinhos : public Obstaculo
{
public:
	Espinhos();
	~Espinhos();
	void render();
	void renderHitbox();

	void atualizar();

	SDL_Rect getPos() const;
	bool isOnScreen() const;
	void setScreen(const bool inScreen);

	void setPosition(int x, int y, int srcX, int srcY);
private:
	SDL_Rect fonte;
	SDL_Rect destino;
	bool onScreen;
};

