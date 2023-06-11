#ifndef BODY_H
#define BODY_H
#pragma once

class Body : public Object
{
    public:
        Rectangle top;
        Rectangle down;
        Rectangle left;
        Rectangle right;

        Body();
        virtual ~Body() = default;
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void animate(Animation* animation) override;
        virtual void renderColliders() override;
        virtual void dispose() override;
        bool operator==(const Body& other) const;

    private:
        int id;

};

#endif