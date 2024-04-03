#include <iostream>
#include <vector>
#include <chrono>
#include <SDL.h>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

int WindowSizeX;
int WindowSizeY;
SDL_Renderer* renderer;
float FL = 5;

Point2D projection2(Point3D point)
{
    return Point2D{ WindowSizeX / 2 + (point.x * FL) / (FL + point.z) * 140, WindowSizeY / 2 + (point.y * FL) / (FL + point.z) * 140 };
}

void render2(const std::vector<Point3D>& points, const std::vector<Edge>& edges)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 750000, 750000, 750000, SDL_ALPHA_OPAQUE);

    for (const auto& edge : edges) {
        Point2D start = projection2(points[edge.start]);
        Point2D end = projection2(points[edge.end]);

        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    // Create points
    std::vector<Point3D> points{
        Point3D{ 0.5, 0, 0 },
        Point3D{ 0, 1, 0 },
        Point3D{ 1,  1, 0 },
        Point3D{ 0, 2, 0 },
        Point3D{ 1,  2 ,0 },
    };

    // Create edges
    std::vector<Edge> edges{
        Edge{ 0, 1 },
        Edge{ 0, 2 },
        Edge{ 0, 3 },
        Edge{ 0, 4 },
        Edge{ 1, 2 },
        Edge{ 1, 3 },
        Edge{ 3, 4 },
        Edge{ 4, 2 },
    };

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << " SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Growing Pyramid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Error !!! " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << " Error !!! Renderer " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);

    

    bool running = true;
    float time = 0.0f;

    while (running)
    {
        // Update z-coordinates of points to make the shape grow and shrink
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].z = sin(time * 0.5f) + 5.0f; // Vary z-coordinate sinusoidally
        }

        // Render the shape
        render2(points, edges);

        // Increment time
        time += 0.1f;

        SDL_Delay(15);

        // Handle SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    // Cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
