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
		{0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
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
		{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,2,0},
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
				if (isTouching(maze, x, y, 2) && maze[y][x] == 1) {
					maze[y][x] = 4;
				}
			}
		}
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				if (maze[y][x] == 4) {
					maze[y][x] = 2;
					distances[y * 20 + x] = steps;
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
	std::string symbols[5] = {"\x1B[0m@@", "\x1B[40m  \x1B[0m", "\x1B[32m@@\x1B[0m", "\x1B[31m@@\x1B[0m"};
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			if (end[0] == x & end[1] == y) {
				std::cout << symbols[3];
			} else if (maze[y][x] == 2) {
				if ((y + x) % 2 == 0) {
					std::cout << "\x1B[32m\x1B[40m";
				} else {
					std::cout << "\x1B[42m\x1B[30m";
				}
				if (std::to_string(distances[y * 20 + x]).length() == 1) {
					std::cout << 0;
				}
				std::cout << distances[y * 20 + x];
			} else {
				std::cout << symbols[maze[y][x]];
			}
		}
		std::cout << std::endl;
	}
}
