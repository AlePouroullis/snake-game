/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
//#include <cstdlib>
#include <tuple>
#include <vector>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx),
	rng(std::random_device()()),
	xDist(1 + board.getBorderSize(), board.getWidth()-2 - board.getBorderSize()),
	yDist(1 + board.getBorderSize() , board.getHeight()-2 - board.getBorderSize()),
	snake({ xDist(rng), yDist(rng) }),
	food(rng, board, snake)
{	
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameIsOver) {

		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			gameIsStarted = true;

		if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			snake.setDir(0);
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			snake.setDir(1);
		}
		else if (wnd.kbd.KeyIsPressed(VK_UP)) {
			snake.setDir(2);
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			snake.setDir(3);
		}
	
		snake_move_counter++;
		if (snake_move_counter >= snake_move_period) {
			snake_move_counter = 0;
			snake.move();
		}

		food.glow();
		
		if (snake.getHead() == food.getLocation()) {
			snake.grow();
			food.respawn(rng, board, snake);
		}

		if (!board.isInsideBoard(snake.getHead()) || snake.collidingWithSelf())
			gameIsOver = true;
	}
}

void Game::ComposeFrame()
{
	board.drawBoard();
	if (!gameIsStarted) {
		SpriteCodex::DrawTitle(300, 300, gfx);
	}else if (!gameIsOver) {
		food.draw(board);
		snake.draw(board);
	}
	else {
		SpriteCodex::DrawGameOver(400, 400, gfx);
	}

}
