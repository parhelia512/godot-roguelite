#pragma once

#include "core/projectile_spawner.hpp"
#include "nodes/character.hpp"

#include <atomic>
#include <utility>
#include <vector>

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/memory.hpp>

namespace rl
{
    class Level : public godot::Node2D
    {
        GDCLASS(Level, godot::Node2D);

    public:
        Level();
        ~Level();

        void _ready() override;
        void _draw() override;
        void _process(double delta_time) override;

        inline void activate(bool active = true)
        {
            m_active = active;
        }

        inline bool active() const
        {
            return m_active;
        }

    protected:
        [[signal_callback]]
        void on_position_changed(const godot::Object* const obj, godot::Vector2 location) const;

        [[signal_callback]]
        void on_shoot_projectile(godot::Node* obj);

        static void _bind_methods()
        {
            godot::ClassDB::bind_method(godot::D_METHOD("on_position_changed"),
                                        &Level::on_position_changed);
            godot::ClassDB::bind_method(godot::D_METHOD("on_shoot_projectile"),
                                        &Level::on_shoot_projectile);
        }

    private:
        using callback_connection = std::pair<godot::String, godot::Callable>;
        std::vector<callback_connection> m_signal_connections{};

        rl::ProjectileSpawner* m_projectile_spawner{ memnew(rl::ProjectileSpawner) };
        godot::Sprite2D* m_background{ memnew(godot::Sprite2D) };
        rl::Character* m_player{ memnew(rl::Character) };
        std::atomic<bool> m_active{ false };
    };
}
