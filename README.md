![AzerothCore](https://img.shields.io/badge/AzerothCore-Module-blue.svg)
![License: GPL v2](https://img.shields.io/badge/License-GPLv2-blue.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)
![WoW Version](https://img.shields.io/badge/WotLK-3.3.5a-FFCC00.svg)

# mod-autolearn-skills
AzerothCore Module — Automatic Skill, Riding, and Mount Learning

This AzerothCore module automatically teaches players class‑appropriate weapon skills, riding ranks, and optionally grants mounts as they level up. It also optionally maxes all combat skills (weapon skills, defense, unarmed) on each level‑up.

The module is designed to be:

- Retail‑accurate by default
- Fully configurable
- Lightweight

---

## Features

### Automatic Weapon Skill Learning
Players automatically learn all weapon skills appropriate for their class when they level up.

### Automatic Combat Skill Maxing
All combat skills (weapon skills, defense, unarmed, etc.) are automatically maxed to the correct value for the player’s level.

### Automatic Riding Skill Learning
Each riding rank can be individually enabled or disabled:

- Apprentice Riding (20)
- Journeyman Riding (40)
- Expert Riding (60)
- Artisan Riding (70)
- Cold Weather Flying (77)

### Optional Mount Granting
Each riding rank has its own mount‑grant toggle:

- Apprentice → racial ground mounts
- Journeyman → epic racial ground mounts
- Expert → basic flying mount
- Artisan → epic flying mount

Epic mounts are only granted if the corresponding toggle is enabled.

### Retail‑accurate defaults
Only Apprentice Riding and Apprentice mounts are enabled by default.

---

## Configuration

Add or modify the following in your `mod_autolearn_skills.conf`:

```ini
[AutoLearnSkills]

# Enable or disable the module
AutoLearnSkills.Enable = 1

# Automatically learn class-appropriate weapon skills
AutoLearnSkills.AutoLearnWeaponSkills = 1

# Automatically max weapon skill values when learned
AutoLearnSkills.MaxWeaponSkills = 1

# Automatically learn riding skills
AutoLearnSkills.AutoLearnRiding = 1

# Learn Apprentice riding and grant apprentice ground mount (20)
AutoLearnSkills.Riding.Apprentice = 1
AutoLearnSkills.Riding.GrantApprenticeMount = 1

# Learn Journeyman riding and grant epic ground mount (40)
AutoLearnSkills.Riding.Journeyman = 0
AutoLearnSkills.Riding.GrantJourneymanMount = 0

# Learn Expert riding and grant basic flying mount (60)
AutoLearnSkills.Riding.Expert = 0
AutoLearnSkills.Riding.GrantExpertMount = 0

# Learn Artisan riding and grant epic flying mount (70)
AutoLearnSkills.Riding.Artisan = 0
AutoLearnSkills.Riding.GrantArtisanMount = 0

# Learn Cold Weather Flying automatically (77)
AutoLearnSkills.Riding.ColdWeather = 0
```
## Notes
All mount‑grant toggles default to 0 (disabled) except Apprentice.

The module only runs on level‑up, so new characters receive their first update at level 2.

Epic mounts are granted only when explicitly enabled.

## Mounts Granted
### Slow Ground Mounts (Apprentice)
Players receive all racial slow ground mounts appropriate for their race when Apprentice Riding is granted and the mount toggle is enabled.

### Epic Ground Mounts (Journeyman)
Players receive all racial epic ground mounts appropriate for their race when Journeyman Riding is granted and the mount toggle is enabled.

### Basic Flying Mounts (Expert)
Players receive a basic flying mount appropriate for their faction when Expert Riding is granted and the mount toggle is enabled.

### Epic Flying Mounts (Artisan)
Players receive an epic flying mount appropriate for their faction when Artisan Riding is granted and the mount toggle is enabled.

## Testing Checklist
- Level 2 → combat skills max
- Level 20 → Apprentice Riding + slow racial ground mounts (if enabled)
- Level 40 → Journeyman Riding + epic racial ground mounts (if enabled)
- Level 60 → Expert Riding + basic flying mount (if enabled)
- Level 70 → Artisan Riding + epic flying mount (if enabled)
- Level 77 → Cold Weather Flying (if enabled)

## Installation
1. Clone or download this module into your AzerothCore modules directory:
```
modules/mod-autolearn-skills
```
2. Rebuild AzerothCore:
```
cd build
cmake ..
make -j$(nproc)
```
3. Copy the .conf.dist file into your server’s config directory and rename it:
```
mod_autolearn_skills.conf
```
4. Adjust settings as desired.

## Contributing
Pull requests and improvements are welcome.
If you want to add additional mount types, class‑specific behavior, or debug logging, feel free to open an issue.
