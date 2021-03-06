/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#include "Basic2DScene.h"

Basic2DScene::Basic2DScene()
{
	m_Renderer = new Renderer2D();
}

Basic2DScene::~Basic2DScene() {
}

void Basic2DScene::Draw()
{
    auto sprites = m_TextureHandler->GetSpriteRenderList();
    for (auto it = sprites.begin(); it != sprites.end(); it++)
    {
        Get2DRenderer().Draw( (**it) );
    }
}

void Basic2DScene::Load() {
    Scene::Load();
	GRRLIB_2dMode();
}


void Basic2DScene::Unload()
{
    for (uint32_t i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}
	m_elements.clear();
    Scene::Unload();

}
Renderer2D& Basic2DScene::Get2DRenderer()
{
	return static_cast<Renderer2D&>(*m_Renderer);
}

void Basic2DScene::Update(float deltaSeconds) {
	for (uint32_t i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->Update();
	}
}
