#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>

#define MAX_CELLS 1024
#define WIDTH 128
#define HEIGHT 128

using namespace std;

class celluar_automata : public olc::PixelGameEngine
{
public:
	celluar_automata()
	{
		sAppName = "Celluar Automata";
	}

private:
	int cell_grid[WIDTH][HEIGHT];

	void handle_nearby_cells(int cell_grid[][128], const int &pos_x, const int &pos_y)
	{
		int neighbor_sum = cell_grid[pos_x - 1][pos_y - 1] +
			cell_grid[pos_x - 0][pos_y - 1] + cell_grid[pos_x + 1][pos_y - 1] +
			cell_grid[pos_x - 1][pos_y + 0] + cell_grid[pos_x + 1][pos_y + 0] +
			cell_grid[pos_x - 1][pos_y + 1] + cell_grid[pos_x + 0][pos_y + 1] +
			cell_grid[pos_x + 1][pos_y + 1];

		if (neighbor_sum < 2)
		{
			cell_grid[pos_x][pos_y] = 0;
		}
		else if (neighbor_sum > 3)
		{
			cell_grid[pos_x][pos_y] = 0;
		}
		else if (neighbor_sum == 3 && cell_grid[pos_x][pos_y] == 0)
		{
			cell_grid[pos_x][pos_y] = 1;
		}
	}

	void draw_game()
	{
		for (int x = 0; x < WIDTH; x++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				handle_nearby_cells(cell_grid, x, y);

				if (cell_grid[x][y] == 1)
				{
					Draw(x, y, olc::WHITE);
				}
				else
				{
					Draw(x, y, olc::BLACK);
				}
			}
		}
	}

	void reset_grid()
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLANK);
		for (int x = 0; x < WIDTH; x++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				cell_grid[x][y] = 0;
			}
		}

		OnUserCreate();
	}

	void user_controls()
	{
		if (GetKey(olc::Key::R).bHeld)
		{
			reset_grid();
		}

		if (GetKey(olc::Key::SHIFT).bHeld)
		{
			this_thread::sleep_for(5ms);
		}
		else if (!GetKey(olc::Key::SHIFT).bHeld)
		{
			this_thread::sleep_for(40ms);
		}

		if (GetKey(olc::Key::CTRL).bHeld)
		{
			this_thread::sleep_for(80ms);
		}
	}

public:
	bool OnUserCreate() override
	{
		srand(time(0));
		for (int i = 0; i < MAX_CELLS; i++)
		{
			cell_grid[rand() % WIDTH][rand() % HEIGHT] = 1;
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::SPACE).bHeld)
		{
			return true;
		}

		draw_game();
		user_controls();

		return true;
	}
};


int main()
{
	celluar_automata demo;
	if (demo.Construct(WIDTH, HEIGHT, 4, 4))
		demo.Start();

	return 0;
}
