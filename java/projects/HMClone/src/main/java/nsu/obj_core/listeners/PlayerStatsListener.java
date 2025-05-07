package nsu.obj_core.listeners;

import nsu.entity.weapons.Weapon;

// make UI object that's going to listen to player stat
public interface PlayerStatsListener {
    void onHealthChanged(int newHealth);
    void onWeaponChanged(Weapon newWeapon);
}
