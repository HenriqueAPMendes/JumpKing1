#include "Botao.h"
#include "../../Jogo/Jogo.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"

Button::Button() {
	pos.x = pos.y = pos.w = pos.h = 0;
	SDL_Color white;
	white.r = white.g = white.b = 255;
	isClicked = isHovering = false;
	texture = nullptr;
	graphics = GerenciadorGrafico::getInstance();
}

void Button::set(int xpos, int ypos, int width, int height) {
	pos.x = xpos;
	pos.y = ypos;
	pos.w = width;
	pos.h = height;
	isClicked = isHovering = false;
}

void Button::setTex(const char* path) {
	texture = graphics->LoadTexture(path);
	if (!texture) std::cout << "button failed loading! Error:" << IMG_GetError();
}

Button::~Button() {
	SDL_DestroyTexture(texture);
}

void Button::handleEvents() {
	if (getMousePos().x > pos.x && getMousePos().x < pos.x + pos.w &&
		getMousePos().y > pos.y && getMousePos().y < pos.y + pos.h)
		isHovering = true;
	else isHovering = false;

	if (isHovering) {
		SDL_PollEvent(&Jogo::evento);
		if (Jogo::evento.type == SDL_MOUSEBUTTONDOWN) {
			if (Jogo::evento.button.button == SDL_BUTTON_LEFT) {
				isClicked = true;
			}
		}
		else isClicked = false;
	}
}

void Button::render() {
	SDL_Rect fonte;
	fonte.x = fonte.y = 0;
	SDL_Point textureSize;
	SDL_QueryTexture(texture, NULL, NULL, &textureSize.x, &textureSize.y);
	fonte.w = textureSize.x;
	fonte.h = textureSize.y;
	graphics->render(texture, fonte, pos);
}

SDL_Point Button::getMousePos() {
	SDL_Point v;
	int x, y;
	SDL_GetMouseState(&x, &y);
	v.x = x;
	v.y = y;
	return v;
}

bool Button::click() {
	return isClicked;
}

void Button::reset() {
	isClicked = isHovering = false;
}
