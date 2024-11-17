#pragma once

class Unit{
    public:
        virtual void move(int x, int y) = 0;
        virtual void attack(int x, int y) = 0;
};
