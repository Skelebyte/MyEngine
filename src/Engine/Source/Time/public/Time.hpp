#ifndef TIME_HPP
#define TIME_HPP

#include <SDL3/SDL.h>



namespace Engine {
    class Time {
        public:
        static void BeginTime();
        static void EndTime();

        static float DeltaTime(float mulitplier = 1.0f);

        private:
        static float deltaTime;
        static int timeStart;
        
    };
}

#endif // TIME_HPP
