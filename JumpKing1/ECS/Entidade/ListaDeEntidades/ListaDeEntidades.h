#pragma once

#include <vector>

#include "../Personagem/Jogador/Jogador.h"
#include "../Personagem/Inimigo/InimigoTipo1/InimigoTipo1.h"
#include "../Personagem/Inimigo/InimigoTipo2/InimigoTipo2.h"
#include "../Personagem/Inimigo/InimigoTipo3/InimigoTipo3.h"
#include "../Personagem/Inimigo/Chefe/Chefe.h"

class ListaDeEntidades {
public:
	ListaDeEntidades();
	~ListaDeEntidades();
	void atualizar();
	void addEntidade(Entidade* en);
	void render();
private:
	std::vector<Entidade*> listaEntidades;


};