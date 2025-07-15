#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>

bool isTouching(int maze[20][20], int x, int y, int tile);
void renderMaze(int maze[20][20], int end[2], int distances[400]);

int main() {
	int maze[20][20] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
		{0,1,0,1,8,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
		{0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,0,0},
		{0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,0},
		{0,1,0,0,0,1,1,1,0,1,1,0,0,0,1,0,1,0,1,0},
		{0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0},
		{0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,0},
		{0,1,0,1,0,1,1,1,0,0,1,0,1,0,1,0,0,0,1,0},
		{0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0},
		{0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,0},
		{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	int* distances = new int[400];
	int end[2] = {1, 1};
	bool found = false;
	int steps = 0;

	renderMaze(maze, end, distances);
	
	while (!found) {
		steps++;
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				if (maze[y][x] == 8) continue;
				if ((isTouching(maze, x, y, 2) || isTouching(maze, x, y, 8)) && maze[y][x] == 1) {
					maze[y][x] = 4;
				}
			}
		}
		for (int y = 0; y < 20; y++) {
			for (int x = -1; x < 20; x++) {
				if (maze[y][x] == 8) continue;
				if (maze[y][x] == 4) {
					maze[y][x] = 2;
					distances[y * 20 + x] = steps;
					// std::cout << std::to_string(x) + ", " + std::to_string(y) << std::endl;
					// std::cout << steps << std::endl;
				}
			}
		}
		found = isTouching(maze, end[0], end[1], 2);
		renderMaze(maze, end, distances);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << steps << " steps" << std::endl;

	delete[] distances;

	return 0;
}

bool isTouching(int maze[20][20], int x, int y, int tile) {
	return maze[y][x-1] == tile || maze[y][x+1] == tile || maze[y-1][x] == tile || maze[y+1][x] == tile;
};

void renderMaze(int maze[20][20], int end[2], int distances[400]) {
	std::cout << "\x1B[2J\x1B[H";
	std::string symbols[5] = {"\x1B[0mXX", "\x1B[40m  \x1B[0m", "\x1B[32mXX\x1B[0m", "\x1B[31m@@\x1B[0m", "\x1b[33m@@\x1b[0m"};
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			if (end[0] == x & end[1] == y) {
				std::cout << symbols[3];
			}
			else if (maze[y][x] == 8) {
				std::cout << symbols[4];
			}
			else if (maze[y][x] == 2) {
				if ((y + x) % 2 == 0) {
					std::cout << "\x1B[32m\x1B[40m";
				} else {
					std::cout << "\x1B[42m\x1B[30m";
				}
				if (distances[y * 20 + x] < 10) {
					std::cout << 0;
				}
				std::cout << distances[y * 20 + x];
				std::cout << "\x1B[0m";
			} else {
				std::cout << symbols[maze[y][x]];
			}
		}
		std::cout << std::endl;
	}
}
