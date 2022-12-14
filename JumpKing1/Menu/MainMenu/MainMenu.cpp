#include "MainMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

MainMenu::MainMenu() {
	background = nullptr;
}

MainMenu::~MainMenu() {
	SDL_DestroyTexture(background);
}

void MainMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	start.set(0.75 * dm.w, 0.25 * dm.h, 0.13 * dm.w, 0.115*dm.h);
	start.setTex("Assets/Buttons/New Game Button.png");

	load.set(0.75 * dm.w, 0.43 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	load.setTex("Assets/Buttons/load.png");

	settings.set(0.6 * dm.w, 0.25 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	settings.setTex("Assets/Buttons/Options Button.png");

	leaderboard.set(0.6 * dm.w, 0.43 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	leaderboard.setTex("Assets/Buttons/Button Leaderboard.png");

	quit.set(0.1 * dm.w, 0.8 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Exit Button.png");

	background = graphics->LoadTexture("Assets/Buttons/menu.png");
}

void MainMenu::reset() {
	start.reset();
	leaderboard.reset();
	settings.reset();
	quit.reset();
	load.reset();
}

int MainMenu::update() {
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	render();
	graphics->present();

	start.handleEvents();
	if (start.click()) return BUTTON_START1;

	settings.handleEvents();
	if (settings.click()) return BUTTON_SETTINGS;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	leaderboard.handleEvents();
	if (leaderboard.click()) return BUTTON_LEADERBOARD;

	load.handleEvents();
	if (load.click()) return BUTTON_LOAD;


	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void MainMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y };
	graphics->render(background, fonte, destino);

	start.render();
	settings.render();
	quit.render();
	leaderboard.render();
	load.render();
}