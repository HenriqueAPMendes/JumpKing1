#include "LevelMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

LevelMenu::LevelMenu() {
	background = nullptr;
}

LevelMenu::~LevelMenu() {
	SDL_DestroyTexture(background);
}

void LevelMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	back.set(0.1 * dm.w, 0.8 * dm.h , 250, 125);
	back.setTex("Assets/Buttons/Back Button.png");

	level1.set(0.75 * dm.w, 0.275 * dm.h, 250, 125);
	level1.setTex("Assets/Buttons/Level 1.png");

	level2.set(0.75 * dm.w, 0.425 * dm.h, 250, 125);
	level2.setTex("Assets/Buttons/Level 2.png");

	background = GerenciadorGrafico::LoadTexture("Assets/Buttons/menu.png");
}

void LevelMenu::reset() {
	level1.reset();
	level2.reset();
	back.reset();
}

int LevelMenu::update() {
	level1.handleEvents();
	if (level1.click()) return BUTTON_START1;	
	
	level2.handleEvents();
	if (level2.click()) return BUTTON_START2;

	back.handleEvents();
	if (back.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void LevelMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,GerenciadorGrafico::getDimensoesJanela().x,GerenciadorGrafico::getDimensoesJanela().y };
	GerenciadorGrafico::render(background, fonte, destino);
	level1.render();
	level2.render();
	back.render();
}