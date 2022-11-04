#pragma once 
#include <SDL.h>

class LeaderboardMenu;
class LevelMenu;
class MainMenu;
class PauseMenu;
class GameOverMenu;
class SettingsMenu;
class Fase;
class Vector2D;
class ListaDeEntidades;

class GerenciadorGrafico
{
public:
	GerenciadorGrafico();
	~GerenciadorGrafico();

	static void init(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia);
	static void init_tileMap();

	static void setListaDeEntidades(ListaDeEntidades* lista);

	static SDL_Texture* LoadTexture(const char* fileName);
	//static void render(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino);
	static void render(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino, bool flip = false);

	static Vector2D getDimensoesJanela();

	static void renderFase(Fase* fase);

	static void renderTile(SDL_Rect fonte, SDL_Rect destino);
	static void renderHitbox(SDL_Rect fonte, SDL_Rect destino);

	static void renderMenu(LeaderboardMenu& leaderboard);
	static void renderMenu(LevelMenu& level);
	static void renderMenu(MainMenu& start);
	static void renderMenu(PauseMenu& pause);
	static void renderMenu(GameOverMenu& gameover);
	static void renderMenu(SettingsMenu& settings);
private:
	static SDL_Texture* tileset;
	static SDL_Texture* tilesetHitbox;
	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static Vector2D dimensoesJanela;
	static ListaDeEntidades* entidades;
};