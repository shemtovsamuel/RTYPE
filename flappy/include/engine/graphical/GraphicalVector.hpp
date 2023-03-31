#pragma once

namespace engine
{
    namespace graphical
    {
        template <typename T>
        class Vector2
        {
        public:
            Vector2(T X = 0.0, T Y = 0.0) : x(X), y(Y)
            {
            }

            template <typename U>
            explicit Vector2(const Vector2<U> &vector) : x(vector.x), y(vector.y)
            {
            }

            T x;
            T y;
        };

        typedef Vector2<float> Vector2f;
        typedef Vector2<int> Vector2i;

        template <typename T>
        class Rect
        {
            public:
                Rect() : left(0), top(0), width(0), height(0)
                {
                }

                Rect(T left, T top, T width, T height) : left(left), top(top), width(width), height(height)
                {
                }

                template <typename U>
                explicit Rect(const Rect<U> &rectangle) : left(rectangle.left), top(rectangle.top), width(rectangle.width), height(rectangle.height)
                {
                }

                T left;
                T top;
                T width;
                T height;
        };

        typedef Rect<float> Rectf;
        typedef Rect<int> Recti;
    }
}
