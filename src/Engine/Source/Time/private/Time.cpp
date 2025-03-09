#include "../public/Time.hpp"

float Engine::Time::deltaTime;
int Engine::Time::timeStart;

void Engine::Time::BeginTime() {
    timeStart = SDL_GetTicks();
}

void Engine::Time::EndTime() {
    deltaTime = SDL_GetTicks() - timeStart;
}

float Engine::Time::DeltaTime(float mulitplier) {
    return deltaTime * mulitplier;
}