#include <mosaic/application/application.hpp>
#include <mosaic/application/instance.hpp>

#include <mosaic/ecs/view.hpp>

#include <mosaic/macros/main.hpp>

struct Health
{
    float Value;
};

struct Speed
{
    float Value;
};

struct Position
{
    float X, Y;
};

struct Weapon
{
    float Damage;
};

struct TimeTracker
{
    int Steps;
    int Max;
};

struct DamageEvent
{
    Mosaic::Entity Target;

    float Amount;
};

void OnDamage(Mosaic::ApplicationResources& resources, const DamageEvent& event, Mosaic::ECSView<Health> view)
{
    auto& console = resources.Console;

    for (auto [entity, health] : view)
    {
        if (entity == event.Target)
        {
            health.Value -= event.Amount;

            console.Log<Mosaic::Console::LogSeverity::Notice>("Entity {} took damage: {}. New health: {}", entity.ID, event.Amount, health.Value);
        }
    }
}

void AttackSystem(Mosaic::ApplicationResources& resources)
{
    auto& ecsManager = resources.ECSManager;
    auto& eventManager = resources.EventManager;
    auto& console = resources.Console;

    auto healthView = ecsManager.QueryView<Health>();
    auto weaponView = ecsManager.QueryView<Weapon>();

    for (auto [entity, health] : healthView)
    {
        console.Log<Mosaic::Console::LogSeverity::Notice>("Health of entity {}: {}", entity.ID, health.Value);
    }

    for (auto [attackerEntity, weapon] : weaponView)
    {
        for (auto [targetEntity, health] : healthView)
        {
            if (targetEntity != attackerEntity)
            {
                eventManager.Emit<DamageEvent>(targetEntity, weapon.Damage);

                console.Log<Mosaic::Console::LogSeverity::Notice>("Entity {} attacks entity {} for {} damage", attackerEntity.ID, targetEntity.ID, weapon.Damage);
            }
        }
    }
}

void TimeSystem(Mosaic::ApplicationResources& resources)
{
    auto& ecsManager = resources.ECSManager;
    auto& eventManager = resources.EventManager;
    auto& console = resources.Console;

    auto timeView = ecsManager.QueryView<TimeTracker>();

    for (auto [entity, time] : timeView)
    {
        console.Log<Mosaic::Console::LogSeverity::Notice>("Iteration number: {}", time.Steps);

        time.Steps++;
    }
}

class MosaicTest : public Mosaic::Application
{
public:
    MosaicTest(Mosaic::ApplicationResources& resources)
        : Application(resources)
    {
    }

    void Setup() override
    {
        auto& resources = GetApplicationResources();

        auto& ecsManager = resources.ECSManager;
        auto& eventManager = resources.EventManager;

        ecsManager.AddSystem(AttackSystem);
        ecsManager.AddSystem(TimeSystem);

        eventManager.AddResponder<DamageEvent, Health>(OnDamage);

        Mosaic::Entity entity0 = ecsManager.CreateEntity();
        Mosaic::Entity entity1 = ecsManager.CreateEntity();

        ecsManager.AddComponent<Health>(entity0, Health(100));
        ecsManager.AddComponent<Health>(entity1, Health(200));

        ecsManager.AddComponent<Speed>(entity0, Speed(100));
        ecsManager.AddComponent<Speed>(entity1, Speed(150));

        ecsManager.AddComponent<Position>(entity0, Position(100, 200));
        ecsManager.AddComponent<Position>(entity1, Position(200, 100));

        ecsManager.AddComponent<Weapon>(entity1, Weapon(5));

        ecsManager.AddComponent<TimeTracker>(entity0, TimeTracker(0, 10));
    }
};

MOSAIC_DEFINE_MAIN(MosaicTest)